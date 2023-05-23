//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_LOCATION_H
#define ZOORK_LOCATION_H

#include "Command.h"
#include "GameObject.h"
#include "NullCommand.h"

class Location : public GameObject {
public:
    Location(const std::string &, const std::string &);

    Location(const std::string &, const std::string &, std::shared_ptr<Command>);

    virtual void enter();

    void setEnterCommand(std::shared_ptr<Command>);

protected:
    std::shared_ptr<Command> enterCommand;
};

#endif //ZOORK_LOCATION_H
