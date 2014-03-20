//
//  Entities.h
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#ifndef __Axium__Entities__
#define __Axium__Entities__
#include "Items.h"
#include <algorithm>
enum gender {male, female};

class Entity
{
    protected:
        bool alive;
        gender genderType;
        std::string name, type;
        std::vector<Item> items;
        int karma = arc4random() % 100 + 1, hitpoints, defense, attack, maxhp, money;
    public:
        std::string getName() {return this->name;}
        std::string getType() {return this->type;}
        std::string getGender() {if(this->genderType == male) return "male"; else if (this->genderType == female) return "female"; else return "unknown";}
        std::string getGenderText() {if(this->genderType == male) return "his"; else if (this->genderType == female) return "her"; else return "their";}
        gender getGenderType() {return this->genderType;}
        bool getLiving() {return this->alive;}
        int getKarma() {return this->karma;}
        int getMoney() {return this->money;}
        int getAttack();
        int getHealth() {return this->hitpoints;}
        int getDefense();
        std::vector<std::string> itemList();
        void restoreHealth();
        void setLiving(bool living){this->alive = living;}
        void setName(std::string name) {this->name = name;}
        void setAttack(int attack) {this->attack = attack;}
        void setDefense(int defense) {this->defense = defense;}
        void takeDamage(int damage);
        void increaseHp (int hp);
        void increaseDefense (int defense) {this->defense += defense;}
        void increaseAttack (int attack) {this-> attack += attack;}
        void increaseMaxHp (int hp) {this-> maxhp += hp; this->hitpoints += hp;}
        void findIncreaseItem(Item searchItem);
        bool hasItem(std::string itemName);

};

class Monster : public Entity
{
private:
    int mobLevel, dropRate;
    Item droppedItem;
public:
    Monster(std::string name, int hitpoints, int defense, int attack, int mobLevel, int dropRate, Item droppedItem);

    int getMobLevel() {return mobLevel;}
    int getItemLevel() {return droppedItem.getLevel();}
    int getDropRate() {return dropRate;}
    Item getDroppedItem() {return droppedItem;}
    std::string getDroppedItemName() {return droppedItem.getName();}
    
};

class Player : public Entity
{
public:
    Player();
    void acquireMoney(int money) {
        if(money > 0)sayWait("You have also acquired " + intToString(money) + " gold.");
        if(money < 0)sayWait("You have spent " + intToString(money) + " gold.");
        this->money += money;}
    void acquireItem(Item item);
    void showItems();
};


#endif /* defined(__Axium__Entities__) */