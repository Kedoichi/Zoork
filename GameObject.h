//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_GAMEOBJECT_H
#define ZOORK_GAMEOBJECT_H

#include <string>

class GameObject {
public:
    GameObject(const std::string &, const std::string &);

    std::string getName() const;

    void setName(const std::string &);

    std::string getDescription() const;

    void setDescription(const std::string &);

protected:
    std::string name;
    std::string description;
};


#endif //ZOORK_GAMEOBJECT_H
