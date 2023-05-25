//
// Created by Richard Skarbez on 5/7/23.
//

#include "Character.h"

Character::Character(const std::string &n, const std::string &d) : GameObject(n, d) {
}
int Character::getHealth()
{
    return health;
};
void Character::setHealth(int setHealth)
{
    health = setHealth;
};
void Character::setAttackable(bool setAttackable)
{
    attackable = setAttackable;
};
bool Character::getAttackable()
{
    return attackable;
};
int Character::getDamage()
{
    return damage;
};
void Character::setDamage(int setdame)
{
    damage = setdame;
};
// std::string Character::getName(){
//     return name;
// }