// osuParse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DBug.h"

int main()
{
	std::cout << std::boolalpha;

	Dbug::primitive_debug();
	Dbug::algorithm_debug();

	int test = 0;
	std::cin >> test;
    return 0;
}

