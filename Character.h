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
    void takeDamage(int damage);
    void getHealth(Item* item);
    void setHealth(Item* item);
    void setAttackable(bool attackable);
    void getDamage(bool attackable);
    void setDamage(bool attackable);
protected:
    std::vector<Item*> inventory;
//    std::vector<std::string> tags;
    int health;
    int damage;
    //int move;
    //int initiative;
    std::vector<std::string> dialogueOptions;
    bool attackable;
};

#endif //ZOORK_CHARACTER_H
