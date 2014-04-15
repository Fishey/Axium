//
//  Combat.c
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Entities.h"
static void Combat(Monster &enemy, Player &me); // Forward declaration of Combat.

static void itemDrop(Monster &enemy, Player &me) // Make monster drop an item, recieve money. Also gives a chance to give stat-boosts.
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

static void doAttack(Monster &enemy, Player &me, int choice) // Do an attack as previously chosen. Changes depending on the player's class.
{
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
                    if (me.getBuffedDefense() < 4)
                        me.increaseBuffedDefense(2);
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
                {
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    int rollem = arc4random() % 100 + 1;
                    if (rollem > 40)
                    {
                        sayWait("Your ninja-like accuracy allows you to bypass the enemy's armor.");
                        enemy.takeDamage(me.getAttack()+enemy.getDefense());
                    }
                    
                    else
                    {
                        sayWait("Your inexperience as a ninja has caused you to miss the target's vital spot.");
                        enemy.takeDamage(0.8*me.getAttack());
                    }
                    
                    break;
                }
                case 3:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    me.increaseBuffedDefense(1);
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
                {
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    double multiplier = me.getMaxHp() / me.getHealth();
                    if (multiplier > 3)
                        multiplier = 3;
                    enemy.takeDamage(me.getAttack()*multiplier);
                    break;
                }
                case 2:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    enemy.takeDamage(1.3*me.getAttack());
                    break;
                case 3:
                    sayWait2("You attack the " + enemy.getName() + " using " + me.getSkills()[choice-1] + ".");
                    enemy.takeDamage(0.8*me.getAttack());
                    if (me.getBuffedDefense() < 4)
                        me.increaseBuffedDefense(2);
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
        case Reaper:
            switch(choice)
        {
            case 1:
                sayWait2("The " + me.getClassName() + " uses " + me.getSkills()[choice-1] + " to heal itself.");
                me.decreaseHp(0.1*me.getMaxHp());
                me.bleed(-0.05*me.getMaxHp());
                break;
            case 2:
            {
                int rollem = arc4random() % 100 + 1;
                if (rollem > 40)
                {
                    sayWait2("The " + me.getClassName() + " uses " + me.getSkills()[choice-1] + " to rend the enemy's skin, causing it to bleed greatly.");
                    if (!enemy.getBleeding())
                        enemy.takeDamage(me.getAttack()+me.getBuffedAttack());
                    else if (enemy.getBleeding())
                    {
                        sayWait("The " + me.getClassName() + " inflicts additional damage as it hits the already bleeding enemy!");
                        enemy.takeDamage(1.5*me.getAttack()+me.getBuffedAttack());
                    }
                    enemy.bleed(0.5 * (me.getAttack()+me.getBuffedAttack()));
                }
                else
                {
                    sayWait2("The " + me.getClassName() + " uses " + me.getSkills()[choice-1] + " to try to rend the enemy's skin, but the blow doesn't manage to penetrate the armor of the enemy!\nInstead, the attack's impact causes a hefty amount of damage.");
                    enemy.takeDamage(me.getAttack()+me.getBuffedAttack());
                }
                
                break;
            }
            case 3:
                if (me.getResCooldown() == 0 && !me.getResurrection())
                {
                    sayWait2("The " + me.getClassName() + " uses " + me.getSkills()[choice-1] + ", absorbing life all around it to ensure it's own survival.");
                    me.setResurrection();
                }
                else if (me.getResCooldown() > 0 || me.getResurrection())
                {
                    sayWait2("The " + me.getClassName() + " tries to use " + me.getSkills()[choice-1] + ", but the surrounding area has not recovered sufficiently yet.\n In a fit of rage, it decides to attack the enemy directly instead!");
                    enemy.takeDamage(me.getAttack()+me.getBuffedAttack());
                    me.increaseHp(0.15*me.getMaxHp());
                }
                break;
            case 4:
                sayWait2("The " + me.getClassName() + " is overcome with " + me.getSkills()[choice-1] + ", increasing it's deadliness even moreso.");
                if (me.getBuffedAttack() < me.getAttack())
                    me.increaseBuffedAttack(0.2*me.getAttack());
                else
                {
                    sayWait("However, it cannot contain such a high amount of power. The energy blasts out in an explosive fashion!");
                    me.takeDamage(0.2*me.getMaxHp());
                    enemy.takeDamage(1.5*me.getAttack()+me.getBuffedAttack());
                    
                }
                break;
            default:
                Combat(enemy, me);
        }
            
        }
    me.bleedDamage();
    me.resCooldownTick();
    }

