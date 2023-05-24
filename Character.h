//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "GameObject.h"
#include "Item.h"
#include <vector>

class Character : public GameObject {
public:
    Character(const std::string &, const std::string &);

    virtual void talk() = 0; // Pure virtual function
protected:
//    std::vector<Item*> inventory;
//    std::vector<std::string> tags;
    int health;
    int attack;
    int move;
    int initiative;
    std::vector<std::string> dialogueOptions;
};

#endif //ZOORK_CHARACTER_H
