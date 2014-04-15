//
//  Entities.cpp
//  Axium
//
//  Created by Randy on 26/02/14.
//  Copyright (c) 2014 Randy. All rights reserved.
//

#include "Entities.h"

    void Entity::restoreHealth() // Restore hitpoints to the maximum.
    {
        sayWait("Your health has been fully restored.");
        this->hitpoints = this->maxhp;
    }
    int Entity::getAttack() // Return the total amount of Attack power of a player or monster. Takes into account any items they have equipped.
    {
        if (items.empty())
        {
        return this->attack;
        }
        else
        {
            int tempAttack = this->attack;
            for (Item &item : this->items)
            {
                if (item.getType() == attackType)
                    tempAttack += item.getLevel();
            }
            return tempAttack;
        }
    }
    int Entity::getDefense() // Return the total amount of Defense of a player or monster. Takes into account any items they have equipped.
    {
        if (items.empty())
        {
            return this->defense;
        }
        else
        {
            int tempDefense = this->defense;
            for (Item &item : this->items)
            {
                if (item.getType() == defenseType)
                    tempDefense += item.getLevel();
            }
            return tempDefense;
        }
    }
    std::vector<std::string> Entity::itemList() // Return all the item names in a list of strings.
    {
        std::vector<std::string> allItems;
        for (Item &item : this->items)
        {
            allItems.push_back(item.getName());
        }
        return allItems;
    }
    void Entity::takeDamage(int damage) // Lowers the Entity's health by the amount supplied. Takes into account any defense the Entity may have. If the damage is lower than the amount of defense, instead heals the Entity up to full HP.
    {
        if ((damage - defense) >= 0)
        {
            std::string capitalized = this->getName();
            capitalized[0] = toupper(capitalized[0]);
            if (hitpoints - (damage - defense) > 0)
                sayWait(capitalized + " took " + intToString((damage - defense)) + " damage.");
            else
                sayWait(capitalized + " took " + intToString(hitpoints) + " damage.");
            this->hitpoints = (hitpoints - (damage - defense));
        }
        else if ((damage - defense) < 0)
        {
            if(hitpoints - (damage - defense) < maxhp)
            {
                sayWait("The blow glances off the target, allowing it to heal for " + intToString(-(damage-defense)) + " hitpoints!");

               this->hitpoints = hitpoints - (damage - defense);
            }
            else
            {
                sayWait("The blow glances off the target, allowing it to heal back to full hitpoints!");

                this->hitpoints = this->maxhp;
            }
        }


    }
    void Entity::increaseAttack(int attack) // Increases the Entity's Attack by the supplied amount. Also displays a message saying what the new Attack value is.
    {
     this-> attack += attack;
    std::string capitalized = this->getName();
    capitalized[0] = toupper(capitalized[0]);
    sayWait("Attack power of " + this->getName() + " has been increased to " + intToString(this->attack) + ".");

}
    void Entity::decreaseHp(int hp) // Lowers the Entity's health by the amount supplied. Does NOT take into account any defense they may have.
    {
    this->hitpoints -= hp;
    std::string capitalized = this->getName();
    capitalized[0] = toupper(capitalized[0]);
    sayWait(capitalized + " lost "+ intToString(hp) + " hitpoints.");
    }
    void Entity::increaseHp (int hp) // Increases the Entity's current hitpoints by the supplied amount, up to it's max HP.
    {
        if (this->hitpoints + hp < maxhp)
        {
            this->hitpoints += hp;
            std::string capitalized = this->getName();
            capitalized[0] = toupper(capitalized[0]);
            sayWait(capitalized + " recovered " + intToString(hp) + " hitpoints.");
        }

        else
        {
            std::string capitalized = this->getName();
            capitalized[0] = toupper(capitalized[0]);
            sayWait(capitalized + " recovered to full hitpoints.");
            this->hitpoints = maxhp;
        }
    }
    bool Entity::hasItem(std::string itemName) // Returns whether or not the Entity already has the item supplied, based on the item's name.
    {
        std::vector<std::string> itemNames = itemList();
        if (std::find(itemNames.begin(), itemNames.end(), itemName) != itemNames.end())
        return true;
        else return false;
    }
    
    void Entity::findIncreaseItem(Item searchItem) // Increases the quantity of the item an Entity has if it is stackable.
    {
        std::vector<Item>::iterator it = std::find (items.begin(), items.end(), searchItem);
        if (it->isStackable())
        {
            it->increaseQuantity();
        }
    }

    Monster::Monster(std::string name, int hitpoints, int defense, int attack, int mobLevel, int dropRate, Item droppedItem) // Set values for a new Monster.
    {
        this->name = name; this->hitpoints = hitpoints; this->maxhp = this->hitpoints; this->defense = defense; this->attack = attack; this->mobLevel = mobLevel; this->droppedItem = droppedItem; this->dropRate = dropRate; this->money = arc4random() % mobLevel + 1; bleeding = false; bleedStrength = 0; resurrect = false;
    };

    Player::Player() // Set initial values for a new Player.
    {
        this->attack = 10; this->defense = 0; this->hitpoints = 100; this->maxhp = 100; this->money = 0; this->alive = true; this->chapter = 1; bleeding = false; bleedStrength = 0; this->genderType = unknown;
    };

    void Player::acquireItem(Item item) // Make the Player acquire an item. If they already have this item, try to increase it's quantity.
    {
        if (!hasItem(item.getName()))
        {
            this->items.push_back(item);
            if (item.getType() == hitpointsType)
            {
                this->increaseHp(item.getLevel());
            }
        }
        else
        {
            findIncreaseItem(item);
            if (item.getType() == hitpointsType)
            {
                this->increaseHp(item.getLevel());
            }

        }
    }
    void Player::showItems() // Displays all items the Player currently has in a formatted string. If the item possesses offensive or defensive stats, display them.
    {
        int i = 0;
        if (!items.empty())
        {
            for (Item &item : this->items)
            {
                i++;
                if (item.getQuantity() > 1) std::cout << intToString(item.getQuantity()) + " of ";
                std::cout << "Item # " + intToString(i) + " : " + item.getName();
                if (item.getType() == defenseType) std::cout << "\t\tIncreases your defensive power by " << item.getLevel() << "\n";
                else if (item.getType() == attackType) std::cout << "\t\tIncreases your attack power by " << item.getLevel() << "\n";
                else std::cout << "\n";
            }
            sayWait("");
        }
        else
        {
            sayWait("You don't currently have any items.\n");
        }
        std::cin.ignore(1);
    }

    void Player::setClass(type classType) // Set a player's class and change stats accordingly.
    {
    this->classType = classType;
    switch (classType) {
        case Paladin:
            this->setDefense(5);
            this->setMaxHp(120);
            break;
        case Ninja:
            this->setAttack(15);
            this->setMaxHp(80);
            break;
        case Commander:
            this->setMaxHp(150);
            break;
        case Reaper:
            this->setAttack(6);
            this->setMaxHp(80);
            break;
        default:
            break;
    }
}

    void Entity::setSkills()
    {
    // do nothing
}

    void Player::setSkills() // Set a Player's skills, changing the names according to the class.
    {
    if (this->getType() == Paladin)
    {
        this->skills.push_back("Holy Recovery");
        this->skills.push_back("Heavy Damage");
        this->skills.push_back("'Perfect' Defense");
        this->skills.push_back("Divine Retribution");
    }
    
    else if (this->getType() == Ninja)
    {
        this->skills.push_back("Ninja's Blood Draw");
        this->skills.push_back("Measured Slice");
        this->skills.push_back("Shadow Clone");
        this->skills.push_back("Ninja's Sacrifice");
    }
    
    else if (this->getType() == Commander)
    {
        this->skills.push_back("Blood-stained Shells");
        this->skills.push_back("Explosive Bulletstorm");
        this->skills.push_back("Tactical Dive");
        this->skills.push_back("Opportunistic Snipe");
    }
    else if (this->getType() == Reaper)
    {
        this->skills.push_back("Mending Blood of the Reaper");
        this->skills.push_back("Lacerating Cleave");
        this->skills.push_back("Soul Envoy's Second Wind");
        this->skills.push_back("Blood-boiling Rage");
    }
    else
    {
        this->skills.push_back("You");
        this->skills.push_back("haven't selected");
        this->skills.push_back("a class");
        this->skills.push_back("you fool!");
    }
}

    std::string Player::getClassName() // Returns the name of the class in string form.
    {
    switch (this->classType) {
        case Paladin:
            return "Paladin";
            break;
        case Ninja:
            return "Ninja";
            break;
        case Commander:
            return "Commander";
            break;
        case Reaper:
            return "Reaper";
        default:
            break;
    }
}

    void Entity::bleed(int strength)
    {
        this->bleedStrength = strength;
        this->bleedCounter = 3;
        this->bleeding = true;
    }

    void Entity::bleedDamage()
    {
        std::string capitalized = this->getName();
        capitalized[0] = toupper(capitalized[0]);
        if (bleeding && bleedCounter > 0 && bleedStrength > 0)
        {
            sayWait(capitalized + " took damage from Damage-Over-Time effects!");
            if (bleedStrength < this->hitpoints)
                this->decreaseHp(bleedStrength);
            else this->decreaseHp(this->hitpoints);
            bleedCounter--;
        }
        
        else if (bleeding && bleedCounter > 0 && bleedStrength < 0)
        {
            sayWait(capitalized + " healed from Health-Over-Time effects!");
            if (this->hitpoints + -bleedStrength < this->maxhp)
                this->increaseHp(-bleedStrength);
            else {
                this->hitpoints = this->maxhp;
                sayWait("Health of " + capitalized + " recovered to full!");
            }
            bleedCounter--;
        }
        
        else if (bleeding && bleedCounter >= 0 && bleedStrength > 0)
        {
            bleeding = false;
            sayWait(capitalized + " has been cured from Damage-Over-Time effects!");
        }
        
        else if (bleeding && bleedCounter >= 0 && bleedStrength < 0)
        {
            bleeding = false;
            sayWait(capitalized + " has lost their Health-Over-Time effects!");
        }
    }

    void Entity::clearBleed()
    {
    this->bleeding = false;
    this->bleedCounter = 0;
}

    void Entity::resetBuffedStats()
    {
        this->buffedDefense = 0;
        this->buffedAttack = 0;
        this->resurrect = false;
        this->resCooldown = 0;
    }