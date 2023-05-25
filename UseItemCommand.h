#ifndef USEITEMCOMMAND_H
#define USEITEMCOMMAND_H

#include "Command.h"
#include "Item.h"
#include "Character.h"

#include <utility>

class UseItemCommand : public Command
{
public:
    explicit UseItemCommand(GameObject *g) : Command(g) {}
    void use(Item *Target);
    void attack();

protected:
    Item *Target;
    Item *Reward;
    Item *Tool;
    Character *Character;
};

#endif // USEITEMCOMMAND_H
