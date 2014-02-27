//
//  Entities.cpp
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Entities.h"
#include "includes.h"
class Entity
{
protected:
    gender genderType;
    std::string name, type;
    int karma = arc4random() % 100 + 1, hitpoints, defense, attack, maxhp;
public:
    std::string getName() {return this->name;}
    std::string getType() {return this->type;}
    std::string getGender() {if(this->genderType == male) return "male"; else if (this->genderType == female) return "female"; else return "unknown";}
    gender getGenderType() {return this->genderType;}
    int getKarma() {return this->karma;}
    int getAttack() {return this->attack;}
    int getHealth() {return this->hitpoints;}
    int getDefense() {return this->defense;}
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
    void increaseHp (int hp) {this->hitpoints += hp;}
};

class Monster : public Entity
{
private:
    int itemLevel;
public:
    Monster(std::string name, int hitpoints, int defense, int attack, int ilvl)
    {
        this->name = name; this->hitpoints = hitpoints; this->defense = defense; this->attack = attack; this->itemLevel = ilvl;
    }
    int getItemLevel() {return itemLevel;}
    
};

class Player : public Entity
{
public: 
    Player()
    {
        this->attack = 10; this->defense = 0; this->hitpoints = 100; this->maxhp = 100;
    }
};
