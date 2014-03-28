//
//  main.cpp
//  Axium
//
//  Created by Randy on 17/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//
#include "Combat.cpp"
#include "json/writer.h"
#include "json/json.h"

Player me;

static void loadChar()
{
    Json::Reader reader;
    Json::Value character;
    if (fexists("out.json"))
    {
        std::fstream loadFile("out.json");
        
        if (loadFile.fail())
        {
            sayWait("Something went terribly wrong. Presumably the specified file does not exist.");
        }
        
        bool parsingSuccessful = reader.parse(loadFile, character);
        
        if (parsingSuccessful)
        {
            me = *new Player();
            if (character["class"] == "Paladin") me.setClass(Paladin);
            else if (character["class"] == "Commander") me.setClass(Commander);
            else if (character["class"] == "Ninja") me.setClass(Ninja);
            me.setDefense(character["defense"].asInt());
            me.setAttack(character["attack"].asInt());
            me.setName(character["name"].asString());
            me.setMaxHp(character["hitpoints"].asInt());
            me.setHp(character["currhitpoints"].asInt());
            me.setGold(character["gold"].asInt());
            for (Json::ValueIterator i = character["items"].begin(); i != character["items"].end(); i++)
            {
                int num = i.index();
                std::string itemName = character["items"][num].get("name", "unknownItem").asString();
                std::string itemTypeString = character["items"][num].get("type", "unknownType").asString();
                itemType newItemType = unknownType;
                if (itemTypeString == "attackType")
                    newItemType = attackType;
                else if (itemTypeString == "defenseType")
                    newItemType = defenseType;
                else if (itemTypeString == "hitpointsType")
                    newItemType = hitpointsType;
                else if (itemTypeString == "questType")
                    newItemType = questType;
                else
                    newItemType = unknownType;
                
                int itemLevel = character["items"][num].get("level", "unknownItem").asInt();
                int itemQuantity = character["items"][num].get("quantity", "unknownItem").asInt();
                bool itemStackable = character["items"][num].get("stackable", false).asBool();
                
                Item newItem(itemName, itemLevel, newItemType, itemStackable, itemQuantity);
                me.acquireItem(newItem);

            }
            me.setSkills();
            
            sayWait2("Your character has been restored.");
        }
        else
        {
            sayWait2("Something went wrong while parsing the file. Check below for details.");
            
            std::cout << reader.getFormatedErrorMessages();
        }
    }
    else
    {
        sayWait2("No save file was found.");
    }
}


static void saveChar(int chapter)
{
    Json::StyledStreamWriter writer;
    std::ofstream out("out.json");
    Json::Value character;
    character["name"] = me.getName();
    character["class"] = me.getClassName();
    character["hitpoints"] = me.getMaxHp();
    character["currhitpoints"] = me.getHealth();
    character["attack"] = me.getBaseAttack();
    character["defense"] = me.getBaseDefense();
    character["gold"] = me.getMoney();
    for(std::vector<Item>::size_type i = 0; i != me.getItems().size(); i++)
    {
        Json::Value thisNewItem;
        
        thisNewItem["name"] = me.getItems()[i].getName();
        thisNewItem["type"] = me.getItems()[i].getTypeString();
        thisNewItem["level"] = me.getItems()[i].getLevel();
        thisNewItem["quantity"] = me.getItems()[i].getQuantity();
        thisNewItem["stackable"] = me.getItems()[i].isStackable();
        
        character["items"].append(thisNewItem);
    }
    character["chapter"] = chapter;
    
    writer.write(out, character);
}


void titleScreen()
{
    clearScreen();
    std::string title = "     ___________\n._____l_______l_____.\n||_____/  |  \\_____||\n      /   |   \\\n     /    |    \\\n    /     |     \\\n   /      |      \\\n  /       |       \\\n /        |        \\\n|         |         |\n \\        |        /\n   \\      |      /\n     \\    |    /\n       \\  |  /\n         \\|/\n          `\n";
    
    title +="\t\t\tWelcome to Axium, brave warrior.\n\nThis will be a story not to be forgotten so easily.\nIf you think you are ready to handle the pressure, follow the instructions on your screen now.\n\n";
    sayWait(title);
}

void goToInn()
{
    clearScreen();
    int input;
    std::cout <<"You enter the inn.\n";
    std::cout << "It costs 5 gold to use the inn. You currently have " << me.getMoney() << " gold. \nWould you like to stay the night?\n1. Yes\t\t\t\t\t 2. No\n";
    std::cin >> input;
    
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        sayWait("You need to enter an integer for this to work.");
        goToInn();
    }
    
    if (input == 1 && me.getHealth() == me.getMaxHp())
    {
        sayWait2("The innkeep notices you are still perfectly healthy, and politely asks you to come again some other time.");
    }
    else if (input == 1 && me.getMoney() >= 5 && me.getHealth() < me.getMaxHp())
    {
        me.acquireMoney(-5);
        me.restoreHealth();
    }
    else if (input == 1 && me.getMoney() < 5)
    {
        sayWait2("You can't afford to do that!");
    }
    else if (input == 2)
    {
        sayWait2("You leave the inn, disgusted by the obscenely priced services it offers.");
    }
}

