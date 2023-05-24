//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "Character.h"
#include "RoomDefaultEnterCommand.h"
#include "Item.h"
#include "Location.h"
#include <map>

class Passage;

class Room : public Location {
public:
    Room(const std::string &, const std::string &);

    Room(const std::string &, const std::string &, std::shared_ptr<Command>);

    void addItem(Item*);
    void removeItem(const std::string&);
    Item* getItem(const std::string&);
    Item* retrieveItem(const std::string&);
    void addCharacter(Character*);
    void removeCharacter(const std::string&);
    Character* getCharacter(const std::string&);

    void addPassage(const std::string &, std::shared_ptr<Passage>);

    void removePassage(const std::string &);
    std::vector<Item*> getItems() const {
        return items;
    }
    std::shared_ptr<Passage> getPassage(const std::string &);
    std::string getDescription() const;
    std::string search() const;

protected:
    std::vector<Item*> items;
    std::vector<Character*> characters;


    std::map<std::string, std::shared_ptr<Passage> > passageMap;
};


#endif //ZOORK_ROOM_H
