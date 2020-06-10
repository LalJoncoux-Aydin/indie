/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Mapp
*/

#include "Map.hpp"

Map::Map(int size)
{
    _size = size;
    _map.resize(_size + 2);
    _bomb_drop = false;
    _compute = false;

    for (int i = 0 ; i <= _size ; ++i) {
        _map[i].resize(_size + 2);
        for (int x = 0 ; x <= _size ; ++x) {
            int value = rand() % 100;
            _map[i][x].element = EMPTY;
            _map[i][x].player = NO_PLAYER;
            _map[i][x].bombState = NO;
            if (i == 0 || i == _size) {
                _map[i][x].element = WALL;
            } else if (x == 0 || x == _size) {
                _map[i][x].element = WALL;
            } else if (x % 2 == 0 && i % 2 == 0){
                _map[i][x].element = INDESTRUCTIBLE_BOX;
            } else if (((i > 2 && i < size - 2) || (x > 2 && x < size - 2)) && (value > 50 || value % 4 == 0)){
                _map[i][x].element = DESTRUCTIBLE_BOX;
                int check = value = rand() % 4 + 1;
                if (value % 3 == 0 || value % 15 == 0) { _map[i][x].powerup = (PowerUp)check;}
                else { _map[i][x].powerup = NO_POWERUP;}
            } else {
                _map[i][x].element = EMPTY;
            }
        }
    }
}

Map::Map(int size, std::vector<std::vector<cell_t>> map)
{
    _size = size;
    _bomb_drop = false;
    _compute = false;
    _map = map;
}

int Map::dropBomb(int xPos, int yPos, int boost, std::vector<ICharacter *> characters)
{
    _map[xPos][yPos].bombState = NO;
    for (auto &perso : characters) {
        auto pos = perso->getPos();
        auto pos_x = pos.x;
        auto pos_y = pos.y;
        for (int x = xPos, count = 0; x < _size && count < 3 + boost; x++, count++) {
            if (_map[x][yPos].element == INDESTRUCTIBLE_BOX) {break;}
            if (_map[x][yPos].element == WALL) {break;}
            if (_map[x][yPos].element == DESTRUCTIBLE_BOX) {
                _map[x][yPos].element = BROKEN_BOX;
            }
            _map[x][yPos].isBoom = true;
            if (pos_x == x && pos_y == yPos) {
                perso->die();
                _map[x][yPos].isDeadBody = true;
                _map[x][yPos].player = NO_PLAYER;
            }
        }
        for (int x = xPos, count = 0; x > 0 && count < 3 + boost; x--, count++) {
            if (_map[x][yPos].element == INDESTRUCTIBLE_BOX) {break;}
            if (_map[x][yPos].element == WALL) {break;}
            if (_map[x][yPos].element == DESTRUCTIBLE_BOX) {
                _map[x][yPos].element = BROKEN_BOX;
            }
            _map[x][yPos].isBoom = true;
            if (pos_x == x && pos_y == yPos) {
                perso->die();
                _map[x][yPos].isDeadBody = true;
                _map[x][yPos].player = NO_PLAYER;
            }
        }
        for (int y = yPos, count = 0; y > 0 && count < 3 + boost; y--, count++) {
            if (_map[xPos][y].element == INDESTRUCTIBLE_BOX) {break;}
            if (_map[xPos][y].element == WALL) {break;}
            if (_map[xPos][y].element == DESTRUCTIBLE_BOX) {
                _map[xPos][y].element = BROKEN_BOX;
            }
            _map[xPos][y].isBoom = true;
            if (pos_x == xPos && pos_y == y) {
                perso->die();
                _map[xPos][y].isDeadBody = true;
                _map[xPos][y].player = NO_PLAYER;
            }
        }
        for (int y = yPos, count = 0; y < _size && count < 3 + boost; y++, count++) {
            if (_map[xPos][y].element == INDESTRUCTIBLE_BOX) {break;}
            if (_map[xPos][y].element == WALL) {break;}
            if (_map[xPos][y].element == DESTRUCTIBLE_BOX) {
                _map[xPos][y].element = BROKEN_BOX;
            }
            _map[xPos][y].isBoom = true;
            if (pos_x == xPos && pos_y == y) {
                perso->die();
                _map[xPos][y].isDeadBody = true;
                _map[xPos][y].player = NO_PLAYER;
            }
        }
    }
    _bomb_drop = true;
    return (true);
}

void Map::clean(PlayerNb p)
{
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            if (_map[i][j].player == p) {
                _map[i][j].player = NO_PLAYER;
                _map[i][j].orient = NO_ORIENT;
            }
        }
    }
}

