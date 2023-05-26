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
    player->updateStat();
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
    player->updateStat();
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

    // Update stat;
    player->updateStat();
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
    int point = 0, stat = 0;

    // Check if the character is the Herbalist or Blacksmith
    if (characterName == "herbalist")
    {
        // get stat and point
        point = player->getHerbPoint();
        stat = player->getMagicStat();

        // 0 mean dont have anything 5 mean already got max level item
        if (stat == 0)
        {
            cout << "You don't have the potion yet. Town Elder will show you where to get !!!\n";
            return;
        }
        if (stat == 5)
        {
            cout << "You got the max level already";
            return;
        }

        bool isSuccessFull = character->upgrade(stat, point);
        if (isSuccessFull)
        {
            itemType = "Potion";
            player->changeHerbPoint(-stat * 10);
        }
    }
    else if (characterName == "blacksmith")
    {
        // get stat and point
        point = player->getMineralPoint();
        stat = player->getStrengthStat();

        // 0 mean dont have anything 5 mean already got max level item
        if (stat == 0)
        {
            cout << "You don't have the sword yet. Town Elder will show you where to get !!!\n";
            return;
        }
        if (stat == 5)
        {
            cout << "You got the max level already";
            return;
        }

        bool isSuccessFull = character->upgrade(stat, point);
        if (isSuccessFull)
        {
            itemType = "Sword";
            cout<<-stat * 10 << itemType;
            player->changeMineralPoint(-stat * 10);
        }
    }
    else
    {
        std::cout << "You can't give to this character.\n";
        return;
    }

    // base on stat -> tier and item add|delete player inventory
    // Starter -> Common -> Rare -> Epic -> Legendary

    switch (stat)
    {
    case 1:
        currentTier = "Starter";
        nextTier = "Common";
        break;
    case 2:
        currentTier = "Common";
        nextTier = "Rare";
        break;
    case 3:
        currentTier = "Rare";
        nextTier = "Epic";
        break;
    case 4:
        currentTier = "Epic";
        nextTier = "Legendary";
        break;
    default:
        break;
    }

    // Login within player's inventory
    Item *item = nullptr;
    int itemIndex = -1;

    std::vector<Item *> &playerInventory = const_cast<std::vector<Item *> &>(player->getInventory());

    for (size_t i = 0; i < playerInventory.size(); ++i)
    {
        if (playerInventory[i]->getName() == currentTier + " " + itemType)
        {
            item = playerInventory[i];
            itemIndex = i;

            // Remove the item from the player's inventory
            playerInventory.erase(playerInventory.begin() + itemIndex);
            Item *reward = player->getCurrentRoom()->getItem(nextTier + " " + itemType);
            player->addItem(reward);
            player->updateStat();
            break;
        }
    }
}