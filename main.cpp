// osuParseSub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

int main()
{
	
	try {
		OsuMap map = OsuMap("map.txt");

		auto LNList = map.hitObjectList().longNote;
		for (auto LN : LNList) {
			std::cout << LN.str() << std::endl;
		}
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}


	std::cout << "Program Complete!" << std::endl;  
}