std::vector<std::vector<cell_t>> Map::update(std::vector<ICharacter *> characters)
{
    int counter = 0;

    for (auto &character : characters) {
        auto pos = character->getPos();
        auto x = pos.x;
        auto y = pos.y;
        ///
        orientation tmp = character->getOrientation();
        ///
        if (counter == 0 && _map[x][y].element == EMPTY) {
            clean(PLAYER1);
            if (_map[x][y].powerup != NO_POWERUP) {character->powerUp(_map[x][y].powerup);}
            _map[x][y].player = PLAYER1;
            _map[x][y].orient = tmp;
        }
        else if (counter == 1 && _map[x][y].element == EMPTY) {
            clean(PLAYER2);
            if (_map[x][y].powerup != NO_POWERUP) {character->powerUp(_map[x][y].powerup);}
            _map[x][y].player = PLAYER2;
            _map[x][y].orient = tmp;
        }
        else if (counter == 2 && _map[x][y].element == EMPTY) {
            clean(PLAYER3);
            if (_map[x][y].powerup != NO_POWERUP) {character->powerUp(_map[x][y].powerup);}
            _map[x][y].player = PLAYER3;
            _map[x][y].orient = tmp;
        }
        else if (counter == 3 && _map[x][y].element == EMPTY) {
            clean(PLAYER4);
            if (_map[x][y].powerup != NO_POWERUP) {character->powerUp(_map[x][y].powerup);}
            _map[x][y].player = PLAYER4;
            _map[x][y].orient = tmp;
        } else {
            character->goToPrevPos();
        }
        auto bombVec = character->getBombs();
        for (auto &bomb : bombVec) {
            if (bomb->isPlaced() == true) {
                continue;
            }
            auto posBomb = bomb->getPos();
            std::cout << _map[posBomb.x][posBomb.y].element << std::endl;
            if (_map[posBomb.x][posBomb.y].element == EMPTY) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION5;
                bomb->place();
            }
        }
        counter++;
    }
    for (auto &character : characters) {
        int i = 0;
        auto bombVec = character->getBombs();
        for (auto &bomb : bombVec) {
            if (bomb->isPlaced() == false) {continue;}
            if (bomb->checkTimerChange() == true) {continue;}
            auto posBomb = bomb->getPos();
            std::cout << "passed time explode NORMAL = " << bomb->getPassedTime() << std::endl;
            if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION5 && bomb->getPassedTime() > 8999) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION4;
                std::cout << "passed time explode 4 = " << bomb->getPassedTime() << std::endl;
                bomb->setPassedTime(0);
            } else if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION4 && bomb->getPassedTime() > 8999) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION3;
                std::cout << "passed time explode 3 = " << bomb->getPassedTime() << std::endl;
                bomb->setPassedTime(0);
            } else if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION3 && bomb->getPassedTime() > 8999) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION2;
                std::cout << "passed time explode 2 = " << bomb->getPassedTime() << std::endl;
                bomb->setPassedTime(0);
            } else if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION2 && bomb->getPassedTime() > 8999) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION1;
                std::cout << "passed time explode 1 = " << bomb->getPassedTime() << std::endl;
                bomb->setPassedTime(0);
            } else if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION1 && bomb->getPassedTime() > 8999) {
                _map[posBomb.x][posBomb.y].bombState == NO;
                dropBomb(posBomb.x, posBomb.y, bomb->getExplosionRadius(), characters);
                std::cout << "deleted !!" << std::endl;
                character->deleteBomb(i);
            } else
                continue;
            i++;
        }
    }
    if (_bomb_drop == true && _compute == true) {
        _bomb_drop = false;
        _compute = false;
        for (int i = 1; i < _size; i++) {
            for (int y = 1; y < _size ; y++) {
                if (_map[i][y].isBoom == true) {
                    _map[i][y].isBoom = false;
                }
            }
        }
        return (_map);
    }
    if (_bomb_drop == true && _compute == false) {
        _compute = true;
        return (_map);
    }
    return (_map);
}


void Map::dump()
{
    for (auto &line : _map) {
        for (auto &cell : line) {
            if (cell.bombState > 0) {std::cout << cell.bombState;}
            // else if (cell.player != NO_PLAYER) std::cout << cell.player;
            else if (cell.element == DESTRUCTIBLE_BOX) std::cout << "B";
            else if (cell.element == INDESTRUCTIBLE_BOX) std::cout << "C";
            else if (cell.element == WALL) std::cout << "W";
            else if (cell.isBoom == true) std::cout << "E";
            else std::cout << " ";
        }
        std::cout << "\n";
    }
}

Map::~Map()
{
}

// #include "Character.hpp"
// #include "ICharacter.hpp"
// #include <unistd.h>

// int main (void)
// {
//     std::vector<Character *> players;

//     players.push_back(new Character(Vector<unsigned int>(1,1), false));
//     players.push_back(new Character(Vector<unsigned int>(1,15), false));
//     players.push_back(new Character(Vector<unsigned int>(15,1), false));
//     players.push_back(new Character(Vector<unsigned int>(15,15), false));

//     Map map(16);
//     // map.dump();
//     // std::cout << map.dropBomb(4,5,0, players) << "\n";
//     // std::cout << map.dropBomb(1,1,10, players) << "\n";
//     players[0]->dropBomb();
//     players[0]->dropBomb();

//     std::cout << "true => " << true << "false => " << false << "\n";
//     // for (auto bombvec : players[0]->getBombs()) {
//     //     std::cout << "Isplaced => " << bombvec->isPlaced() << "\n";
//     // }
//     // for (auto bombvec : players[0]->getBombs()) {
//     //     bombvec->place();
//     // }
//     // for (auto bombvec : players[0]->getBombs()) {
//     //     std::cout << "Isplaced => " << bombvec->isPlaced() << "\n";
//     // }
//     auto bomb = players[0]->getBombs();
//     std::cout << bomb.size();
//     int i = 0;
//     while (i < 7) {
//         map.dump();
//         map.update(players);
//         map.update(players);
//         map.dump();
//         sleep(1);
//         i++;
//     }
// }
