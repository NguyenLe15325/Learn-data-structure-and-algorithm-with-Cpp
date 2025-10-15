#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

// Forward declaration for the Room class to be used in the Game class.
class Room;

// Abstract Character class - a blueprint for all combatants.
class Character {
protected:
    std::string name;
    int health;
    int attackPower;
public:
    Character(std::string n, int h, int ap) : name(n), health(h), attackPower(ap) {}
    virtual ~Character() = default;
    virtual void attack(Character& target) = 0;
    void takeDamage(int damage) { health -= damage; if (health < 0) health = 0; }
    std::string getName() const { return name; }
    int getHealth() const { return health; }
    bool isAlive() const { return health > 0; }
};

// Player class inherits from Character.
class Player : public Character {
public:
    Player(std::string n, int h, int ap) : Character(n, h, ap) {}
    void attack(Character& target) override {
        int damage = attackPower + (rand() % 5);
        std::cout << getName() << " attacks " << target.getName() << " for " << damage << " damage!" << std::endl;
        target.takeDamage(damage);
    }
};

// Monster class inherits from Character.
class Monster : public Character {
private:
    int goldDrop;
public:
    Monster(std::string n, int h, int ap, int drop) : Character(n, h, ap), goldDrop(drop) {}
    void attack(Character& target) override {
        int damage = attackPower;
        std::cout << getName() << " attacks " << target.getName() << " for " << damage << " damage!" << std::endl;
        target.takeDamage(damage);
    }
    int getGoldDrop() const { return goldDrop; }
};

// Room class - a single location in the dungeon.
class Room {
public:
    Character* monster = nullptr;
    std::string description;
    Room(std::string desc, Character* m = nullptr) : description(desc), monster(m) {}
};

// Game class - the main game engine.
class Game {
private:
    Player player;
    std::vector<std::vector<Room>> dungeon;
    int playerX, playerY;

    void battle(Character& enemy) {
        std::cout << "\nA " << enemy.getName() << " blocks your path! Battle begins!" << std::endl;
        while (player.isAlive() && enemy.isAlive()) {
            player.attack(enemy);
            if (!enemy.isAlive()) break;
            enemy.attack(player);
            if (!player.isAlive()) break;
        }
        if (player.isAlive()) {
            std::cout << "\nYou defeated the " << enemy.getName() << "!" << std::endl;
            Monster* defeatedMonster = dynamic_cast<Monster*>(&enemy);
            if (defeatedMonster) {
                std::cout << "You found " << defeatedMonster->getGoldDrop() << " gold!" << std::endl;
            }
            dungeon[playerY][playerX].monster = nullptr; // Monster is gone.
        } else {
            std::cout << "\nYou have been defeated by the " << enemy.getName() << "!" << std::endl;
        }
    }

public:
    Game() : player("Hero", 100, 15), playerX(0), playerY(0) {
        srand(time(0));
        // Simple 3x3 dungeon map initialization.
        dungeon.resize(3, std::vector<Room>(3, Room("An empty room.")));
        dungeon[0][0].description = "The starting room. A path leads east and south.";
        dungeon[0][1] = Room("A corridor with a large spider.", new Monster("Spider", 20, 5, 5));
        dungeon[0][2] = Room("A treasure room! The path leads west.", new Monster("Goblin", 30, 8, 25));
        dungeon[1][0] = Room("A damp, stone passage.", new Monster("Slime", 15, 3, 2));
        dungeon[1][1] = Room("A crossroads. Paths lead in all four directions.");
        dungeon[1][2] = Room("A dead end.", new Monster("Rat", 10, 2, 1));
        dungeon[2][0] = Room("A dark chamber. You can go north or east.", new Monster("Orc", 40, 12, 50));
        dungeon[2][1] = Room("An eerie library. You can move west or east.", new Monster("Skeleton", 25, 7, 10));
        dungeon[2][2] = Room("The final room! A dragon sleeps here.", new Monster("Dragon", 100, 20, 100));
    }

    void play() {
        std::cout << "Welcome to the Simple Dungeon Crawler!" << std::endl;

        while (player.isAlive()) {
            Room& currentRoom = dungeon[playerY][playerX];
            std::cout << "\n--- Your Location ---" << std::endl;
            std::cout << currentRoom.description << std::endl;
            std::cout << "Health: " << player.getHealth() << std::endl;

            if (currentRoom.monster) {
                std::cout << "A " << currentRoom.monster->getName() << " stands here, with " << currentRoom.monster->getHealth() << " health." << std::endl;
                battle(*currentRoom.monster);
                if (!player.isAlive()) break;
            }

            if (playerX == 2 && playerY == 2 && !currentRoom.monster) {
                std::cout << "\nCongratulations! You have defeated the dragon and won the game!" << std::endl;
                break;
            }

            char move;
            std::cout << "\nWhat do you do? (n/s/e/w to move): ";
            std::cin >> move;
            
            int newX = playerX, newY = playerY;
            if (move == 'n' && playerY > 0) newY--;
            else if (move == 's' && playerY < 2) newY++;
            else if (move == 'e' && playerX < 2) newX++;
            else if (move == 'w' && playerX > 0) newX--;
            else std::cout << "You cannot move in that direction." << std::endl;

            playerX = newX;
            playerY = newY;
        }

        if (!player.isAlive()) {
            std::cout << "\nGame Over. You have been slain." << std::endl;
        }
    }
};

int main() {
    Game dungeonGame;
    dungeonGame.play();
    return 0;
}