static void EnemydoAttack(Monster &enemy, Player &me) // Make monster do a random attack. A monster's level determines whether it can or cannot do an attack of that level. If the level is not high enough, it will pick a lower-levelled attack.
{
    int rollem =  arc4random() % enemy.getMobLevel()*10 + 1;
    if (enemy.getMobLevel() >=9 && rollem >90)
    {
        sayWait("The "+ enemy.getName() +" attacked you with its adorableness. Aww.");
        me.takeDamage((0.95*me.getHealth())- me.getBuffedDefense());
    }
    else if ( enemy.getMobLevel() >=8 && rollem >80)
    {
        sayWait("The "+ enemy.getName() +" attacked you with Iron claw.");
        me.takeDamage(2.5* enemy.getAttack() - me.getBuffedDefense());
    }
    else if ( enemy.getMobLevel() >=7 && rollem >70)
    {
        sayWait("The "+ enemy.getName() +" used 'All or Nothing'!");
        rollem = arc4random() % 100 + 1;
        if ( rollem > 50)
        {
            sayWait ("The" + enemy.getName() +" got lucky!");
            me.takeDamage(2.0* enemy.getAttack() - me.getBuffedDefense());
            enemy.increaseHp (0.2 * enemy.getMaxHp());
        }
        else
        {
            sayWait ("The attack of the " + enemy.getName() +" failed.");
            me.takeDamage(0.1* enemy.getAttack() - me.getBuffedDefense());
        }
    }
    else if (  enemy.getMobLevel() >=6 && rollem >60)
    {
        sayWait("The "+ enemy.getName() +" armored up!");
        enemy.increaseDefense (0.25 * enemy.getBaseDefense());
    }
    else if (  enemy.getMobLevel() >=5 && rollem >50)
    {
        sayWait("The " +enemy.getName() + " enters a fiery rage which increases its attack!");
        enemy.increaseAttack (0.15 * enemy.getBaseAttack());
    }
    else if ( enemy.getMobLevel() >=4 && rollem >40)
    {
        sayWait("The " +enemy.getName() + " healed itself.");
        enemy.increaseHp (0.1 * enemy.getMaxHp());
    }
    else if ( enemy.getMobLevel() >=3 && rollem >30)
    {
        sayWait("The " +enemy.getName() + " used Noble Sacrifice.");
        enemy.decreaseHp(0.15*enemy.getHealth());
        me.takeDamage(1.75*enemy.getAttack());
    }
    
    else if (enemy.getMobLevel() >=2 && rollem >20)
    {
        sayWait("The "+ enemy.getName() +" used Sting.");
        me.takeDamage(1.25* enemy.getAttack() - me.getBuffedDefense());
        me.bleed(0.2*enemy.getAttack());
    }
    else
    {
        sayWait("The "+ enemy.getName() +" attacked you with Bite.");
        me.takeDamage(enemy.getAttack() - me.getBuffedDefense());
    }
    enemy.bleedDamage();
    enemy.resCooldownTick();
}

static void Combat(Monster &enemy, Player &me) // Show current battle stats, make the player choose the next action, then perform this action and if applicable make the enemy retaliate.
{
    bool fighting = true;
    while (enemy.getHealth() > 0 || me.getHealth() > 0 || fighting != false)
    {
        clearScreen();
        std::cout << "Your current hitpoints: " + intToString(me.getHealth()) + ".\n";
        std::cout << "The enemy's current hitpoints: " + intToString(enemy.getHealth()) + ".\n";
        std::cout << "Your attack power: " + intToString(me.getAttack()+me.getBuffedAttack()) + ".\n";
        std::cout << "The enemy's defense: " + intToString(enemy.getDefense()) + ".\n";
        int input;
        std::cout << "What type of attack would you like to perform?\n";
        int i = 0;
        for (std::string &skill : me.getSkills())
        {
            i++;
            std::cout << i << ". Use " << skill << ".\n";
        }
        std::cout << "5. Run away.\n";

        std::cin >> input;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            sayWait("You need to enter an integer for this to work.");
        }
        
        else if (input == 5)
        {
            int rollem = arc4random() % 100 + 1;
            if (rollem > 50)
            {
                fighting = false;
                sayWait2("Got away safely!");
                break;
            }
            else
            {
                sayWait2("The enemy catches you off guard as you try to run away!");
                EnemydoAttack(enemy, me);
                if (me.getHealth() <= 0)
                {
                    break;
                }
            }
            
        }
        else
        {
            doAttack(enemy, me, input);
            if (enemy.getHealth() <= 0)
            {
                if (enemy.getResurrection())
                {
                    enemy.resActivate();
                }
                else
                    break;
            }
            EnemydoAttack(enemy, me);
            if (me.getHealth() <= 0)
            {
                if (me.getResurrection())
                {
                    me.resActivate();
                }
                else
                    break;
            }
        }
    }
    
    
    me.resetBuffedStats();
    
    if (me.getHealth() <= 0 && enemy.getHealth() > 0)
    {
        sayWait("You have lost the battle against the fearsome " + enemy.getName() + ". You were never able to see your friends or family again. How you disappeared has always remained a mystery.\nGame over.");
        me.setLiving(false);
        exit(0);
    }
    
    else if (enemy.getHealth() <= 0 && me.getHealth() > 0)
    {
        sayWait("Congratulations. You have beaten the " + enemy.getName() + ".");
        me.clearBleed();
        itemDrop(enemy, me);
    }
    
    else if (enemy.getHealth() > 0 && me.getHealth() > 0)
    {
        //got away!
    }
    
    else
    {
        sayWait("As you are about to land the final hit on the " + enemy.getName() + ", they counter you with a lethal blow. \nYou have defeated the " + enemy.getName() + ", but in doing so have lost your own life.\nGame over.");
        me.setLiving(false);
        exit(0);
    }
}