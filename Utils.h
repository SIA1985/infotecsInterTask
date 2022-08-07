#pragma once

#include <iostream>
#include <algorithm>

#include "ProgramClasses.h"


#define LOG(a) std::cerr << "Error: " << a << '\n';
#define CONSOLE(a) std::cout << a << '\n';


//First subprogram
Errors CheckStringLengthAndContetnt(std::string& __string)
{
	if (__string.length() > 64)
	{
		LOG("Input string is longer then 64 symbols")
		return Errors::InvalidInput; 
	}

	int i = 0;
	while (__string[i])
	{
		if (__string[i] < '0' || __string[i] > '9')
		{
			LOG("Input string contains symbols that are not numbers")
			return Errors::InvalidInput;
		}
		i++;
	}

	return Errors::NoErrors;
}

void StringProcessing(std::string& __string)
{
	std::sort<std::string::iterator>(__string.begin(), __string.end(), [](char a, char b) {return a > b; });


	std::string NewString;

	for (auto it = __string.begin(); it < __string.end(); it++)
	{
		if (*it % 2 == 0)
		{
			NewString.append("KB");
		}
		else
		{
			NewString.push_back(*it);
		}
	}

	__string = NewString;
}


//Second subprogram
int GetSumOfEvenNumbersInString(std::string& __string)
{
	int EvenNumbersSum = 0;
	for (auto it = __string.begin(); it < __string.end(); it++)
	{
		if (*it >= '0' && *it <= '9')
		{
			EvenNumbersSum += int(*it) - 48;
		}
	}

	return EvenNumbersSum;
}