void statsMenu()
{
    std::cout << "Stats for " << me.getName() << ", the young " << me.getClassName() << " :\n";
    std::cout << "Your current hitpoints: " + intToString(me.getHealth()) + ".\n";
    std::cout << "Your attack power: " + intToString(me.getAttack()) + ".\n";
    std::cout << "Your defensive power: " + intToString(me.getDefense()) + ".\n";
    std::cout << "You currently have " << me.getMoney() << " gold.\n";
    me.showItems();
}

void chapterOneMenu(int option, bool &chapterOne)
{
    switch (option) { // Use input to determine what to do next.
        case 1:
        {
            clearScreen();
            Item batTooth("Bat tooth", 0, questType, true); // Create an item to be dropped by the Zubat.
            Monster zubat("Zubat", 15,5,5,1, 90, batTooth); // Create the Zubat for the player to fight.
            std::cout <<"A bat pops up out of nowhere and decides to get fresh with you!\nPress enter to continue . . .";
            std::cin.ignore(2); // Say a line of text and wait for the user to press the Enter key.
            Combat(zubat, me); // Start a fight with a predetermined opponent. The return value determines whether the program continues running.
            break;
        }
        case 2:
            clearScreen();
            statsMenu();
            break;
        case 3:
        {
            clearScreen();
            Item Excalibur("Excalibur", 10, attackType);
            Item Hecate("Hecate II", 10, attackType);

            if (!me.hasItem(Excalibur.getName()) && me.getType() != Commander)
            {
                sayWait2("Looking around, you notice a faintly glowing sword sticking out from a rock in the middle of nowhere. \nMaking great use of the opportunity, you take the blade. \nYou have acquired the mighty blade Excalibur!");
                me.acquireItem(Excalibur);
            }
            else if (!me.hasItem(Hecate.getName()) && me.getType() == Commander)
            {
                sayWait2("Looking around, you notice a large rifle laying on the ground in the middle of nowhere. \nMaking great use of the opportunity, you take the gun. \nYou have acquired the mighty gun Hecate II!");
                me.acquireItem(Hecate);
            }
            else
            {
                sayWait2("You look around for any more items, but sadly, there aren't any.");
            }
            break;
        }
        case 4:
        {
            clearScreen();
            goToInn();
            break;
        }
        case 5:
        {
            Item loot("Hobo's coat", 5, defenseType);
            Monster destroyer("defenseless hobo", 100, 5, 15, 4, 90, loot);
            Combat(destroyer, me);
            break;
        }
            
        case 6:
        {
            loadChar();
            break;
        }
        case 9:
            sayWait2("Goodbye!");
            saveChar(1);
            exit(0);
            break;
        default:
            break;
    }

}

void initStory()
{
    int input;
    std::cout << " what will be your class young adventurer?. \n 1. the boring paladin, \n 2. the amateur ninja, \n 3. the cheap commander. ";
    std::cin >> input;
    switch (input)
    {
        case 1:
        {
            me.setClass(Paladin);
            sayWait2("you are a boring Paladin even tough you can be pretty awesome most of the time you bore the crap out of people");
            me.setSkills();
            break;
        }
        case 2:
        {
            me.setClass(Ninja);
            me.setSkills();
            sayWait2(" you are a ninja. you use awesome ninja skills to silently take out enemys and chop there head of with katana,s. But you are a amateur so most of these things you can't even do ");
            break;
        }
        case 3:
        {
            me.setClass(Commander);
            me.setSkills();
            sayWait2(" you are a cheap ass moterfucking commander. even tough you use guns they are not as effective as you might think. So even tough you are not as cheap ass as people say, you are still cheapass ");
            break;
        }
            
        default:
            me.setClass(Paladin);
            me.setSkills();
            sayWait2("Because you are so indecisive, you have become a boring Paladin.");
            break;
            
    }
    bool chapterOne = true;
    me.setName("You");
    while (chapterOne)
    {
        clearScreen(); // Clear the screen.
        int option;
        std::cout << "What would you like to do? Enter the number for the option you would like. \n1. Fight. \t\t\t\t 2. View stats and items. \n3. Look around the area for items. \t 4. Visit the inn.\n5. Fight an unspeakable boss monster.\t6. Load previous character. \n9. Exit\n"; // Ask the user for input.
        std::cin >> option; // Wait for input.
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            sayWait("You need to enter an integer for this to work.");
        }
        else {
            chapterOneMenu(option, chapterOne);
        }
    }
}

int main(int argc, const char * argv[])
{
    titleScreen();
    initStory();
    sayWait("The next area is full of unicorns and rainbows. What will you do now?");
    return 0;
}
