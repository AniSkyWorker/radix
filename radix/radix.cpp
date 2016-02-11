#include "stdafx.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct Converter 
{
	std::vector<int> inputNum;
	int originalNotation;
	int resultNotation;
	bool wasError;
	bool negativeNumber;

	Converter(std::string str, int notation, int resultNotation)
		:originalNotation(notation)
		,resultNotation(resultNotation)
		,wasError(false)
		,negativeNumber(false)
	{
		CheckNotations();
		if (!HasError())
		{
			setNumberSign(str[0]);
			for (char digit : str)
				if (!HasError())
					inputNum.push_back(strElemToInt(digit));
		}
	}

	void CheckNotations()
	{
		if ((originalNotation > 36 || originalNotation < 2)
			|| (resultNotation > 36 || resultNotation < 2))
		{
			std::cout << "One of inputted notations is incorrect! [2 <= noatation <= 36]";
			Error();
		}

		return;
	}

	void Negative()
	{
		negativeNumber = true;
		return;
	}

	void Error()
	{
		wasError = true;
		return;
	}

	bool IsNegative() const
	{
		return negativeNumber;
	}

	bool HasError() const
	{
		return wasError;
	}
	
	void setNumberSign(char& c)
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

	int strElemToInt(char c)
	{
		if (c >= '0' && c <= '9' && (c - '0') < originalNotation) 
			return c - '0';
		else if (c >= 'A' && c <= 'Z' && (c - 'A' + 10) < originalNotation)
			return c - 'A' + 10;
		else if (c >= 'a' && c <= 'z' && (c - 'a' + 10) < originalNotation)
			return c - 'a' + 10;
		else
		{
			Error();
			std::cout << "Invalid character in number that inputted to convert!";
			return NULL;
		}
	}

	char intToStrElem(int num)
	{
		if (num >= 0 && num <= 9)
			return num + '0';
		else
			return num + 'A' - 10;
	}

	int GetConvertDigit()
	{
		int convertDigit = 0;
		for (int& digit : inputNum)
		{
				convertDigit = convertDigit*originalNotation + digit;
				digit = convertDigit / resultNotation;
				convertDigit = convertDigit % resultNotation;
		}
		return convertDigit;
	}

	bool IsZero()
	{
		for (int digit : inputNum)
			if (digit != 0)
				return false;

		return true;
	}

	std::string GetConvertNum()
	{
		std::string result;

		if (IsZero())
			return result += '0';

		if (IsNegative())
			result += '-';

		std::vector<int> resultNum;
		while(!IsZero())
			resultNum.push_back(GetConvertDigit());

		for (auto it = resultNum.rbegin();it != resultNum.rend(); it++)
			result += intToStrElem(*it);

		return result;
	}
};

bool IsNotationIncorrect(std::string notation)
{
	for (char chr : notation)
		if (!(chr >= '0' && chr <= '9'))
			return true;

	return false;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid number of parametrs!" << std::endl
			<< "Usage: <number> <originalNotation> <resultNotation>";
		return 1;
	}
	
	if (IsNotationIncorrect(argv[2]) || IsNotationIncorrect(argv[3]))
	{
		std::cout << "One of inputted notations is incorrect! [2 <= noatation <= 36]";
		return 1;
	}
	
	Converter converter(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
	if (converter.HasError())
		return 1;

	std::cout << converter.GetConvertNum() << std::endl;
    return 0;
}

