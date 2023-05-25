//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "GameObject.h"
#include "Item.h"
#include <vector>

class Character : public GameObject
{
public:
    Character(const std::string &, const std::string &);
    // std::string getName();

    virtual void talk() = 0; // Pure virtual function
    int getHealth();
    void setHealth(int health);
    void setAttackable(bool attackable);
    bool getAttackable();
    int getDamage();
    void setDamage(int damage);

protected:
    // std::string name;
    std::vector<Item *> inventory;
    //    std::vector<std::string> tags;
    int health;
    int damage;
    // int move;
    // int initiative;
    std::vector<std::string> dialogueOptions;
    bool attackable;
};

#endif // ZOORK_CHARACTER_H
