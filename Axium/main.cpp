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
        std::cout << "What would you like to do? Enter the number for the option you would like. \n1. Fight - 2. Check items. - 9. Exit\n"; // Ask the user for input.
        std::cin >> option; // Wait for input.
        if (std::cin.fail())
        {
            std::cout <<"Fuck you for trying to fuck with my code. Dick.";
            running = false;
        }
        else {
        switch (option) { // Use input to determine what to do next.
            case 1:
            {
                Item batTooth("Bat tooth"); // Create an item to be dropped by the Zubat.
                Monster zubat("Zubat", 15,5,5,1, 90, batTooth); // Create the Zubat for the player to fight.
                sayWait("A bat pops up out of nowhere and decides to get fresh with you!"); // Say a line of text and wait for the user to press the Enter key.
                running = Combat(zubat, me); // Start a fight with a predetermined opponent.
                break;
            }
            case 2:
                me.showItems();
                break;
            case 3:
            {
                if (!me.hasItem("Excalibur"))
                {
                Item Excalibur("Excalibur", 10, attackType);
                me.acquireItem(Excalibur);
                }
                else
                {
                    std::cout << "Foolish mortal! You already own the legendary sword Excalibur. Why would you need another?\nPress enter to continue . . .";
                    std::cin.ignore(2);
                }
                break;
            }
            case 9:
                sayWait("Goodbye!");
                running = false;
                break;
            default:
                break;
        }
        }
    }
}

int main(int argc, const char * argv[])
{
    initStory();
    return 0;
}