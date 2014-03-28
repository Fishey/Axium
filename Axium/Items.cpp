//
//  Items.cpp
//  Axium
//
//  Created by Randy on 06/03/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//
#include "Items.h"

Item::Item()
    {
        this->itemLevel = 0;
        this->name = "unknown";
    }
Item::Item(std::string name)
    {
        this->itemLevel = 0;
        this->name = name;
    }
Item::Item(std::string name, bool stackable)
    {
        this->name = name;
        this->stackable = stackable;
    }
Item::Item(std::string name, int iLVL)
    {
        this->itemLevel = iLVL;
        this->name = name;
    }
Item::Item(std::string name, int iLVL, itemType itemKind)
    {
        this->itemLevel = iLVL;
        this->name = name;
        this->itemKind = itemKind;
    }
Item::Item(std::string name, int iLVL, itemType itemKind, bool stackable)
    {
        this->itemLevel = iLVL;
        this->name = name;
        this->itemKind = itemKind;
        this->stackable = stackable;
    }
Item::Item(std::string name, int iLVL, itemType itemKind, bool stackable, int quantity)
{
    this->itemLevel = iLVL;
    this->name = name;
    this->itemKind = itemKind;
    this->stackable = stackable;
    this->quantity = quantity;
}