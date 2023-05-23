//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_COMMAND_H
#define ZOORK_COMMAND_H

#include "GameObject.h"
#include <iostream>

class Command {
public:
    explicit Command(GameObject* g) : gameObject(g) {}

    virtual ~Command() = default;

    virtual void execute() = 0;

protected:
    GameObject* gameObject;
};

#endif //ZOORK_COMMAND_H
