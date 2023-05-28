//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ITEM_H
#define ZOORK_ITEM_H

#include "Command.h"
#include "GameObject.h"
#include "NullCommand.h"

class Item : public GameObject
{
public:
    Item(const std::string &, const std::string &);

    Item(const std::string &, const std::string &, std::shared_ptr<Command>);

    virtual void use();

    void setUseCommand(std::shared_ptr<Command>);

    void setRequireSearch(bool value);
    bool getRequireSearch() const;

    void setCollectable(bool value);
    bool getCollectable() const;

    void setRequiredItem(const std::string &itemName);
    std::string getRequiredItem() const;

protected:
    bool requireSearch = false;
    bool collectable = true;
    std::shared_ptr<Command> useCommand;
    std::string requiredItem;
};

#endif // ZOORK_ITEM_H