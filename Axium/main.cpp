//
//  main.cpp
//  Axium
//
//  Created by Randy on 17/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//
#include "Combat.cpp"
Player me;

void goToInn()
{
    int input;
    std::cout <<"You enter the inn.";
    std::cout << "It costs 5 gold to use the inn. Would you like to stay the night?\n 1. Yes - 2. No\n";
    std::cin >> input;
    if (input == 1 && me.getMoney() >= 5)
    {
        me.acquireMoney(-5);
        me.restoreHealth();
    }
    else if (me.getMoney() < 5)
    {
        sayWait2("You can't afford to do that!");
    }
}

void chapterOneMenu(int option, bool &chapterOne)
{
    switch (option) { // Use input to determine what to do next.
        case 1:
        {
            Item batTooth("Bat tooth", 0, questType, true); // Create an item to be dropped by the Zubat.
            Monster zubat("Zubat", 15,5,5,1, 90, batTooth); // Create the Zubat for the player to fight.
            std::cout <<"A bat pops up out of nowhere and decides to get fresh with you!\nPress enter to continue . . .";
            std::cin.ignore(2); // Say a line of text and wait for the user to press the Enter key.
            Combat(zubat, me); // Start a fight with a predetermined opponent. The return value determines whether the program continues running.
            break;
        }
        case 2:
            clearScreen();
            std::cout << "\nYou currently have " << me.getMoney() << " gold.\n";
            me.showItems();
            break;
        case 3:
        {
            Item Excalibur("Excalibur", 10, attackType);

            if (!me.hasItem(Excalibur.getName()))
            {
                me.acquireItem(Excalibur);
            }
            else
            {
                std::cout << "Foolish mortal! You already own the legendary sword Excalibur. Why would you need another?\nPress enter to continue . . .";
                std::cin.ignore(2);
            }
            break;
        }
        case 4:
        {
            goToInn();
            break;
        }
        case 9:
            sayWait2("Goodbye!");
            me.setLiving(false);
            break;
        default:
            break;
    }

}

void initStory()
{
    bool chapterOne = true;
    me.setName("You");
    while (me.getLiving() && chapterOne)
    {
        clearScreen(); // Clear the screen.
        int option;
        std::cout << "What would you like to do? Enter the number for the option you would like. \n1. Fight. - 2. Check items. 3. Obtain the mighty blade Excalibur. - 4. Visit the inn. - 9. Exit\n"; // Ask the user for input.
        std::cin >> option; // Wait for input.
        if (std::cin.fail())
        {
            std::cout <<"You need to enter an integer for this to work.";
            me.setLiving(false);
        }
        else {
            chapterOneMenu(option, chapterOne);
        }
    }
}

int main(int argc, const char * argv[])
{
    
    initStory();
    if(me.getLiving())
    {
    sayWait("The next area is full of unicorns and rainbows. What will you do now?");
    }
    return 0;
}
