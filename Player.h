//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PLAYER_H
#define ZOORK_PLAYER_H

#include "Character.h"
#include "Location.h"
#include "NullRoom.h"

class Player : public Character
{
public:
    static Player *instance()
    {
        // Note: lazy instantiation of the singleton Player object
        if (!playerInstance)
        {
            playerInstance = new Player();
        }
        return Player::playerInstance;
    }

    void setCurrentRoom(Room *);

    Room *getCurrentRoom() const;

    Player(const Player &) = delete;

    Player &operator=(const Player &) = delete;

    void addItem(Item *);
    void removeItem(const std::string &);
    // Item *getItem(const std::string &);
    // Item *retrieveItem(const std::string &);
    std::vector<Item *> getInventory() const;
    int getInventorySize() const;
    bool backpackstatus() const;
    void setBackpack(bool value);
    void talk() override
    {
        // Implement player's dialogue here
        std::cout << getName() << ": \"Let's win this\"" << std::endl;
    }

private:
    bool backpackStatus;
    std::vector<Item *> inventory;
    static Player *playerInstance;
    Room *currentRoom;

    Player() : Character("You", "You are a person, alike in dignity to any other, but uniquely you."),
               currentRoom(new NullRoom()) {}
};

#endif // ZOORK_PLAYER_H
