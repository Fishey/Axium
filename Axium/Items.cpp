//
//  Items.cpp
//  Axium
//
//  Created by Randy on 06/03/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Items.h"
enum itemType
{
    attackType, defenseType, hitpointsType, questType, unknownType
};
class Item
{
    itemType itemKind;
    std::string name;
    int itemLevel, quantity;
    bool stackable = false;;
    
public:
    Item()
    {
        this->itemLevel = 0;
        this->name = "unknown";
    }
    Item(std::string name)
    {
        this->itemLevel = 0;
        this->name = name;
    }
    Item(std::string name, bool stackable)
    {
        this->stackable = stackable;
    }
    Item(std::string name, int iLVL)
    {
        this->itemLevel = iLVL;
        this->name = name;
    }
    Item(std::string name, int iLVL, itemType itemKind)
    {
        this->itemLevel = iLVL;
        this->name = name;
        this->itemKind = itemKind;
    }
    
    itemType getType() {return this->itemKind;}
    std::string getName() {return this->name;}
    int getLevel() {return this->itemLevel;}
    int getQuantity() {return this->quantity;}
    };