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

int Player::getMagicStat()
{
    return magic;
}
int Player::getStrengthStat()
{
    return strength;
}
int Player::getHealth()
{
    return health;
}
void Player::changeHealthPoint(int value)
{
    health = health + value;
}

void Player::setMagicStat(int value) { magic = value; };
void Player::setStrengthStat(int value) { strength = value; };
void Player::setHealth(int value) { health = value; };