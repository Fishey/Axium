//
//  includes.h
//  Axium
//
//  Created by Randy on 19/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#ifndef Axium_includes
#define Axium_includes
#include <iostream>
#include <sstream>
#include <vector>

std::string intToString(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

void sayWait(std::string input)
{
    std::cout << input << "\n";
    std::cout << "Press enter to continue . . .";
    std::cin.ignore(1);
    std::cout << "\033[F";
    for(int i = 0; i < 31; i++)
        std::cout << "\b";
    for(int i = 0; i < 31; i++)
        std::cout << " ";
    for(int i = 0; i < 31; i++)
        std::cout << "\b";
}

void clearScreen()
{
    std::cout << std::string( 100, '\n' );
}

#endif
