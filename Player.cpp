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
    for (auto it = inventory.begin(); it != inventory.end(); ++it)
    {
        if ((*it)->getName() == itemName)
        {
            inventory.erase(it);
            break;
        }
    }
}