#include "RoomDefaultEnterCommand.h"
#include "Passage.h"
#include "Player.h"
#include "Room.h"
#include "npc.h"
#include "mob.h"
#include "ZOOrkEngine.h"

int main()
{
    std::shared_ptr<Room> start = std::make_shared<Room>("start-room",
                                                         "You are standing in an open field west of a white house, with a boarded front door.\n");

    std::shared_ptr<Room> south_of_house = std::make_shared<Room>("south-of-house",
                                                                  "You are facing the south side of a white house.  There is no door here, and all the windows are barred.\n");

    std::shared_ptr<Room> behind_house = std::make_shared<Room>("behind-house",
                                                                "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.\n");

    std::shared_ptr<Room> garden = std::make_shared<Room>("garden", "You are in the garden, North of the House. There is a big square on the West and a Forest Path on East.");
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
    Item *torch = new Item("Torch", "A burning torch to light your way.");
    Item *crowbar = new Item("Crowbar", "A sturdy crowbar for prying things open.");
    Item *compass = new Item("Compass", "A navigational tool for finding direction.");

    // Item for gameplay
    // Sword
    Item *sword = new Item("Sword", "With this you can attacke enemy.");

    // Potions
    Item *potion = new Item("Potion", "With this you can heal in battle.");
    // Functional items
    Item *minersPickaxe = new Item("Miner's Pickaxe", "A sturdy pickaxe used for mining.");
    Item *hoe = new Item("Silver Hoe", "Special tool to collect herbs");

    // Tool required to collect item
    Item *mistericHerb = new Item("Misteric Herb", "It look strange. Better take it to Herbalist first");
    mistericHerb->setRequireSearch(true);
    mistericHerb->setCollectable(false);
    mistericHerb->setRequiredItem(hoe->getName());

    Item *mineral = new Item("Mineral", "It look good for weapon. Let's bring it to Blacksmith");
    mineral->setRequireSearch(true);
    mineral->setCollectable(false);
    mineral->setRequiredItem(minersPickaxe->getName());

    // Add items to room

    start->addItem(sword);
    start->addItem(potion);
    behind_house->addItem(torch);
    behind_house->addItem(backpack);
    behind_house->addItem(crowbar);
    behind_house->addItem(compass);
    villageSquare->addItem(minersPickaxe);
    villageSquare->addItem(hoe);
    deeperForest->addItem(mistericHerb);
    abandonedMine->addItem(mineral);

#pragma endregion

#pragma region NPC
    TownElder townElder;
    Herbalist herbalist;
    Blacksmith blacksmith;

    // Set NPC locations
    start->addCharacter(&townElder);
    villageSquare->addCharacter(&herbalist);
    villageSquare->addCharacter(&blacksmith);
#pragma endregion

#pragma region MOB
    ForestImp forestImp;
    FungalShaman fungalShaman;
    DarkWoodNymph darkWoodNymph;
    Goblin goblin;
    RockGolem rockGolem;
    AncientGuardian ancientGuardian;
    AncientDragon ancientDragon;

    forestImp.setHealth(30);
    forestImp.setAttack(10);
    forestImp.setLevel(1);
    forestImp.setAttackable(true);
    forestImp.setRewardType("Herb");
    fungalShaman.setHealth(40);
    fungalShaman.setAttack(20);
    fungalShaman.setLevel(2);
    fungalShaman.setAttackable(true);
    fungalShaman.setRewardType("Herb");
    darkWoodNymph.setHealth(60);
    darkWoodNymph.setAttack(35);
    darkWoodNymph.setLevel(3);
    darkWoodNymph.setAttackable(true);
    darkWoodNymph.setRewardType("Herb");

    goblin.setHealth(30);
    goblin.setAttack(10);
    goblin.setLevel(1);
    goblin.setAttackable(true);
    goblin.setRewardType("Mineral");
    rockGolem.setHealth(60);
    rockGolem.setAttack(15);
    rockGolem.setLevel(2);
    rockGolem.setAttackable(true);
    rockGolem.setRewardType("Mineral");
    ancientGuardian.setHealth(100);
    ancientGuardian.setAttack(20);
    ancientGuardian.setLevel(3);
    ancientGuardian.setAttackable(true);
    ancientGuardian.setRewardType("Mineral");

    ancientDragon.setHealth(200);
    ancientDragon.setAttack(30);
    ancientDragon.setLevel(4);
    ancientDragon.setAttackable(true);
    ancientDragon.setRewardType("Mineral");

    // add to map
    deeperForest->addCharacter(&forestImp);
    deeperForest->addCharacter(&fungalShaman);
    ancientRuin->addCharacter(&fungalShaman);
    enchantedForest->addCharacter(&darkWoodNymph);

    abandonedMine->addCharacter(&goblin);
    abandonedMine->addCharacter(&rockGolem);
    dungeon->addCharacter(&rockGolem);
    dungeon->addCharacter(&ancientGuardian);
    dungeon->addCharacter(&ancientDragon);
#pragma endregion
    ZOOrkEngine zoork(start);

    zoork.run();

    return 0;
}