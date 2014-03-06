//
//  main.cpp
//  Axium
//
//  Created by Randy on 17/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//
#include "Combat.c"
Player me;

void initStory()
{
    
    bool running = true;
    me.setName("You");
    while (running != false)
    {
        clearScreen(); // Clear the screen.
        int option;
        std::cout << "What would you like to do? Enter the number for the option you would like. \n1. Fight - 2. Exit - 3. Check items.\n";
        std::cin >> option;
        switch (option) {
            case 1:
            {
                Monster zubat("Zubat", 15,5,5,1, 90, "Bat tooth");
                sayWait("A bat pops up out of nowhere and decides to get fresh with you!"); // Say a line of text and wait for the user to press the Enter key.
                Combat(zubat, me); // Start a fight with a predetermined opponent.
                break;
            }
            case 2:
                sayWait("Goodbye!");
                running = false;
                break;
            case 3:
                me.showItems();
                break;
            default:
                break;
        }
    }
}

int main(int argc, const char * argv[])
{
    initStory();
    return 0;
}