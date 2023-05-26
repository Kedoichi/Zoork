//
// Created by Richard Skarbez on 5/7/23.
//

#include "Character.h"
#include <iostream>

Character::Character(const std::string &n, const std::string &d) : GameObject(n, d) {}

bool Character::upgrade(int currentStat, int material)
{
    std::cout << "I don't understand it.";
    return false;
}

bool Character::getAttackable()
{
    return beAttackable;
};
void Character::setAttackable(bool value)
{
    beAttackable = value;
};
