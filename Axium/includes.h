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
#include <thread>
#include <chrono>
#include <fstream>

static bool fexists(const char *filename) // If file exists, return true. If not, return false.
{
    std::ifstream ifile(filename);
    return ifile.good();
}

static std::string intToString(int i) // Return the supplied int in string form.
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

static void sayWait(std::string input) // Say a line, then display "Press enter to continue . . ." below. Wait for user to press enter, then remove the line and replace it with another.
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

static void sayWait2(std::string input) // Say a line, then display "Press enter to continue . . ." below. Wait for user to press enter, then remove the line and replace it with another. This function ignores 2 enters.
{
    std::cout << input << "\n";
    std::cout << "Press enter to continue . . .";
    std::cin.ignore(2);
    std::cout << "\033[F";
    for(int i = 0; i < 31; i++)
        std::cout << "\b";
    for(int i = 0; i < 31; i++)
        std::cout << " ";
    for(int i = 0; i < 31; i++)
        std::cout << "\b";
}

static void clearScreen() // Clear the screen with 100 newlines.
{
    std::cout << std::string( 100, '\n' );
}

#endif
