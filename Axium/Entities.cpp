//
//  Entities.cpp
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Entities.h"

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
        this->hitpoints = (hitpoints - (damage - defense));
        std::string output = this->getName() + " took " + intToString((damage - defense)) + " damage.";
        sayWait(output);
    }
    void Entity::increaseHp (int hp) {
        if (this->hitpoints + hp < maxhp) this->hitpoints += hp;
        else this->hitpoints = maxhp;
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
        std::cout << "You have a " + it->getName() + " already.";
        if (it->isStackable())
        {
            it->increaseQuantity();
        }
    }

    Monster::Monster(std::string name, int hitpoints, int defense, int attack, int mobLevel, int dropRate, Item droppedItem)
    {
        this->name = name; this->hitpoints = hitpoints; this->defense = defense; this->attack = attack; this->mobLevel = mobLevel; this->droppedItem = droppedItem; this->dropRate = dropRate;
    };

    Player::Player()
    {
        this->attack = 10; this->defense = 0; this->hitpoints = 100; this->maxhp = 100;
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
        for (Item &item : this->items)
        {
            i++;
            std::cout << intToString(item.getQuantity()) + " of " "Item # " + intToString(i) + " : " + item.getName() + "\n";
        }
        sayWait("");
        std::cin.ignore(1);
    }