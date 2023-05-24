//
// Created by Richard Skarbez on 5/7/23.
//

#include "NullPassage.h"
#include "Room.h"

#include <utility>
using namespace std;

Room::Room(const std::string &n, const std::string &d) : Location(n, d)
{
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

std::string makeLowercase(std::string input)
{
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p)
{
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction)
{
    auto it = passageMap.find(direction);
    if (it != passageMap.end())
    {
        passageMap.erase(it);
    }
}
void Room::addCharacter(Character *character)
{
    characters.push_back(character);
}
Character *Room::getCharacter(const std::string &characterName)
{
    for (auto &character : characters)
    {
        if (makeLowercase(character->getName()) == characterName)
        {
            return character;
        }
    }
    return nullptr;
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction)
{
    auto it = passageMap.find(direction);
    if (it != passageMap.end())
    {
        return it->second;
    }
    else
    {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

void Room::addItem(Item *item)
{
    items.push_back(item);
}

void Room::removeItem(const std::string &itemName)
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        if ((*it)->getName() == itemName)
        {
            items.erase(it);
            break;
        }
    }
}

Item *Room::getItem(const std::string &itemName)
{
    for (auto &item : items)
    {
        if (makeLowercase(item->getName()) == itemName)
        {
            return item;
        }
    }
    return nullptr;
}

Item *Room::retrieveItem(const std::string &itemName)
{
    Item *item = getItem(itemName);
    if (item)
    {
        removeItem(itemName);
    }
    return item;
}

string Room::getDescription() const
{
    string description = Location::getDescription();

    // Append items description
    if (!items.empty())
    {
        description += "Items in the room:\n";
        for (const auto &item : items)
        {
            description += "- " + item->getName() + ": " + item->getDescription() + "\n";
        }
    }

    // Append characters description
    if (!characters.empty())
    {
        description += "Characters in the room:\n";
        for (const auto &character : characters)
        {
            description += "- " + character->getName() + ": " + character->getDescription() + "\n";
        }
    }

    return description;
}
