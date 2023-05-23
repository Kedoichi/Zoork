//
// Created by Richard Skarbez on 5/7/23.
//

#ifndef ZOORK_PASSAGE_H
#define ZOORK_PASSAGE_H

#include "NullRoom.h"
#include "Room.h"
#include <iostream>

class Passage : public Location {
public:
    static void
    createBasicPassage(Room*, Room*, const std::string &, bool);

    Passage(const std::string &, const std::string &, Room*, Room*);

    Passage(const std::string &, const std::string &, std::shared_ptr<Command>, Room*, Room*);

    void setFrom(Room*);

    Room* getFrom() const;

    void setTo(Room*);

    Room* getTo() const;

protected:
    static std::string oppositeDirection(const std::string &);

    Room* fromRoom;
    Room* toRoom;
};

#endif //ZOORK_PASSAGE_H
