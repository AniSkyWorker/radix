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
		if(!HasError())
			for (char digit : str)
				if(!HasError())
					inputNum.push_back(strElemToInt(digit));
	}

	void CheckNotations()
	{
		if ((originalNotation > 32 || originalNotation < 2)
			|| (resultNotation > 32 || resultNotation < 2))
		{
			perror("One of inputted notations is incorrect!");
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

	int strElemToInt(char c)
	{
		if (c >= '0' && c <= '9' && (c - '0') < originalNotation) 
			return c - '0';
		else if (c >= 'A' && c <= 'Z' && (c - 'A' + 10) < (originalNotation))
			return c - 'A' + 10;
		else if (c == '-')
		{
			Negative();
			return NULL;
		}
		else
		{
			Error();
			perror("Invalid character in number that inputted to convert!");
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
		for (std::size_t i = 0; i < inputNum.size(); i ++ )
		{
				convertDigit = convertDigit*originalNotation + inputNum[i];
				inputNum[i] = convertDigit / resultNotation;
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
		if (!(chr <= '9' && chr >= '0'))
			return true;

	return false;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		perror("Invalid number of parametrs!");
		return 1;
	}
	
	if (IsNotationIncorrect(argv[2]) || IsNotationIncorrect(argv[3]))
	{
		perror("One of inputted notations is incorrect!");
		return 1;
	}
	
	Converter converter(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
	if (converter.HasError())
		return 1;

	std::cout << converter.GetConvertNum() << std::endl;
    return 0;
}
