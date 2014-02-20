//
//  main.cpp
//  Axium
//
//  Created by Randy on 17/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include <iostream>
#include "includes.h"
void initStory();

int main(int argc, const char * argv[])
{
    initStory();
    return 0;
}

void initStory()
{
    std::string name;
    std::cout << "Hello player. Welcome to the world of Axium.\n";
    std::cout << "The world of Axium is controlled by three major empires. \nYour family was once one of the strongest in all of the lands. Reigning over large amounts of land, with strict but respectful mannerisms for as long as they lasted.\n";
    std::cout << "However, one day the other empires plotted an evil conspiracy; they decided your family line had lived long enough.";
    std::cout << "The events that happened afterwards have paved the way for your story.\n";
    std::cout << "Will you enact revenge, striking every one of your enemies down on your way to show the power of your family line? Or will you show mercy and teach your enemies the errors of their ways? The choice is yours.\n\n";
    std::cout << "To begin your story, first of all, enter your name.\n";
    std::cin >> name;
    me.setName(name);
    
    std::cout << "Welcome, brave adventurer " + me.getName() + ".";
}