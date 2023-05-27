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
    virtual bool upgrade(int currentPower, int material);
    virtual void talk() = 0; // Pure virtual function
    bool getAttackable();
    void setAttackable(bool value);
    void setHealth(int value);
    int getHealth();
    void setAttack(int value);
    int getAttack();
    void setLevel(int value);
    int getLevel();
    void setRewardType(std::string value);
    std::string getRewardType();


protected:
    //    std::vector<Item*> inventory;
    //    std::vector<std::string> tags;
    int health;
    int attack;
    int level;
    std::string rewardType;
    std::vector<std::string> dialogueOptions;
    bool beAttackable = false;
};

#endif // ZOORK_CHARACTER_H
