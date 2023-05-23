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
        else if (command == "quit")
        {
            handleQuitCommand(arguments);
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

    // Add the item to the player's inventory
    player->addItem(item);

    // Remove the item from the room
    player->getCurrentRoom()->removeItem(item->getName());

    std::cout << "You have taken the " << item->getName() << ".\n";
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments)
{
    // To be implemented
    std::cout << "This functionality is not yet enabled.\n";
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
