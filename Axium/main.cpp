//
//  main.cpp
//  Axium
//
//  Created by Randy on 17/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//
#include "Combat.c"
Player me;
Monster zubat("Zubat", 15,5,5,1);

void initStory()
{
    me.setName("You");
    clearScreen(); // Clear the screen.
    sayWait("A bat pops up out of nowhere and decides to get fresh with you!"); // Say a line of text and wait for the user to press the Enter key.
    Combat(zubat, me); // Start a fight with a predetermined opponent.
}

int main(int argc, const char * argv[])
{
    initStory();
    return 0;
}