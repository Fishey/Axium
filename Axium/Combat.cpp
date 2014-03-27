//
//  Combat.c
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Entities.h"
static void Combat(Monster &enemy, Player &me);

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
        sayWait("You also acquired one " + enemy.getDroppedItemName() + ".");
        me.acquireItem(enemy.getDroppedItem());
    }
    me.acquireMoney(enemy.getMoney());
}

static int doAttack(Monster &enemy, Player &me, int choice)
{
    int returnedDefense = 0;
    switch(me.getType())
    {
        case Paladin:
            switch(choice)
            {
                case 1:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    enemy.takeDamage(me.getAttack());
                    me.increaseHp(0.5*(0.8*(me.getAttack()-enemy.getDefense())));
                    break;
                case 2:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    enemy.takeDamage(1.3*me.getAttack());
                    break;
                case 3:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    enemy.takeDamage(0.6*me.getAttack());
                    returnedDefense = me.getDefense() * 0.5 + 2;
                    break;
                case 4:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    me.decreaseHp(0.1*me.getHealth());
                    enemy.takeDamage(1.5*me.getAttack());
                    break;
                default:
                    Combat(enemy, me);
            }
            break;
        case Ninja:
            switch(choice)
            {
                case 1:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    enemy.takeDamage(me.getAttack());
                    me.increaseHp(0.3*(0.8*(me.getAttack()-enemy.getDefense())));
                    break;
                case 2:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    sayWait("Your ninja-like accuracy allows you to bypass the enemy's armor.");
                    enemy.takeDamage(me.getAttack()+enemy.getDefense());
                    break;
                case 3:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    returnedDefense = me.getDefense() * 0.5 + 1;
                    enemy.takeDamage(me.getAttack());
                    break;
                case 4:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    me.decreaseHp(0.3*me.getHealth());
                    enemy.takeDamage(2*me.getAttack());
                    break;
                default:
                    Combat(enemy, me);
            }

            break;
        case Commander:
            switch(choice)
            {
                case 1:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    enemy.takeDamage(me.getAttack());
                    me.increaseHp(0.5*(0.8*(me.getAttack()-enemy.getDefense())));
                    break;
                case 2:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    enemy.takeDamage(1.3*me.getAttack());
                    break;
                case 3:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    enemy.takeDamage(0.8*me.getAttack());
                    break;
                case 4:
                {
                    int rollem = arc4random() % 100 + 1;
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    if (rollem > 75)
                        enemy.takeDamage(3*me.getAttack());
                    else
                        sayWait("The enemy was too quick! Your shot misses!");
                    break;
                }
                default:
                    Combat(enemy, me);
            }

            break;
            
        }
    return returnedDefense;
    }

static void Combat(Monster &enemy, Player &me)
{
    do
    {
        clearScreen();
        std::cout << "Your current hitpoints: " + intToString(me.getHealth()) + ".\n";
        std::cout << "The enemy's current hitpoints: " + intToString(enemy.getHealth()) + ".\n";
        std::cout << "Your attack power: " + intToString(me.getAttack()) + ".\n";
        std::cout << "The enemy's defense: " + intToString(enemy.getDefense()) + ".\n";
        int input;
        std::cout << "What type of attack would you like to perform?\n";
        int i = 0;
        for (std::string &skill : me.getSkills())
        {
            i++;
            std::cout << i << ". Use " << skill << ".\n";
        }

        std::cin >> input;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            sayWait("You need to enter an integer for this to work.");
        }
        else
        {
            int returnedDefense = doAttack(enemy, me, input);
            if (enemy.getHealth() <= 0)
                break;
            sayWait("The " + enemy.getName() + " retaliates with an attack.");
            me.takeDamage(enemy.getAttack() - returnedDefense);
            if (me.getHealth() <= 0)
                break;
        }
    }
    while (enemy.getHealth() > 0 && me.getHealth() > 0);
    
    if (me.getHealth() <= 0 && enemy.getHealth() > 0)
    {
        sayWait("You have lost the battle against the fearsome " + enemy.getName() + ". You were never able to see your friends or family again. How you disappeared has always remained a mystery.\nGame over.");
        me.setLiving(false);
        exit(0);
    }
    
    else if (enemy.getHealth() <= 0 && me.getHealth() > 0)
    {
        sayWait("Congratulations. You have beaten the " + enemy.getName() + ".");
        itemDrop(enemy, me);
    }
    
    else
    {
        sayWait("As you are about to land the final hit on the " + enemy.getName() + ", they counter you with a lethal blow. \nYou have defeated the " + enemy.getName() + ", but in doing so have lost your own life.\nGame over.");
        me.setLiving(false);
        exit(0);
    }
}