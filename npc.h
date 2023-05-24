#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include <iostream>

class TownElder : public Character
{
public:
    TownElder() : Character("Town Elder", "An elderly figure dressed in robes, offering guidance and quests to the player.") {}

    void talk() override
    {
        std::cout << "Player: \"Greetings, wise elder. Can you provide any guidance for my journey?\"" << std::endl;
        std::cout << "Town Elder: \"Ah, a brave adventurer! I sense your purpose. To uncover the secrets of this land, you must venture into the depths of the dungeon. Find the ancient relic hidden within its chambers.\"" << std::endl;
        std::cout << "Player: \"I accept this quest, noble elder. Is there anything else you can tell me?\"" << std::endl;
        std::cout << "Town Elder: \"Indeed, young adventurer. Behind the house, there are som items that might help you in your journey.\"" << std::endl;
        std::cout << "Player: \"Thank you for your guidance, wise elder. I shall explore the dungeon and retrieve the ancient relic.\"" << std::endl;
    }
};

class Herbalist : public Character
{
public:
    Herbalist() : Character("Herbalist", "A knowledgeable herbalist with an assortment of potions and remedies.") {}

    void talk() override
    {
        std::cout << "Player: \"Hello, herbalist. Do you have any remedies or potions that could aid me?\"" << std::endl;
        std::cout << "Herbalist: \"Welcome, traveler. I specialize in healing potions. Take this mysterious potion; it cleanses adverse effects. Bring me rare herbs, and I shall reward you handsomely.\"Remember to use this Silver Hoe to collect\"" << std::endl;
        std::cout << "Player: \"Thank you for your generosity. I'll be on the lookout for those herbs.\"" << std::endl;
    }
};

class Blacksmith : public Character
{
public:
    Blacksmith() : Character("Blacksmith", "A skilled blacksmith who forges weapons and armor.") {}

    void talk() override
    {
        std::cout << "Player: \"Greetings, blacksmith. I am in need of better equipment. What do you have to offer?\"" << std::endl;
        std::cout << "Blacksmith: \"Ah, a warrior seeking strength! Feast your eyes upon my finest weapons and armor. Arm yourself well and face your enemies with confidence.\"" << std::endl;
        std::cout << "Player: \"I shall choose wisely. Thank you for your craftsmanship.\"" << std::endl;
    }
};

class TavernOwner : public Character
{
public:
    TavernOwner() : Character("Tavern Owner", "The owner of the tavern, providing food, drinks, and a place to rest.") {}

    void talk() override
    {
        std::cout << "Player: \"Good day, tavern owner. Might I find refreshments or a place to rest here?\"" << std::endl;
        std::cout << "Tavern Owner: \"Welcome, weary traveler. I have hearty meals and a cozy room for a modest fee. Rest well, and share your tales with fellow patrons.\"" << std::endl;
        std::cout << "Player: \"I'll gladly partake in your hospitality. A warm meal and some rest are much needed.\"" << std::endl;
    }
};
class MysteriousStranger : public Character
{
public:
    MysteriousStranger() : Character("Mysterious Stranger", "A cloaked figure lurking in the shadows of the ancient ruin.") {}

    void talk() override
    {
        std::cout << "Player: \"Greetings, mysterious stranger. What secrets do you hold in this ancient ruin?\"" << std::endl;
        std::cout << "Mysterious Stranger: \"You seek answers, do you not? Prove your worth by completing my trials. Only then shall the truth be revealed.\"" << std::endl;
        std::cout << "Player: \"I accept your challenge. Lead me through these trials, and I shall uncover the secrets hidden within.\"" << std::endl;
    }
};

#endif // NPC_H
