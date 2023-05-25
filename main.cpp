#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "npc.h"
#include "ZOOrkEngine.h"
#include "UseItemCommand.h"

int main()
{
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                                                         "You are standing in an open field west of a white house, with a boarded front door.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                                                                  "You are facing the south side of a white house.  There is no door here, and all the windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                                                                "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");

    std::shared_ptr<Room> garden = std::make_shared<Room>("garden", "You are in the garden, North of the House. There is a big square on the West.");
    std::shared_ptr<Room> villageSquare = std::make_shared<Room>("village-square", "You are in the village square.");

    std::shared_ptr<Room> forestPath = std::make_shared<Room>("forest-path", "You are on the forest path. There are two paths in front of you. East: Abandoned-Mine | North: Deeper Forest.");
    std::shared_ptr<Room> abandonedMine = std::make_shared<Room>("abandoned-mine", "You are in the abandoned mine. There is a strange gate to the East.");
    std::shared_ptr<Room> dungeon = std::make_shared<Room>("dungeon", "You are in the dungeon.");

    std::shared_ptr<Room> deeperForest = std::make_shared<Room>("deeper-forest", "You are in the deeper forest. It is dark here. There is some light to the North.");
    std::shared_ptr<Room> ancientRuin = std::make_shared<Room>("ancient-ruin", "You are in the ancient ruin. There is a small path to the East.");
    std::shared_ptr<Room> enchantedForest = std::make_shared<Room>("enchanted-forest", "You are in the enchanted forest.");

// Create Passage
#pragma region CreatePassage

    Passage::createBasicPassage(start.get(), south_of_house.get(), "south", true);

    Passage::createBasicPassage(start.get(), behind_house.get(), "west", true);

    Passage::createBasicPassage(start.get(), garden.get(), "north", true);

    Passage::createBasicPassage(garden.get(), villageSquare.get(), "west", true);

    Passage::createBasicPassage(garden.get(), forestPath.get(), "east", true);

    Passage::createBasicPassage(forestPath.get(), abandonedMine.get(), "east", true);

    Passage::createBasicPassage(abandonedMine.get(), dungeon.get(), "east", true);

    Passage::createBasicPassage(forestPath.get(), deeperForest.get(), "north", true);

    Passage::createBasicPassage(deeperForest.get(), ancientRuin.get(), "north", true);

    Passage::createBasicPassage(ancientRuin.get(), enchantedForest.get(), "east", true);
#pragma endregion

    // Create and add Items
