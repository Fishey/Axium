//
//  Entities.cpp
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Entities.h"

    void Entity::restoreHealth()
    {
        sayWait("Your health has been fully restored.");
        this->hitpoints = this->maxhp;
    }
    int Entity::getAttack() {
        if (items.empty())
        {
        return this->attack;
        }
        else
        {
            int tempAttack = this->attack;
            for (Item &item : this->items)
            {
                if (item.getType() == attackType)
                    tempAttack += item.getLevel();
            }
            return tempAttack;
        }
    }
    int Entity::getDefense() {
        if (items.empty())
        {
            return this->defense;
        }
        else
        {
            int tempDefense = this->defense;
            for (Item &item : this->items)
            {
                if (item.getType() == defenseType)
                    tempDefense += item.getLevel();
            }
            return tempDefense;
        }
    }
    std::vector<std::string> Entity::itemList()
    {
        std::vector<std::string> allItems;
        for (Item &item : this->items)
        {
            allItems.push_back(item.getName());
        }
        return allItems;
    }
    void Entity::takeDamage(int damage)
    {
        if ((damage - defense) >= 0)
        {
            this->hitpoints = (hitpoints - (damage - defense));
            std::string capitalized = this->getName();
            capitalized[0] = toupper(capitalized[0]);
            sayWait(capitalized + " took " + intToString((damage - defense)) + " damage.");
        }
        else if ((damage - defense) < 0)
        {
            if(((hitpoints - (damage - defense)) < maxhp))
            {
                sayWait("The blow glances off the target, allowing it to heal for " + intToString(-(damage-defense)) + " hitpoints!");

               this->hitpoints = (hitpoints - (damage - defense));
            }
            else
            {
                sayWait("The blow glances off the target, allowing it to heal back to full hitpoints!");

                this->hitpoints = this->maxhp;
            }
        }


    }
    void Entity::increaseHp (int hp) {
        if (this->hitpoints + hp < maxhp)
        {
            this->hitpoints += hp;
            sayWait("You have recovered " + intToString(hp) + " hitpoints.");
        }

        else
        {
            this->hitpoints = maxhp;
        }
    }
    bool Entity::hasItem(std::string itemName)
    {
        std::vector<std::string> itemNames = itemList();
        if (std::find(itemNames.begin(), itemNames.end(), itemName) != itemNames.end())
        return true;
        else return false;
    }
    
    void Entity::findIncreaseItem(Item searchItem)
    {
        std::vector<Item>::iterator it = std::find (items.begin(), items.end(), searchItem);
        if (it->isStackable())
        {
            it->increaseQuantity();
        }
    }

    Monster::Monster(std::string name, int hitpoints, int defense, int attack, int mobLevel, int dropRate, Item droppedItem)
    {
        this->name = name; this->hitpoints = hitpoints; this->maxhp = this->hitpoints; this->defense = defense; this->attack = attack; this->mobLevel = mobLevel; this->droppedItem = droppedItem; this->dropRate = dropRate; this->money = arc4random() % mobLevel + 1;
    };

    Player::Player()
    {
        this->attack = 10; this->defense = 0; this->hitpoints = 100; this->maxhp = 100; this->money = 0; this->alive = true;
    };

    
    
    void Player::acquireItem(Item item) {
        if (!hasItem(item.getName()))
        this->items.push_back(item);
        else
        {
            findIncreaseItem(item);
        }
    }
    void Player::showItems()
    {
        int i = 0;
        if (!items.empty())
        {
            for (Item &item : this->items)
            {
                i++;
                if (item.getQuantity() > 1) std::cout << intToString(item.getQuantity()) + " of ";
                std::cout << "Item # " + intToString(i) + " : " + item.getName();
                if (item.getType() == defenseType) std::cout << "\t\tIncreases your defensive power by " << item.getLevel() << "\n";
                else if (item.getType() == attackType) std::cout << "\t\tIncreases your attack power by " << item.getLevel() << "\n";
                else std::cout << "\n";
            }
            sayWait("");
        }
        else
        {
            sayWait("You don't currently have any items.\n");
        }
        std::cin.ignore(1);
    }

void Player::setClass(type classType)
{
    this->classType = classType;
    switch (classType) {
        case Paladin:
            this->increaseDefense(5);
            this->increaseMaxHp(20);
            break;
        case Ninja:
            this->increaseAttack(5);
            this->increaseMaxHp(-20);
            break;
        case Commander:
            this->increaseMaxHp(50);
            break;
            
        default:
            break;
    }
}

void Entity::setSkills()
{
    // do nothing
}

void Player::setSkills()
{
    if (this->getType() == Paladin)
    {
        this->skills.push_back("Holy Recovery");
        this->skills.push_back("Heavy Damage");
        this->skills.push_back("'Perfect' Defense");
        this->skills.push_back("Divine Retribution");
    }
    
    else if (this->getType() == Ninja)
    {
        this->skills.push_back("Ninja's Blood Draw");
        this->skills.push_back("Measured Slice");
        this->skills.push_back("Shadow Clone");
        this->skills.push_back("Ninja's Sacrifice");
    }
    
    else if (this->getType() == Commander)
    {
        this->skills.push_back("Blood-stained Shells");
        this->skills.push_back("Explosive Bulletstorm");
        this->skills.push_back("Tactical Dive");
        this->skills.push_back("Opportunistic Snipe");
    }
    else
    {
        this->skills.push_back("You");
        this->skills.push_back("haven't selected");
        this->skills.push_back("a class");
        this->skills.push_back("you fool!");
    }
}

std::string Player::getClassName()
{
    switch (this->classType) {
        case Paladin:
            return "Paladin";
            break;
        case Ninja:
            return "Ninja";
            break;
        case Commander:
            return "Commander";
        default:
            break;
    }
}