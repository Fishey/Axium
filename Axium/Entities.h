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
enum gender {male, female, unknown};
enum type {Paladin, Ninja, Commander, Reaper};

class Entity
{
    protected:
        bool alive, bleeding, resurrect;
        gender genderType;
        std::string name;
        std::vector<Item> items;
        std::vector<std::string> skills;
        int karma = arc4random() % 100 + 1, hitpoints, defense, attack, maxhp, money, bleedStrength, bleedCounter, buffedAttack, buffedDefense, resCooldown;
    public:
        std::string getName() {return this->name;}
        std::string getGender() {if(this->genderType == male) return "male"; else if (this->genderType == female) return "female"; else return "unknown";}
        std::string getGenderText() {if(this->genderType == male) return "his"; else if (this->genderType == female) return "her"; else return "their";}
        gender getGenderType() {return this->genderType;}
        bool getResurrection() {return this->resurrect;}
        bool getLiving() {return this->alive;}
        bool getBleeding() {return this->bleeding;}
        int getResCooldown() {return this->resCooldown;}
        int getKarma() {return this->karma;}
        int getMoney() {return this->money;}
        int getAttack();
        int getBaseAttack(){return this->attack;}
        int getBaseDefense(){return this->defense;}
        int getBuffedAttack(){return this->buffedAttack;}
        int getBuffedDefense(){return this->buffedDefense;}
        int getHealth() {return this->hitpoints;}
        int getDefense();
        int getMaxHp() {return this->maxhp;}
        std::vector<Item> getItems() {return this->items;}
        std::vector<std::string> itemList();
        void bleed(int strength);
        void bleedDamage();
        void clearBleed();
        void restoreHealth();
        void setHp(int hp) {this->hitpoints = hp;}
        void setSkills();
        void setLiving(bool living){this->alive = living;}
        void setName(std::string name) {this->name = name;}
        void setAttack(int attack) {this->attack = attack;}
        void setDefense(int defense) {this->defense = defense;}
        void setMaxHp(int maxhp) {this->maxhp = maxhp; this->hitpoints = maxhp;}
        void setGold(int money) {this->money = money;}
        void setGender(gender gender){this->genderType = gender;}
        void takeDamage(int damage);
        void decreaseHp (int hp);
        void increaseHp (int hp);
        void increaseDefense (int defense) {this->defense += defense;}
        void increaseAttack (int attack);
        void increaseBuffedDefense(int defense) {this->buffedDefense += defense;}
        void increaseBuffedAttack(int attack) {this->buffedAttack += attack;}
        void increaseMaxHp (int hp) {this-> maxhp += hp; this->hitpoints += hp;}
        void resCooldownTick() {if (this->resCooldown > 0) this->resCooldown--;}
        void resActivate()
        {
            this->resurrect = false;
            this->hitpoints = 0.3*this->maxhp;
            if (this->name != "Reaper")
                sayWait(this->name + "'s resurrection ability allowed them to recover " + intToString(0.3 * this->maxhp) + " health.");
            else
                sayWait("The " + name + "'s surroundings turn crimson as the energy it absorbed gets unleashed again, restoring " + intToString(0.3 * this->maxhp) + " of it's health.");
        }
        void setResurrection()
        {
            this->resurrect = true;
            this->resCooldown = 3;
        }
        void resetBuffedStats();
        void findIncreaseItem(Item searchItem);
        bool hasItem(std::string itemName);

};

class Monster : public Entity
{
private:
    int mobLevel, dropRate;
    Item droppedItem;
public:
    Monster() {};
    Monster(std::string name, int hitpoints, int defense, int attack, int mobLevel, int dropRate, Item droppedItem);

    int getMobLevel() {return mobLevel;}
    int getItemLevel() {return droppedItem.getLevel();}
    int getDropRate() {return dropRate;}
    Item getDroppedItem() {return droppedItem;}
    std::string getDroppedItemName() {return droppedItem.getName();}
    
};

class Player : public Entity
{
private:
    int chapter;
    type classType;
public:
    Player();
    type getType() {return this->classType;}
    void acquireMoney(int money) {
        if(money > 0)sayWait("You have also acquired " + intToString(money) + " gold.");
        if(money < 0)sayWait2("You have spent " + intToString(-money) + " gold.");
        this->money += money;}
    void acquireItem(Item item);
    void setSkills();
    std::vector<std::string> getSkills(){return this->skills;}
    std::string getClassName();
    void showItems();
    void setClass(type classType);
    void setChapter(int chapter){this->chapter = chapter;}
    int getChapter() {return this->chapter;}
};


#endif /* defined(__Axium__Entities__) */