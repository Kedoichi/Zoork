#ifndef MOB_H
#define MOB_H

#include "Character.h"
#include <iostream>

// Thoose in forest and drop herb
class ForestImp : public Character
{
public:
    ForestImp() : Character("Forest Imp", "A mischievous creature with glowing green eyes. It tends to hide in the shadows of the forest.") {}
    void talk() override{};
};

class FungalShaman : public Character
{
public:
    FungalShaman() : Character("Fungal Shaman", "A sinister creature that resides deep within the fungal-infested areas. It harnesses the power of mushrooms for its dark magic.") {}
    void talk() override{};
};
class DarkWoodNymph : public Character
{
public:
    DarkWoodNymph() : Character("Dark Wood Nymph", "A haunting and mysterious entity that resides within the darkest corners of the enchanted forest. Its presence brings an eerie stillness to the air.") {}
    void talk() override{};
};

// Thoose in mine and drop mineral
class Goblin : public Character
{
public:
    Goblin() : Character("Goblin", "A small and mischievous creature with sharp claws and a wicked grin. Watch out for its quick attacks!") {}
    void talk() override{};
};
class RockGolem : public Character
{
public:
    RockGolem() : Character("Rock Golem", "A towering creature made of solid rock and earth. It guards the underground caves with its immense strength.") {}
    void talk() override{};
};
class AncientGuardian : public Character
{
public:
    AncientGuardian() : Character("Ancient Guardian", "A colossal golem-like entity that protects ancient ruins. Its body is adorned with ancient symbols and gemstones.") {}
    void talk() override{};
};
class Dragon : public Character
{
public:
    Dragon() : Character("Dragon", "A fearsome creature of legend with fiery breath, tough scales, and piercing gaze.") {}
    void talk() override{};
};

#endif // MOB_H