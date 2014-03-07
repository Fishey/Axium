//
//  Entities.cpp
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Entities.h"
#include "Items.cpp"
#include "includes.h"

class Entity
{
protected:
    gender genderType;
    std::string name, type;
    std::vector<Item> items;
    int karma = arc4random() % 100 + 1, hitpoints, defense, attack, maxhp;
public:
    std::string getName() {return this->name;}
    std::string getType() {return this->type;}
    std::string getGender() {if(this->genderType == male) return "male"; else if (this->genderType == female) return "female"; else return "unknown";}
    gender getGenderType() {return this->genderType;}
    int getKarma() {return this->karma;}
    int getAttack() {
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
    int getHealth() {return this->hitpoints;}
    int getDefense() {
        if (items.empty())
        {
            return this->defense;
        }
        else
        {
            int tempDefense = this->defense;
            for (Item &item : this->items)
            {
                if (item.getType() == attackType)
                    tempDefense += item.getLevel();
            }
            return tempDefense;
        }
    }
    std::vector<std::string> itemList()
    {
        std::vector<std::string> allItems;
        for (Item &item : this->items)
        {
            allItems.push_back(item.getName());
        }
        return allItems;
    }
    void setName(std::string name) {this->name = name;}
    void setAttack(int attack) {this->attack = attack;}
    void setDefense(int defense) {this->defense = defense;}
    void takeDamage(int damage)
    {
        this->hitpoints = (hitpoints - (damage - defense));
        std::string output = this->getName() + " took " + intToString((damage - defense)) + " damage.";
        sayWait(output);
    }
    void increaseDefense (int defense) {this->defense += defense;}
    void increaseAttack (int attack) {this-> attack += attack;}
    void increaseMaxHp (int hp) {this-> maxhp += hp; this->hitpoints += hp;}
    void increaseHp (int hp) {
        if (this->hitpoints + hp < maxhp) this->hitpoints += hp;
        else this->hitpoints = maxhp;
    }
    bool hasItem(std::string itemName)
    {
        std::vector<std::string> itemNames = itemList();
        if (std::find(itemNames.begin(), itemNames.end(), itemName) != itemNames.end())
        return true;
        else return false;
    }
    
   /* Item findItem(std::string itemName)
    {
       if (std::find(itemList().begin(), itemList().end(), itemName) != itemList().end())
       {
           return itemList().end();
       }
    } */ // WIP
};

class Monster : public Entity
{
private:
    int mobLevel, dropRate;
    Item droppedItem;
public:
    Monster(std::string name, int hitpoints, int defense, int attack, int mobLevel, int dropRate, Item droppedItem)
    {
        this->name = name; this->hitpoints = hitpoints; this->defense = defense; this->attack = attack; this->mobLevel = mobLevel; this->droppedItem = droppedItem; this->dropRate = dropRate;
    }
    int getMobLevel() {return mobLevel;}
    int getItemLevel() {return droppedItem.getLevel();}
    int getDropRate() {return dropRate;}
    Item getDroppedItem() {return droppedItem;}
    std::string getDroppedItemName() {return droppedItem.getName();}
    
};

class Player : public Entity
{
public:
    Player()
    {
        this->attack = 10; this->defense = 0; this->hitpoints = 100; this->maxhp = 100;
    }
    
    void acquireItem(Item item) {
        if (!hasItem(item.getName()))
        this->items.push_back(item);
        else
        {
            //lookup item
            //add 1 to item quantity
            //WIP
        }
    }
    void showItems()
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
};
