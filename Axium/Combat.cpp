//
//  Combat.c
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Entities.h"


static void itemDrop(Monster &enemy, Player &me)
{
    int dropRate = 100 - enemy.getDropRate();
    int rollem = arc4random() % 100 + 1;
    
    if (rollem > dropRate)
    {
        if (rollem > 95)
        {
            std::string output = "You are very lucky! The " + enemy.getName() + " dropped a scroll that will permanently increase your Attack power by " + intToString(enemy.getMobLevel()) + ".";
            sayWait(output);
            me.increaseAttack(enemy.getMobLevel());
            output = "Your new Attack level is: " + intToString(me.getAttack()) + ".";
            sayWait(output);
        }
        
        else if (rollem > 90)
        {
            std::string output = "Fortune smiles upon you! The " + enemy.getName() + " dropped a rare material that will permanently increase your Defensive power by " + intToString(enemy.getMobLevel()) + ".";
            sayWait(output);
            me.increaseDefense(enemy.getMobLevel());
            output = "Your new Defence level is: " + intToString(me.getDefense()) + ".";
            sayWait(output);
        }
        sayWait("You also acquired a " + enemy.getDroppedItemName() + ".");
        me.acquireItem(enemy.getDroppedItem());
    }
}

static bool Combat(Monster &enemy, Player &me)
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
        if (enemy.getHealth() <= 0)
            break;
        std::cout << "The " + enemy.getName() + " retaliates with an attack.\n";
        me.takeDamage(enemy.getAttack());
        if (me.getHealth() <= 0)
            break;
        
    }
    while (enemy.getHealth() > 0 && me.getHealth() > 0);
    
    if (me.getHealth() <= 0 && enemy.getHealth() > 0)
    {
        sayWait("You have lost the battle against the fearsome " + enemy.getName() + ". You were never able to see your friends or family again. How you disappeared has always remained a mystery.\nGame over.");
        return false;
    }
    
    else if (enemy.getHealth() <= 0 && me.getHealth() > 0)
    {
        sayWait("Congratulations. You have beaten the " + enemy.getName() + ".");
        itemDrop(enemy, me);
        return true;
    }
    
    else
    {
        sayWait("As you are about to land the final hit on the " + enemy.getName() + ", they counter you with a lethal blow. \nYou have defeated the " + enemy.getName() + ", but in doing so have lost your own life.\nGame over.");
        return false;
    }
}