//
//  Player.cpp
//  Axium
//
//  Created by Randy on 19/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Player.h"
class Player
{
    std::string name, type;
    int karma;
public:
    std::string getName() {return this->name;};
    std::string getType() {return this->type;};
    int getKarma() {return this->karma;};
    void setName(std::string name) {this->name = name;};
};


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