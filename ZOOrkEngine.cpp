//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"

#include <utility>

using namespace std;

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start)
{
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
    player->setBackpack(false);
    player->setBalance(100);
    player->setHerbPoint(0);
    player->setMineralPoint(0);
    player->setHealth(100);
    player->setStrengthStat(0);
    player->setMagicStat(0);
}

void ZOOrkEngine::run()
{
    while (!gameOver)
    {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go")
        {
            handleGoCommand(arguments);
        }
        else if ((command == "look") || (command == "inspect"))
        {
            handleLookCommand(arguments);
        }
        else if ((command == "take") || (command == "get"))
        {
            handleTakeCommand(arguments);
        }
        else if (command == "drop")
        {
            handleDropCommand(arguments);
        }
        else if (command == "search")
        {
            handleSearchCommand();
        }
        else if (command == "talk")
        {
            handleTalkCommand(arguments);
        }
        else if (command == "quit")
        {
            handleQuitCommand(arguments);
        }
        else if (command == "gather")
        {
            handleGatherCommand(arguments);
        }
        else if (command == "give")
        {
            handleGiveCommand(arguments);
        }
        else if (command == "battle" || command == "bt")
        {
            handleBattleCommand(arguments);
        }
        else if (command == "inv" || command == "inventory")
        {
            handleInventoryCommand();
        }
        else
        {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments)
{
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north")
    {
        direction = "north";
    }
    else if (arguments[0] == "s" || arguments[0] == "south")
    {
        direction = "south";
    }
    else if (arguments[0] == "e" || arguments[0] == "east")
    {
        direction = "east";
    }
    else if (arguments[0] == "w" || arguments[0] == "west")
    {
        direction = "west";
    }
    else if (arguments[0] == "u" || arguments[0] == "up")
    {
        direction = "up";
    }
    else if (arguments[0] == "d" || arguments[0] == "down")
    {
        direction = "down";
    }
    else
    {
        direction = arguments[0];
    }

    Room *currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments)
{
    if (arguments.empty())
    {
        // print the description of the current room if no other argument

        Room *currentRoom = player->getCurrentRoom();
        std::cout << currentRoom->getDescription() << std::endl;
    }
    else
    {
        std::string target = arguments[0];
        for (size_t i = 1; i < arguments.size(); ++i)
        {
            target += " " + arguments[i];
        }
        std::string itemName = makeLowercase(target);

        Item *item = player->getCurrentRoom()->getItem(itemName);
        if (item != nullptr)
        {
            std::cout << item->getDescription() << std::endl;
        }
        else
        {
            std::cout << "There is no " << target << " here." << std::endl;
        }
    }
}
void ZOOrkEngine::handleSearchCommand()
{
    Room *currentRoom = player->getCurrentRoom();
    std::cout << currentRoom->search() << std::endl;
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments)
{
    if (arguments.empty())
    {
        std::cout << "Please specify the item you want to take.\n";
        return;
    }
    std::string target = arguments[0];
    for (size_t i = 1; i < arguments.size(); ++i)
    {
        target += " " + arguments[i];
    }
    std::string itemName = makeLowercase(target);

    // Check if the current room has the specified item
    Item *item = player->getCurrentRoom()->getItem(itemName);
    if (item == nullptr)
    {
        std::cout << "There is no " << itemName << " here.\n";
        return;
    }

    if (itemName == "backpack")
    {
        player->setBackpack(true);
        std::cout << "You have taken the " << item->getName() << ".\n";
        player->addItem(item);

        player->getCurrentRoom()->removeItem(item->getName());
        return;
    }

    // Check if the player already has the maximum number of items without a backpack
    if (player->getInventorySize() >= 2 && player->backpackstatus() == false)
    {
        std::cout << "You can only carry two items without a backpack.\n";
        return;
    }

    // Is iteam collectable

    if (item->getCollectable() == false)
    {
        std::cout << "You can't take that.\nThere must be a way to have it.";
        return;
    }
    // Add the item to the player's inventory
    player->addItem(item);

    // Remove the item from the room
    player->getCurrentRoom()->removeItem(item->getName());

    std::cout << "You have taken the " << item->getName() << ".\n";

    // Update stat;
    if (itemName == "sword")
    {
        player->setStrengthStat(1);
    }
    if (itemName == "potion")
    {
        player->setMagicStat(1);
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments)
{
    if (arguments.empty())
    {
        std::cout << "Please specify the item you want to drop.\n";
        return;
    }

    std::string target = arguments[0];
    for (size_t i = 1; i < arguments.size(); ++i)
    {
        target += " " + arguments[i];
    }
    std::string itemName = makeLowercase(target);

    // Check if the player has the specified item in their inventory
    Item *item = nullptr;
    int itemIndex = -1;

    std::vector<Item *> &playerInventory = const_cast<std::vector<Item *> &>(player->getInventory());

    for (size_t i = 0; i < playerInventory.size(); ++i)
    {
        if (makeLowercase(playerInventory[i]->getName()) == itemName)
        {
            item = playerInventory[i];
            itemIndex = i;
            break;
        }
    }

    if (item == nullptr)
    {
        std::cout << "You don't have a " << itemName << " in your inventory.\n";
        return;
    }

    // Remove the item from the player's inventory
    playerInventory.erase(playerInventory.begin() + itemIndex);

    std::cout << item->getName() << " removed.\n";

    const std::vector<Item *> &inventory = player->getInventory();

    if (inventory.empty())
    {
        std::cout << "Your inventory is empty.\n";
    }
    else
    {
        std::cout << "Inventory:\n";
        for (Item *item : inventory)
        {
            std::cout << "- " << item->getName() << ": " << item->getDescription() << "\n";
        }
    }

    // Add the item to the current room's items
    player->getCurrentRoom()->addItem(item);

    std::cout << "You have dropped the " << item->getName() << ".\n";
}

void ZOOrkEngine::handleTalkCommand(std::vector<std::string> &arguments)
{
    if (arguments.empty())
    {
        std::cout << "Please specify the character you want to talk to.\n";
        return;
    }

    std::string target = arguments[0];
    for (size_t i = 1; i < arguments.size(); ++i)
    {
        target += " " + arguments[i];
    }
    std::string characterName = makeLowercase(target);

    // Check if the current room has the specified character
    Character *character = player->getCurrentRoom()->getCharacter(characterName);
    if (character == nullptr)
    {
        std::cout << "There is no " << characterName << " here.\n";
        return;
    }

    // Perform the talk action with the character
    character->talk();

    // Check if the character is the Mysterious Stranger
    if (characterName == "mysterious stranger")
    {
        // Check if the player has the hoe in their inventory
        bool hasGlass = player->getVisionStatus();
        if (!hasGlass)
        {
            // Give the hoe to the player
            Item *vision = new Item("Mistic Glasses", "There are number on Character. Use examine command for a closer look!!!\nYou can see on the dark now");
            std::cout << "The Mysterious Stranger gives you a Mistic Glasses.\n";
            player->addItem(vision);
            player->setVisionStatus(true);
        }
        else
        {
            std::cout << "You already have a Mistic Glasses.\n";
        }
        return;
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments)
{
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes")
    {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input)
{
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' '))
    {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input)
{
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}

void ZOOrkEngine::handleInventoryCommand()
{
    std::vector<Item *> inventory = player->getInventory();

    if (inventory.empty())
    {
        std::cout << "Your inventory is empty.\n";
    }
    else
    {
        std::cout << "Inventory:\n";
        for (Item *item : inventory)
        {
            std::cout << "- " << item->getName() << ": " << item->getDescription() << "\n";
        }
    }
    // Print player stat
    std::cout << "----------------------------------" << endl;
    std::cout << "Health: " << player->getHealth() << endl;
    std::cout << "Balance: " << player->getBalance() << endl;
    std::cout << "Strength: " << player->getStrengthStat() << endl;
    std::cout << "Magic: " << player->getMagicStat() << endl;
    std::cout << "Herb: " << player->getHerbPoint() << endl;
    std::cout << "Mineral: " << player->getMineralPoint() << endl;
}

void ZOOrkEngine::handleGatherCommand(std::vector<std::string> arguments)
{
    if (arguments.empty())
    {
        std::cout << "Please specify the item you want to take.\n";
        return;
    }
    std::string target = arguments[0];
    for (size_t i = 1; i < arguments.size(); ++i)
    {
        target += " " + arguments[i];
    }
    std::string itemName = makeLowercase(target);

    // Check if the current room has the specified item
    Item *item = player->getCurrentRoom()->getItem(itemName);
    if (item == nullptr)
    {
        std::cout << "There is no " << itemName << " here.\n";
        return;
    }

    // Check player have tool ?

    int quality;
    string toolRequire = item->getRequiredItem();

    Item *tool = nullptr;
    std::vector<Item *> &playerInventory = const_cast<std::vector<Item *> &>(player->getInventory());

    for (size_t i = 0; i < playerInventory.size(); ++i)
    {
        if (playerInventory[i]->getName() == toolRequire)
        {
            tool = playerInventory[i];
            break;
        }
    }

    if (tool == nullptr)
    {
        std::cout << "You don't have a " << toolRequire << " in your inventory.\n";
        return;
    }
    else
    {

        if (itemName == "mineral")
        {
            quality = getRandomNumber(1, 5);
            player->changeMineralPoint(quality);
        }
        if (itemName == "misteric herb")
        {
            quality = getRandomNumber(1, 5);
            player->changeHerbPoint(quality);
        }
    }

    std::cout << "You have taken the " << quality << " x " << item->getName() << ".\n";
}

int ZOOrkEngine::getRandomNumber(int min, int max)
{
    // Providing a seed value
    srand((unsigned)time(NULL));

    // Get a random number
    int random = rand() % (max - min + 1);
    return random + min;
}

void ZOOrkEngine::handleGiveCommand(std::vector<std::string> &arguments)
{
    if (arguments.empty())
    {
        std::cout << "Please specify the character you want to give to.\n";
        return;
    }

    std::string target = arguments[0];
    for (size_t i = 1; i < arguments.size(); ++i)
    {
        target += " " + arguments[i];
    }
    std::string characterName = makeLowercase(target);

    // Check if the current room has the specified character
    Character *character = player->getCurrentRoom()->getCharacter(characterName);
    if (character == nullptr)
    {
        std::cout << "There is no " << characterName << " here.\n";
        return;
    }

    // Init variable for logic
    string currentTier = "", nextTier = "", itemType = "";
    int point, stat;
    bool isSuccessFull;

    // Check if the character is the Herbalist or Blacksmith
    if (characterName == "herbalist")
    {
        // get stat and point
        point = player->getHerbPoint();
        stat = player->getMagicStat();

        // 0 mean dont have anything 5 mean already got max level item
        if (stat == 0)
        {
            std::cout << "You don't have the potion yet. Town Elder will show you where to get !!!\n";
            return;
        }
        if (stat == 5)
        {
            std::cout << "You got the max level already";
            return;
        }

        isSuccessFull = character->upgrade(stat, point);
        if (!isSuccessFull)
        {
            return;
        }
        player->changeHerbPoint(-stat * 10);
        player->setMagicStat(stat++);
    }
    else if (characterName == "blacksmith")
    {
        // get stat and point
        point = player->getMineralPoint();
        stat = player->getStrengthStat();

        // 0 mean dont have anything 5 mean already got max level item
        if (stat == 0)
        {
            std::cout << "You don't have the sword yet. Town Elder will show you where to get !!!\n";
            return;
        }
        if (stat == 5)
        {
            std::cout << "You got the max level already";
            return;
        }

        isSuccessFull = character->upgrade(stat, point);
        if (!isSuccessFull)
        {
            return;
        }
        player->changeMineralPoint(-stat * 10);
        player->setStrengthStat(stat + 1);
    }
    else
    {
        std::cout << "You can't give to this character.\n";
        return;
    }

    std::cout << "Sucessfull !!! use inventory command to check your stats." << endl;
}

void ZOOrkEngine::handleBattleCommand(std::vector<std::string> &arguments)
{
    if (arguments.empty())
    {
        std::cout << "Please specify the character you want to attack.\n";
        return;
    }

    std::string target = arguments[0];
    for (size_t i = 1; i < arguments.size(); ++i)
    {
        target += " " + arguments[i];
    }
    std::string characterName = makeLowercase(target);

    // Check if the current room has the specified character
    Character *character = player->getCurrentRoom()->getCharacter(characterName);
    if (character == nullptr)
    {
        std::cout << "There is no " << characterName << " here.\n";
        return;
    }

    if (!character->getAttackable())
    {
        std::cout << "You can't attack this character.\n";
        return;
    }

    // init variable for battle
    //  the battle is turn base. each turn player can choose to
    // 1:atk 2:heal 3:run
    //  if player choose to atk, the player will deal damage to the enemy
    // base on the strength of player.
    //  if player choose to heal, the player will heal base on the magic of player
    //  if player choose to run, the player will have potential chance to run away base on lv of mob

    int playerHP, playerStrength, playerMagic;
    int mobHP, mobAtkStat, mobLevel;
    int action, randomValue, reward;

    playerHP = player->getHealth();
    playerStrength = player->getStrengthStat();
    playerMagic = player->getMagicStat();

    mobHP = character->getHealth();
    mobAtkStat = character->getAttack();
    mobLevel = character->getLevel();

    // using do while to ask player action each turn
    do
    {
        cout << "Choose action\n1: Attack\n2: Heal\n3: Run" << endl
             << "--";
        cin >> action;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        switch (action)
        {
        case 1:
            // player atk
            randomValue = getRandomNumber(playerStrength * 8, playerStrength * 13);
            mobHP -= randomValue;
            cout << "You deal " << randomValue << " damage to " << characterName << endl;
            break;
        case 2:
            // player heal
            randomValue = getRandomNumber(playerMagic * 5, playerMagic * 15);

            playerHP += randomValue;
            cout << "You heal " << randomValue << " HP" << endl;
            player->setHealth(playerHP += randomValue);
            break;
        case 3:
            // player run
            if (getRandomNumber(1, 5) > mobLevel)
            {
                cout << "You run away" << endl;
                return;
            }
            else
            {
                cout << "You can't run away" << endl;
            }
            break;
        default:
            cout << "Please choose the correct action" << endl;
            break;
        }

        if (mobHP >= 0)
        {
            // mob atk
            randomValue = getRandomNumber(mobAtkStat * 0.8, mobAtkStat * 1.3);
            playerHP -= randomValue;
            player->setHealth(playerHP);
            cout << characterName << " deal " << randomValue << " damage to you" << endl;
        }
        else
        {
            cout << "You win" << endl;
            reward = getRandomNumber(mobLevel * 2, mobLevel * 10);
            if (character->getRewardType() == "Herb")
            {
                player->changeHerbPoint(reward);
            }
            if (character->getRewardType() == "Mineral")
            {
                player->changeMineralPoint(reward);
            }

            cout << "You have recieve " << reward << " " << character->getRewardType() << " !!!\n";
        }

        if (playerHP <= 0)
        {
            cout << "You lose" << endl;
            cout << "Try again mate" << endl;
            gameOver = true;
        }
    } while (playerHP > 0 and mobHP > 0);
}
