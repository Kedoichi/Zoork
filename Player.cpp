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

std::vector<Item *> Player::getInventory() const
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
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(), [&](Item *item)
                                   {
        if (item->getName() == itemName)
        {
            delete item; // Delete the item object if necessary
            return true; // Remove the item from the vector
        }
        return false; }),
                    inventory.end());
}

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

void Player::setDamage(int value)
{
    damage = value;
};