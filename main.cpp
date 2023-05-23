#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "ZOOrkEngine.h"

int main()
{
std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                                                         "You are standing in an open field west of a white house, with a boarded front door.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                                                                  "You are facing the south side of a white house.  There is no door here, and all the windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                                                                "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");

    std::shared_ptr<Room> garden = std::make_shared<Room>("garden", "You are in the garden. The Village Square is on the south of the garden.");
    std::shared_ptr<Room> villageSquare = std::make_shared<Room>("village-square", "You are in the village square.");

    std::shared_ptr<Room> forestPath = std::make_shared<Room>("forest-path", "You are on the forest path. There are two paths in front of you. East: Abandoned-Mine | North: Deeper Forest.");
    std::shared_ptr<Room> abandonedMine = std::make_shared<Room>("abandoned-mine", "You are in the abandoned mine. There is a strange gate to the East.");
    std::shared_ptr<Room> dungeon = std::make_shared<Room>("dungeon", "You are in the dungeon.");

    std::shared_ptr<Room> deeperForest = std::make_shared<Room>("deeper-forest", "You are in the deeper forest. It is dark here. There is some light to the North.");
    std::shared_ptr<Room> ancientRuin = std::make_shared<Room>("ancient-ruin", "You are in the ancient ruin. There is a small path to the East.");
    std::shared_ptr<Room> enchantedForest = std::make_shared<Room>("enchanted-forest", "You are in the enchanted forest.");

    Passage::createBasicPassage(start.get(), south_of_house.get(), "south", true);
    Passage::createBasicPassage(south_of_house.get(), behind_house.get(), "east", true);

    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
