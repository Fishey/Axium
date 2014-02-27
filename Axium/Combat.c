//
//  Combat.c
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include <stdio.h>
#include "Entities.cpp"
#include "includes.h"
int damage;

void Combat(Monster enemy, Player me)
{
    do
    {
        clearScreen();
        std::cout << "Your current hitpoints: " + intToString(me.getHealth()) + ".\n";
        std::cout << "The enemy's current hitpoints: " + intToString(enemy.getHealth()) + ".\n";
        std::cout << "Your attack power: " + intToString(me.getAttack()) + ".\n";
        std::cout << "The enemy's defense: " + intToString(enemy.getDefense()) + ".\n";
        std::cout << "You attack the " + enemy.getName() + ".\n";
        enemy.takeDamage(me.getAttack());
    }
    while (enemy.getHealth() > 0 && me.getHealth() > 0);
    
    if (me.getHealth() <= 0 && enemy.getHealth() > 0)
    {
        sayWait("You have lost the battle. You were never able to see your friends or family again. How you disappeared has always remained a mystery.\nGame over.");
    }
    
    else if (enemy.getHealth() <= 0 && me.getHealth() > 0)
    {
        std::cout << "Congratulations. You have beaten the " + enemy.getName() + ".";
    }
    
    else
    {
        sayWait("As you are about to land the final hit on the " + enemy.getName() + ", they counter you with a finishing blow. \nYou have defeated the " + enemy.getName() + ", but in doing so have lost your own life.\nGame over.");
    }
}