//
//  Items.h
//  Axium
//
//  Created by Randy on 06/03/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#ifndef __Axium__Items__
#define __Axium__Items__
#include "includes.h"
enum itemType
{
    attackType, defenseType, hitpointsType, questType, unknownType
};

class Item
{
    itemType itemKind = unknownType;
    std::string name;
    int itemLevel, quantity = 1;
    bool stackable = false;;
    
public:
    bool operator ==(const Item &Right) const
    {
        return (name == Right.name) && (itemKind == Right.itemKind);
    }
    
    Item();
    Item(std::string name);
    Item(std::string name, bool stackable);
    Item(std::string name, int iLVL);
    Item(std::string name, int iLVL, itemType itemKind);
    Item(std::string name, int iLVL, itemType itemKind, bool stackable);
    Item(std::string name, int iLVL, itemType itemKind, bool stackable, int quantity);
    
    itemType getType() {return this->itemKind;}
    std::string getTypeString()
    {
        switch(this->itemKind)
        {
            case attackType:
                return "attackType";
            case defenseType:
                return "defenseType";
            case hitpointsType:
                return "hitpointsType";
            case questType:
                return "questType";
            case unknownType:
                return "unknownType";
        }
    }
    std::string getName() {return this->name;}
    int getLevel() {return this->itemLevel;}
    int getQuantity() {return this->quantity;}
    void increaseQuantity() {if (this->stackable) this->quantity++;}
    bool isStackable() {return this->stackable;}
};

#endif /* defined(__Axium__Items__) */
