//
//  main.cpp
//  Axium
//
//  Created by Randy on 17/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//
#include "Combat.cpp"
#include "json/json.h"

Player me;

void initStory();

static void loadChar(std::string path) // Restore stats of a previous character from a JSON file.
{
    path = path + ".sav";
    Json::Reader reader;
    Json::Value character;
    
    if (fexists("out.sav") || fexists("quick.sav"))
    {
        std::fstream loadFile(path);
        
        if (loadFile.fail())
        {
            sayWait("Something went terribly wrong. Presumably the specified file does not exist.");
        }
        
        bool parsingSuccessful = reader.parse(loadFile, character);
        
        if (parsingSuccessful)
        {
            sayWait2("\nYour character has been restored."); // Display a message to say you have loaded a savegame.
            me = *new Player(); // Reset the player
            me.setName(character["name"].asString()); // Set the name.
            if (character["class"] == "Paladin") me.setClass(Paladin); //
            else if (character["class"] == "Commander") me.setClass(Commander); //
            else if (character["class"] == "Ninja") me.setClass(Ninja); //
            else if (character["class"] == "Reaper") me.setClass(Reaper); // Set the class.
            me.setDefense(character["defense"].asInt()); // Set the defense stat.
            me.setAttack(character["attack"].asInt()); // Set the attack stat.
            me.setMaxHp(character["hitpoints"].asInt()); // Set max HP.
            me.setHp(character["currhitpoints"].asInt()); // Set current HP.
            me.setGold(character["gold"].asInt()); // Set amount of gold.
            me.setChapter(character["chapter"].asInt()); // Set chapter player is on.
            for (Json::ValueIterator i = character["items"].begin(); i != character["items"].end(); i++)
            {
                int num = i.index(); // Turn iterator into an int for usage in arrays.
                std::string itemName = character["items"][num].get("name", "unknownItem").asString(); // Set the new item's name.
                std::string itemTypeString = character["items"][num].get("type", "unknownType").asString(); // Set the new item's type (string).
                itemType newItemType = unknownType;
                if (itemTypeString == "attackType") // Use the new item's type string to determine what type it is.
                    newItemType = attackType;
                else if (itemTypeString == "defenseType")
                    newItemType = defenseType;
                else if (itemTypeString == "hitpointsType")
                    newItemType = hitpointsType;
                else if (itemTypeString == "questType")
                    newItemType = questType;
                else
                    newItemType = unknownType;
                
                int itemLevel = character["items"][num].get("level", "unknownItem").asInt(); // Set the new item's level.
                int itemQuantity = character["items"][num].get("quantity", "unknownItem").asInt(); // Set the new item's quantity.
                bool itemStackable = character["items"][num].get("stackable", false).asBool(); // Set whether the item is stackable or not.
                
                Item newItem(itemName, itemLevel, newItemType, itemStackable, itemQuantity); // Create the new item.
                me.acquireItem(newItem); // Make the player acquire the new item.

            }
            me.setSkills(); // Set the Player's skills according to the class they have.
            me.resetBuffedStats(); // Reset the Player's stats to normal values.
            
            if (me.getChapter() == 1) // Return the Player to the chapter they were on.
                initStory();
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

static void quickSave() // Saves stats of a character to a JSON file. (Used for auto-saving.)
{
    Json::StyledStreamWriter writer;
    std::ofstream out("quick.sav");
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
        character["chapter"] = me.getChapter();
    
    writer.write(out, character);
}

static void saveChar() // Saves stats of a character to a JSON file.
{
    Json::StyledStreamWriter writer;
    std::ofstream out("out.sav");
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
    character["chapter"] = me.getChapter();
    
    writer.write(out, character);
}

void goToInn() // Visit an inn, if the player has enough money to afford staying, and if they choose to do so, restore hitpoints to the maximum.
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

void statsMenu() // Show stats for the Player.
{
    if (me.getType() != Reaper)
        std::cout << "Stats for " << me.getName() << ", the young " << me.getClassName() << " :\n";
    else
        std::cout << "Stats for the " << me.getClassName() << " :\n";
    std::cout << "Your current hitpoints: " + intToString(me.getHealth()) + ".\n";
    std::cout << "Your attack power: " + intToString(me.getAttack()) + ".\n";
    std::cout << "Your defensive power: " + intToString(me.getDefense()) + ".\n";
    std::cout << "You currently have " << me.getMoney() << " gold.\n";
    me.showItems();
}

void chapterOneMenu(int option, bool &chapterOne) // Perform an action based on the input previously given.
{
    clearScreen();
    switch (option) { // Use input to determine what to do next.
        case 1:
        {
            int input;
            
            sayWait("An adorable looking little girl approaches you as you attempt to leave the village.");
            sayWait("'Won't you stay with us a little longer?', she says in an innocent tone. \nYou could swear you notice a glint of malice in her eyes as you hesitate.");
            std::cout << "What will your answer be?\n1. Yes.\t\t2. No.\n";
            std::cin >> input;
            
            switch(input)
            {
                case 1:
                {
                    Item tail("Elin's tail", 5, defenseType);
                    Monster Elin("adorable-looking Elin", 150, 5, 20, 9, 90, tail);
                    Combat(Elin, me);
                    if (Elin.getHealth() == 0 && me.getHealth() > 0) chapterOne = false;
                    break;
                }
                case 2:
                    break;
            }
            quickSave();
            break;
        }
        case 2:
            
            statsMenu();
            break;
        case 3:
        {
            Item Excalibur("Excalibur", 40, attackType);
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
            goToInn();
            break;
        }
        case 5:
        {
            Monster zubat;
            Item batTooth("Bat tooth", 0, questType, true); // Create an item to be dropped by the Zubat.
            if (me.getDefense()*2 < me.getAttack())
            {
                zubat = *new Monster("Zubat", me.getMaxHp()*0.35,me.getDefense()*2+2,me.getAttack()*0.5,3, 90, batTooth); // Create the Zubat for the player to fight.
            }
            else
                zubat = *new Monster("Zubat", me.getMaxHp()*0.35,me.getAttack()*0.5,me.getDefense()*0.5+2,3, 90, batTooth); // Create the Zubat for the player to fight.
            
            sayWait2("A bat pops up out of nowhere and decides to get fresh with you!");
            
            Combat(zubat, me); // Start a fight with a predetermined opponent.
            quickSave();
            break;
        }
            
        case 6:
        {
            loadChar("out");
            break;
        }
            
        case 7:
        {
            sayWait2("Quicksaving . . .");
            saveChar();
            break;
        }
        case 9:
            sayWait2("Goodbye!");
            saveChar();
            exit(0);
            break;
        default:
            break;
    }

}

void initStory() // Show the user their options and then await input. Use this input in a function to determine what it does.
{
    bool chapterOne = true;
    while (chapterOne)
    {
        clearScreen(); // Clear the screen.
        int option;
        std::cout << "What would you like to do? Enter the number for the option you would like. \n1. Attempt to leave the village.\t2. View stats and items. \n3. Look around the area for items. \t4. Visit the inn.\n5. Fight the wildlife.\t\t\t6. Load previous save. \n7. Quicksave.\n9. Exit\n"; // Ask the user for input.
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
    
    sayWait("Upon finally leaving the town, you notice a path with a sign that indicates:\n________________________\n|                      |\n|      Colusseum ->    |\n|                      |\n------------------------");
    me.setChapter(2);
}

void tutorialStory()
{
    sayWait("You wake up in a field, supposedly in the world of Axium as previously stated.\nIt is a peaceful-looking area, green with grass all around. In the distance you notice a small village. With nowhere else to turn to, you decide to approach the village.");
    sayWait("However, a stray goblin decides to try its luck and blocks your way. Use your skills as a " + me.getClassName() + "and defeat it!");
    Item classItem; // Create a new item.
    switch(me.getType()) // Change the item's name and values according to the class they are.
    {
        case Paladin:
        {
            classItem = *new Item("Shabby hammer", 5, attackType, false);
            break;
        }
        case Ninja:
        {
            classItem = *new Item("Shabby knife", 5, attackType, false);
            break;
        }
        case Commander:
        {
            classItem = *new Item("Shabby musket", 5, attackType, false);
            break;
        }
        case Reaper:
        {
            classItem = *new Item("Worn scythe", 5, attackType, false);
            break;
        }
    }
    Monster Goblin("Goblin", 100, 2, 10, 2, 100, classItem); // Make a new monster with the provided values. Drops the item that was previously created
    Combat(Goblin, me); // Fight the Goblin that was previously created.
    sayWait("Upon defeating the foul goblin, you dust yourself off and equip your new weapon. You feel empowered and ready to carry on, and immediately soldier on to the nearby village.");
    initStory(); // Continue to the initial story area.
}

void createChar() // Create a new character with base stats after asking the user about the details: name, gender and class.
{
    int input;
    std::string name, gender;
    clearScreen();
    if (me.getName().empty())
    {
        std::cout << "Young adventurer, before we start, pray tell me your name.\n";
        std::cin >> name;
        me.setName(name);
    }
    
    if (me.getGenderType() == unknown)
    {
    std::cout << "Furthermore, are you male or female?\n";
    std::cin >> gender;
    
    if (gender == "Male" || gender == "male")
        me.setGender(male);
    else if (gender == "Female" || gender == "female")
        me.setGender(female);
    else
        me.setGender(male);
    }
    clearScreen();
    switch(me.getGenderType())
    {
        case male:
            sayWait2("Very well. Once again I welcome you to Axium, mister " + me.getName() + ". \nIn the world of Axium, adventurers such as yourself have a choice\nof fighting styles.\nI will show you your options. Choose wisely.");
            break;
        case female:
            sayWait2("Very well. Once again I welcome you to Axium, miss " + me.getName() + ". \nIn the world of Axium, adventurers such as yourself have a choice\nof fighting styles.\nI will show you your options. Choose wisely.");
        case unknown:
            createChar();
            break;
    }
    
    std::cout << "\n1. The Boring Paladin(+DEF)\t\t\t2. The Amateur Ninja(+ATK -DEF)\n3. The Cheap Commander.(+HP)\t\t\t4. The Reaper (+??? -ATK).\n";
    std::cin >> input;
    
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        sayWait("You need to enter an integer for this to work.");
        createChar();
    }
    
    switch (input)
    {
        case 1:
        {
            me.setClass(Paladin);
            me.setSkills();
            sayWait2("You are a boring Paladin. Even tough you can be pretty awesome, most of the time you bore the crap out of people.\nYou use holy attacks, and a massive shield to keep yourself safe at all times.");
            break;
        }
        case 2:
        {
            me.setClass(Ninja);
            me.setSkills();
            sayWait("You are a Ninja. You use awesome ninja skills to silently take out enemies and chop their head off with katanas. But, sadly, you are an amateur, so most of these things you can't even do just yet.");
            break;
        }
        case 3:
        {
            me.setClass(Commander);
            me.setSkills();
            sayWait2("You are a Commander, and a bit of a cheap one at that. You shoot your targets at range, making yourself technically impervious to melee attackers. \nHowever, due to game limitations they will still be able to damage you.\nRegardless, you have some of the most damaging skills of any class and a hefty amount of health. Thus, you are a bit of a cheapass.");
            break;
        }
        case 4:
            me.setClass(Reaper);
            me.setSkills();
            me.setName(me.getClassName());
            clearScreen();
            sayWait2("You have chosen to become a Reaper.\n\nNo other details were supplied.");
            clearScreen();
            break;
            
        default:
            me.setClass(Paladin);
            me.setSkills();
            sayWait2("Because you are so indecisive, you have become a boring Paladin.");
            break;
            
    }
    tutorialStory();
}

void titleScreen() // Show the initial title screen. If a save file is found display the option to continue. If not, or if the user chooses not to continue, immediately create a character.
{
    clearScreen();
    std::string title = "     ___________\n._____l_______l_____.\n||_____/  |  \\_____||\n      /   |   \\\n     /    |    \\\n    /     |     \\\n   /      |      \\\n  /       |       \\\n /        |        \\\n|         |         |\n \\        |        /\n   \\      |      /\n     \\    |    /\n       \\  |  /\n         \\|/\n          `\n";
    
    if (!fexists("out.sav") && !fexists("quick.sav"))
    {
        title +="\t\t\tWelcome to Axium, brave warrior.\nYou have been summoned to this world to save us from the evils that lurk around.";
        sayWait(title);
        createChar();
    }
    else if (fexists("out.sav") || fexists("quick.sav"))
    {
        int input;
        title +="\t\t\tWelcome back to Axium, brave warrior.\n";
        title +="Would you like to continue your previous character's story?\n";
        title +="1. Load Quicksave (latest save).\t\t2. Load save file #1.\n9. New game\n";
        std::cout << title;
        std::cin >> input;
        
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000,'\n');
            sayWait("You need to enter an integer for this to work.");
            titleScreen();
        }
        else
        {
            if (input == 1)
            {
                clearScreen();
                loadChar("out");
            }
            else if (input == 2)
            {
                clearScreen();
                loadChar("quick");
            }
            else if (input == 9)
            {
                clearScreen();
                sayWait2("\n\nThis will be a story not to be forgotten so easily.\nIf you think you are ready to handle the pressure, follow the instructions on your screen now.");
                createChar();
            }
            
        }
    }
}


int main(int argc, const char * argv[])
{
    titleScreen();
    sayWait("You have reached the end of the game. Thank you for playing!");
    return 0;
}
