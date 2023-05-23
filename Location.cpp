//
// Created by Richard Skarbez on 5/7/23.
//

#include "Location.h"

Location::Location(const std::string &n, const std::string &d) : GameObject(n, d),
                                                                 enterCommand(std::make_shared<NullCommand>()) {}

Location::Location(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : GameObject(n, d),
                                                                                             enterCommand(
                                                                                                 std::move(c)) {}

void Location::enter()
{
    enterCommand->execute();
}
std::string Location::getDescription() const {
    return description;
}
void Location::setEnterCommand(std::shared_ptr<Command> c)
{
    enterCommand = std::move(c);
}