#pragma region CreateAndAddItem

    // std::shared_ptr<Item> test = std::make_shared<Item>("enchanted-forest", "You are in the enchanted forest.");
    // test->setDuration(10);
    // std::shared_ptr<UseItemCommand> testCommand = std::make_shared<UseItemCommand>(test.get());
    // testCommand->addTargetObject(/*whatever you want the target object to be*/);
    // test->setUseCommand(testCommand);

    Item *backpack = new Item("Backpack", "A tool used for store items.");
    backpack->setRequireSearch(false);
    Item *torch = new Item("Torch", "A burning torch to light your way.");
    torch->setRequireSearch(false);
    Item *crowbar = new Item("Crowbar", "A sturdy crowbar for prying things open.");
    crowbar->setRequireSearch(false);
    Item *compass = new Item("Compass", "A navigational tool for finding direction.");
    compass->setRequireSearch(false);

    // Item for gameplay
    // Sword
    std::shared_ptr<Item> sword1 = std::make_shared<Item>("Starter Sword", "A basic sword for beginners.");
    sword1->setRequireSearch(false);
    sword1->setCollectable(true);

    std::shared_ptr<Item> sword2 = std::make_shared<Item>("Common Sword", "A reliable sword commonly found in the realm.");
    sword2->setRequireSearch(false);
    sword2->setCollectable(false);
    std::shared_ptr<Item> sword3 = std::make_shared<Item>("Rare Sword", "A rare and powerful sword sought after by adventurers.");
    sword3->setRequireSearch(false);
    sword3->setCollectable(false);
    std::shared_ptr<Item> sword4 = std::make_shared<Item>("Epic Sword", "An epic sword with legendary qualities, capable of slaying powerful foes.");
    sword4->setRequireSearch(false);
    sword4->setCollectable(false);
    std::shared_ptr<Item> sword5 = std::make_shared<Item>("A legendary sword of immense power, rumored to have been forged by the gods themselves.");
    sword5->setRequireSearch(false);
    sword5->setCollectable(false);

    // Potion
    std::shared_ptr<Item> potion1 = std::make_shared<Item>("Starter Potion", "A basic potion to restore a small amount of health.");
    potion1->setRequireSearch(false);
    potion1->setCollectable(true);

    std::shared_ptr<Item> potion2 = std::make_shared<Item>("Common Potion", "A common potion that replenishes moderate health.");
    potion2->setRequireSearch(false);
    potion2->setCollectable(false);
    std::shared_ptr<Item> potion3 = std::make_shared<Item>("Rare Potion", "A rare potion known for its potent healing properties.");
    potion3->setRequireSearch(false);
    potion3->setCollectable(false);
    std::shared_ptr<Item> potion4 = std::make_shared<Item>("Epic Potion", "An epic potion that can fully restore health and provide temporary boosts.");
    potion4->setRequireSearch(false);
    potion4->setCollectable(false);
    std::shared_ptr<Item> potion5 = std::make_shared<Item>("Legendary Potion", "A legendary elixir said to grant immortality, healing all wounds and bestowing great power.");
    potion5->setRequireSearch(false);
    potion5->setCollectable(false);

    // Functional item
    std::shared_ptr<Item> minersPickaxe = std::make_shared<Item>("Miner's Pickaxe", "A sturdy pickaxe used for mining.");
    minersPickaxe->setRequireSearch(false);
    minersPickaxe->setCollectable(true);
    minersPickaxe->setDuration(10);
    std::shared_ptr<UseItemCommand> pickaxeCmd = std::make_shared<UseItemCommand>(minersPickaxe.get());
    minersPickaxe->setUseCommand(pickaxeCmd);

    std::shared_ptr<Item> hoe = std::make_shared<Item>("Silver Hoe", "Special tool to collect herb");
    hoe->setRequireSearch(false);
    hoe->setCollectable(true);
    hoe->setDuration(10);
    std::shared_ptr<UseItemCommand> hoeCmd = std::make_shared<UseItemCommand>(hoe.get());
    hoe->setUseCommand(hoeCmd);

    // Tool required to collect item
    Item *mistericHerb = new Item("Misteric Herb", "It look strange. Better take it to Herbalist first");
    mistericHerb->setRequireSearch(true);
    mistericHerb->setCollectable(false);

    Item *mineral = new Item("Mineral", "It look good for weapon. Let's bring it to Blacksmith");
    mineral->setRequireSearch(true);
    mineral->setCollectable(false);

    // Add items to room
    behind_house->addItem(torch);
    behind_house->addItem(backpack);
    behind_house->addItem(crowbar);
    behind_house->addItem(compass);
    villageSquare->addItem(minersPickaxe.get());
    villageSquare->addItem(hoe.get());
    deeperForest->addItem(mistericHerb);
    abandonedMine->addItem(mineral);

    start->addItem(sword1.get());
    start->addItem(potion1.get());

    // add item to room theese item required upgrade to get
    villageSquare->addItem(sword2.get());
    villageSquare->addItem(potion2.get());
    villageSquare->addItem(sword3.get());
    villageSquare->addItem(potion3.get());
    villageSquare->addItem(sword4.get());
    villageSquare->addItem(potion4.get());
    villageSquare->addItem(sword5.get());
    villageSquare->addItem(potion5.get());

#pragma endregion

#pragma region NPC
    TownElder townElder;
    Herbalist herbalist;
    Blacksmith blacksmith;
    MysteriousStranger mysteriosStranger;

    // Set NPC locations
    start->addCharacter(&townElder);
    behind_house->addCharacter(&herbalist);
    villageSquare->addCharacter(&blacksmith);
    ancientRuin->addCharacter(&mysteriosStranger);
#pragma endregion
    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}
