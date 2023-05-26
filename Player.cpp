//
// Created by Richard Skarbez on 5/7/23.
//

#include "Player.h"

Player *Player::playerInstance = nullptr;

void Player::setCurrentRoom(Room *room)
{
    currentRoom = room;
}
bool Player::backpackstatus() const
{
    return backpackStatus;
}

void Player::setBalance(int value)
{
    balance = value;
}
int Player::getBalance()
{
    return balance;
}
void Player::setBackpack(bool value)
{
    backpackStatus = value;
}

const std::vector<Item *> &Player::getInventory() const
{
    return inventory;
}
int Player::getInventorySize() const
{
    return inventory.size();
}
Room *Player::getCurrentRoom() const
{
    return currentRoom;
}
void Player::addItem(Item *item)
{
    inventory.push_back(item);
}

void Player::removeItem(const std::string &itemName)
{
    auto it = std::find_if(inventory.begin(), inventory.end(), [&](Item *item)
                           { return item->getName() == itemName; });

    if (it != inventory.end())
    {
        Item *itemToRemove = *it;
        inventory.erase(it);
        delete itemToRemove; // Clean up the memory of the removed item
    }
}

// void Player::removeItem(const std::string &itemName)
// {

//     playerInventory.erase(playerInventory.begin() + itemIndex);
//     auto it = std::find_if(inventory.begin(), inventory.end(), [&](Item *item)
//                            { return item->getName() == itemName; });

//     if (it != inventory.end())
//     {
//         inventory.erase(it);
//     }
// }

void Player::setHerbPoint(int value)
{
    herbPoint = value;
}
int Player::getHerbPoint()
{
    return herbPoint;
}
void Player::setMineralPoint(int value)
{
    mineralPoint = value;
}
int Player::getMineralPoint()
{
    return mineralPoint;
}
void Player::changeHerbPoint(int value)
{
    herbPoint = herbPoint + value;
}
void Player::changeMineralPoint(int value)
{
    mineralPoint = mineralPoint + value;
}
bool Player::getVisionStatus() const
{
    return visionStatus;
}
void Player::setVisionStatus(bool value)
{
    visionStatus = value;
}
void Player::updateStat()
{
    int swordLevel = 0;  // Default base damage level
    int potionLevel = 0; // Default base potion level

    // Iterate over the player's inventory
    for (Item *item : inventory)
    {
        std::string itemName = item->getName();
        std::string lastWord = itemName.substr(itemName.find_last_of(' ') + 1);
        if (lastWord == "Sword")
        {
            if (item->getName() == "Starter Sword")
            {
                swordLevel = 1;
            }
            if (item->getName() == "Common Sword")
            {
                swordLevel = 2;
            }
            if (item->getName() == "Rare Sword")
            {
                swordLevel = 3;
            }
            if (item->getName() == "Epic Sword")
            {
                swordLevel = 4;
            }
            if (item->getName() == "Legendary Sword")
            {
                swordLevel = 5;
            }

            std::cout << "\"Your strength change from " << strength << " -> " << swordLevel << " !!!\"\n";
            strength = swordLevel;
        }
        if (lastWord == "Potion")
        {
            if (item->getName() == "Starter Potion")
            {
                potionLevel = 1;
            }
            else if (item->getName() == "Common Potion")
            {
                potionLevel = 2;
            }
            else if (item->getName() == "Rare Potion")
            {
                potionLevel = 3;
            }
            else if (item->getName() == "Epic Potion")
            {
                potionLevel = 4;
                ;
            }
            else if (item->getName() == "Legendary Potion")
            {
                potionLevel = 5;
            }
            
            std::cout << "\"Your magic change from " << magic << " -> " << potionLevel << " !!!\"\n";
            magic = potionLevel;
        }
    }
}
int Player::getMagicStat()
{
    return magic;
}
int Player::getStrengthStat()
{
    return strength;
}