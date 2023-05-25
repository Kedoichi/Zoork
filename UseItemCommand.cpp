#include "UseItemCommand.h"
#include "Item.h"
#include "Player.h"
using namespace std;

void UseItemCommand::use(Item *Target)
{
    std::string itemName = static_cast<Item *>(gameObject)->getName();
    std::string targetName = Target->getName();
    static_cast<Item *>(gameObject)->decreaseDuration();
    if (static_cast<Item *>(gameObject)->getDuration() <= 2)
    {
        cout << "The item is almost broken. Bring it to Blacksmith to repair !!!";
    }

    if (itemName == "Miner's Pickaxe")
    {
        if (targetName != "Mineral")
        {
            cout << "This tool cannot be use on " << targetName << " !!!";
            return;
        }
        else
        {
            cout << "You use " << itemName << " on " << targetName << endl;
            cout << "You get 1 Mineral" << endl;
            Player::instance()->increateMineralPoint();
            return;
        }
    }
    if (itemName == "Miner's Pickaxe")
    {
        if (targetName != "Misteric Herb")
        {
            cout << "This tool cannot be use on " << targetName << " !!!";
            return;
        }
        else
        {
            cout << "You use " << itemName << " on " << targetName << endl;
            cout << "You get 1 Mineral" << endl;
            Player::instance()->increateMineralPoint();
            return;
        }
    }
}

void UseItemCommand::attack()
{
    int playerDamage, playerHP;
    int targetDamage, targerHP;
    bool isAtkable;
    bool doHavePotion = false;

    // Get player stats and target stats
    isAtkable = Character->getAttackable();
    playerDamage = Player::instance()->getDamage();
    playerHP = Player::instance()->getHealth();
    targetDamage = Character->getDamage();
    targerHP = Character->getHealth();

    for (Item *playerItem : Player::instance()->getInventory())
    {
        if (playerItem->getName() == "Misteric Potion")
        {
            doHavePotion = true;
            break;
        }
    }

    // Logic is the player hit target first then the target attacke then.
    // If one of them still have HP. They can able to attack

    if (isAtkable)
    {
        do
        {
            std::cout << "Choose an action: " << std::endl;
            std::cout << "1. Attack" << std::endl;
            std::cout << "2. Use Potion" << std::endl;
            std::cout << "3. Run" << std::endl;

            int choice;
            std::cin >> choice;
            switch (choice)
            {
            case 1:
                targerHP -= playerDamage;
                if (targerHP <= 0)
                {
                    int coin = getRandomNumber(10, 50);
                    std::cout << "You win" << std::endl;
                    std::cout << "You get " << coin << " coins" << std::endl;
                }
                else
                {
                    std::cout << "You hit the target with " << playerDamage << ".\n"
                              << Character->getName() << "'s HP remain: " << targerHP << "!\n";
                }
                playerHP -= targetDamage;
                if (playerHP <= 0)
                {
                    std::cout << "You die" << std::endl;
                }
                else
                {
                    std::cout << Character->getName() << " hit you with " << targetDamage << ".\nYour HP remain: " << playerHP << "!\n";
                }
                break;
            case 2:
                if (doHavePotion)
                {
                    playerHP += getRandomNumber(5, 20);
                    std::cout << "You use potion. Your HP is now: " << playerHP << std::endl;
                }
                else
                {
                    std::cout << "You don't have any potion" << std::endl;
                }
                break;
            case 3:
                if (getRandomNumber(1, 5) == 1)
                {
                    std::cout << "You run away" << std::endl;
                    break;
                }
                else
                {
                    playerHP -= targetDamage;
                    if (playerHP <= 0)
                    {
                        std::cout << "You die" << std::endl;
                    }
                    else
                    {
                        std::cout << Character->getName() << " hit you with " << targetDamage << ".\nYour HP remain: " << playerHP << "!\n";
                    }
                    break;
                }
                break;
            default:
                std::cout << "Invalid choice" << std::endl;
                break;
            }
        } while (targerHP > 0 or playerHP > 0);
    }
}

int getRandomNumber(int min, int max)
{
    // Providing a seed value
    srand((unsigned)time(NULL));

    // Get a random number
    int random = rand() % (max - min + 1);

    return random + min;
}