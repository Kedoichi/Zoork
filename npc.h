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
        std::cout << "Town Elder: \"Indeed, young adventurer.I have this Sword and Potion overthere, take it with you. Also, behind the house, there are some items that might help you in your journey.\"" << std::endl;
        std::cout << "Player: \"Thank you for your guidance. I shall explore the dungeon and retrieve the ancient relic.\"" << std::endl;
        std::cout << "Town Elder: \"Oh! I forget.\nUse look/search command to see the item around and you can take/drop item.\"" << std::endl;
        std::cout << "Player: \"Thank you, wise elder.\"" << std::endl;
    }
};

class Herbalist : public Character
{
public:
    Herbalist() : Character("Herbalist", "A knowledgeable herbalist with an assortment of potions and remedies.") {}

    void talk() override
    {
        std::cout << "Player: \"Hello, herbalist. Do you have any remedies or potions that could aid me?\"" << std::endl;
        std::cout << "Herbalist: \"Welcome, traveler. Hmmm... I got better potion for you.\n.Bring me good herb then I can upgrade it. - Use give Herbalist\"" << std::endl;
        std::cout << "Player: \"Thank you for your generosity. I'll be on the lookout for those herbs.\"" << std::endl;
        std::cout << "System: \"You can gather Herb by command \"gather\" !!!\"" << std::endl;
    }

    bool upgrade(int currentStat, int material)
    {
        if (material >= currentStat * 10)
        {
            std::cout << "Herbalist: \"Oh, you bring me good herb. Let me upgrade it for you.\"" << std::endl;
            return true;
        }
        else
        {
            std::cout << "Herbalist: \"Hmm... Not enought. Try to get some more herb\"" << std::endl;
            std::cout << "Herbalist: \"I need " << currentStat * 10 << " herbs\"" << std::endl;
            return false;
        }
    }
};

class Blacksmith : public Character
{
public:
    Blacksmith() : Character("Blacksmith", "A skilled blacksmith who forges weapons and armor.") {}

    void talk() override
    {
        std::cout << "Player: \"Greetings, blacksmith. I am in need of better equipment. What do you have to offer?\"" << std::endl;
        std::cout << "Blacksmith: \"Ah, a warrior seeking strength! Gimme mineral, I will upgrade you weapon.  - Use give Blacksmith\"" << std::endl;
        std::cout << "Player: \"I shall choose wisely. Thank you for your craftsmanship.\"" << std::endl;
        std::cout << "System: \"You can gather mineral by command \"gather\" !!!\"" << std::endl;
    }
    bool upgrade(int currentStat, int material)
    {
        if (material >= currentStat * 10)
        {
            std::cout << "Blacksmith: \"Oh, you bring me good mineral. Let me upgrade it for you.\"" << std::endl;
            return true;
        }
        else
        {
            std::cout << "Blacksmith: \"Hmm... Not enought. Try to get some more mineral\"" << std::endl;
            std::cout << "Blacksmith: \"I need " << currentStat * 10 << " minerals\"" << std::endl;
            return false;
        }
    }
};

class MysteriousStranger : public Character
{
public:
    MysteriousStranger() : Character("Mysterious Stranger", "A cloaked figure lurking in the shadows of the ancient ruin.") {}

    void talk() override
    {
        std::cout << "Player: \"Greetings, mysterious stranger. What secrets do you hold in this ancient ruin?\"" << std::endl;
        std::cout << "Mysterious Stranger: \"You seek answers, do you not? There are dangerous creatures lurking within the depths of this mine.\nTake these glasses to see their hidden stats and help you survive in there..\"" << std::endl;
        std::cout << "Player: \"I am grateful for your warning and the glasses. I shall proceed with caution.\"" << std::endl;
    }
};

#endif // NPC_H