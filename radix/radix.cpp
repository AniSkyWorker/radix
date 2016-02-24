#include "stdafx.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

const int C_MAX_NOTATION = 36;
const int C_MIN_NOTATION = 2;

struct SConverter 
{
	std::vector<int> m_inputNum;
	int m_originalNotation;
	int m_resultNotation;
	bool m_wasError = false;
	bool m_negativeNumber = false;

	SConverter(std::string str, int notation, int resultNotation)
		:m_originalNotation(notation)
		,m_resultNotation(resultNotation)
	{
		CheckNotations();

		if (!HasError())
		{
			ParseNumberSign(str[0]);
			for (char digit : str)
			{
				if (!HasError())
				{
					m_inputNum.push_back(StrElemToInt(digit));
				}
			}
		}
	}

	void CheckNotations()
	{
		if ((m_originalNotation > C_MAX_NOTATION || m_originalNotation < C_MIN_NOTATION)
			|| (m_resultNotation > 36 || m_resultNotation < 2))
		{
			std::cout << "One of inputted notations is incorrect! [2 <= notation <= 36]" <<std::endl;
			Error();
		}

		return;
	}

	void Negative()
	{
		m_negativeNumber = true;
	}

	void Error()
	{
		m_wasError = true;
	}

	bool IsNegative() const
	{
		return m_negativeNumber;
	}

	bool HasError() const
	{
		return m_wasError;
	}
	
	void ParseNumberSign(char& c)
	{
		if (c == '-')
		{
			Negative();
			c = '0';
		}
		else if (c == '+')
		{
			c = '0';
		}
	}

	int StrElemToInt(char chr)
	{
		int digit;

		if (chr >= '0' && chr <= '9')
		{
			digit = chr - '0';

			if (digit < m_originalNotation)
			{
				return digit;
			}
		}
		else if (chr >= 'A' && chr <= 'Z')
		{
			digit = chr - 'A' + 10;
			if (digit < m_originalNotation)
			{
				return digit;
			}
		}
		else if (chr >= 'a' && chr <= 'z')
		{
			digit = chr - 'a' + 10;
			if (digit < m_originalNotation)
			{
				return digit;
			}
		}
		Error();
		std::cout << "Invalid character in number that inputted to convert!" << std::endl;
		return 0;
	}

	char IntToStrElem(int num)
	{
		if (num >= 0 && num <= 9)
			return num + '0';
		else
			return num + 'A' - 10;
	}

	int GetConvertDigit()
	{
		int convertDigit = 0;
		for (int& digit : m_inputNum)
		{
				convertDigit = convertDigit * m_originalNotation + digit;
				digit = convertDigit / m_resultNotation;
				convertDigit = convertDigit % m_resultNotation;
		}
		return convertDigit;
	}

	bool IsZeroNumber() const
	{
		for (int digit : m_inputNum)
		{
			if (digit != 0)
			{
				return false;
			}
		}

		return true;
	}

	std::string GetConvertNumInStr()
	{
		std::string result;

		if (IsZeroNumber())
		{
			return result += '0';
		}

		if (IsNegative())
		{
			result += '-';
		}

		std::vector<int> resultNum;
		while (!IsZeroNumber())
		{
			resultNum.push_back(GetConvertDigit());
		}

		for (auto it = resultNum.rbegin();it != resultNum.rend(); it++)
		{
			result += IntToStrElem(*it);
		}

		return result;
	}
};

bool IsNotationIncorrect(const std::string& notation)
{
	if (notation.length() > C_MIN_NOTATION)
	{
		return true;
	}

	for (char chr : notation)
	{
		if (!(chr >= '0' && chr <= '9'))
		{
			return true;
		}
	}

	return false;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid number of arguments!" << std::endl
			<< "Usage:radix.exe  <number> <originalNotation> <resultNotation>" << std::endl;
		return 1;
	}
	
	if (IsNotationIncorrect(argv[2]) || IsNotationIncorrect(argv[3]))
	{
		std::cout << "One of inputted notations is incorrect! [2 <= notation <= 36]" << std::endl;
		return 1;
	}
	
	SConverter converter(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
	if (converter.HasError())
	{
		return 1;
	}

	std::cout << converter.GetConvertNumInStr() << std::endl;
    return 0;
}

