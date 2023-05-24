//
// Created by Richard Skarbez on 5/7/23.
//

#include "Item.h"

#include <utility>

Item::Item(const std::string &n, const std::string &d) : GameObject(n, d),
                                                         useCommand(std::make_shared<NullCommand>()) {}

Item::Item(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : GameObject(n, d),
                                                                                     useCommand(std::move(c)) {}

void Item::use()
{
    useCommand->execute();
}

void Item::setUseCommand(std::shared_ptr<Command> c)
{
    useCommand = c;
}

void Item::setRequireSearch(bool value)
{
    requireSearch = value;
}

bool Item::getRequireSearch() const
{
    return requireSearch;
}
void Item::setCollectable(bool value)
{
    collectable = value;
}

bool Item::getCollectable() const
{
    return collectable;
}

int Item::getDuration() const
{
    return duration;
}
void Item::setDuration(int value)
{
    duration = value;
}

void Item::decreaseDuration()
{
    if (duration > 0)
    {
        --duration;
    }
}