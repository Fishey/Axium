//
//  Player.cpp
//  Axium
//
//  Created by Randy on 19/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Player.h"
#include <stdlib.h>     /* srand, rand */

class Player
{
    gender genderType;
    std::string name, type;
    int karma = arc4random() % 100 + 1;
public:
    std::string getName() {return this->name;};
    std::string getType() {return this->type;};
    int getKarma() {return this->karma;};
    void setName(std::string name);
};


//Looking for a way to make this work on a Mac, but just causes errors for now.
/*
void Player::setName(std::string name)
{
    this->name = name;
}

std::string Player::getName()
{
    return this->name;
}

std::string Player::getType()
{
    return this->type;
}

int Player::getKarma()
{
    return this->karma;
}
*/