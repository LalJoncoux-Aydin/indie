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

std::vector<int> Map::dropBomb(int xPos, int yPos, std::shared_ptr<Bomb> bomb)
{
    std::vector<int> result;
    unsigned int bomb_rad = bomb->getExplosionRadius();
    for (int i = 1; i != bomb_rad + 1 && xPos - i >= 0 && xPos + i <= 16 && yPos - i >= 0 && yPos + i <= 16; i++) {
        if (_map[xPos - i][yPos].element == DESTRUCTIBLE_BOX) {
            _map[xPos - i][yPos].element = BROKEN_BOX;
            return result;
        } else if (!(_map[xPos - i][yPos].element == WALL) && !(_map[xPos - i][yPos].element == INDESTRUCTIBLE_BOX) && _map[xPos - i][yPos].player == NO_PLAYER) {
            _map[xPos - i][yPos].element = BURNING;
        } else if (!(_map[xPos - i][yPos].player == NO_PLAYER)) {
            if (_map[xPos - i][yPos].player == PLAYER1)
                result.push_back(1);
            if (_map[xPos - i][yPos].player == PLAYER2)
                result.push_back(2);
            if (_map[xPos - i][yPos].player == PLAYER3)
                result.push_back(3);
            if (_map[xPos - i][yPos].player == PLAYER4)
                result.push_back(4);
        }

        if (_map[xPos + i][yPos].element == DESTRUCTIBLE_BOX) {
            _map[xPos + i][yPos].element = BROKEN_BOX;
            return result;
        } else if (!(_map[xPos + i][yPos].element == WALL) && !(_map[xPos + i][yPos].element == INDESTRUCTIBLE_BOX) && _map[xPos + i][yPos].player == NO_PLAYER) {
            _map[xPos + i][yPos].element = BURNING;
        } else if (!(_map[xPos + i][yPos].player == NO_PLAYER)) {
            if (_map[xPos + i][yPos].player == PLAYER1)
                result.push_back(1);
            if (_map[xPos + i][yPos].player == PLAYER2)
                result.push_back(2);
            if (_map[xPos + i][yPos].player == PLAYER3)
                result.push_back(3);
            if (_map[xPos + i][yPos].player == PLAYER4)
                result.push_back(4);
        }

        if (_map[xPos][yPos - i].element == DESTRUCTIBLE_BOX) {
            _map[xPos][yPos - i].element = BROKEN_BOX;
            return result;
        } else if (!(_map[xPos][yPos - i].element == WALL) && !(_map[xPos][yPos - i].element == INDESTRUCTIBLE_BOX) && _map[xPos][yPos - i].player == NO_PLAYER) {
            _map[xPos][yPos - i].element = BURNING;
        } else if (!(_map[xPos][yPos - i].player == NO_PLAYER)) {
            if (_map[xPos][yPos - i].player == PLAYER1)
                result.push_back(1);
            if (_map[xPos][yPos - i].player == PLAYER2)
                result.push_back(2);
            if (_map[xPos][yPos - i].player == PLAYER3)
                result.push_back(3);
            if (_map[xPos][yPos - i].player == PLAYER4)
                result.push_back(4);
        }

        if (_map[xPos][yPos + i].element == DESTRUCTIBLE_BOX) {
            _map[xPos][yPos + i].element = BROKEN_BOX;
            return result;
        } else if (!(_map[xPos][yPos + i].element == WALL) && !(_map[xPos][yPos + i].element == INDESTRUCTIBLE_BOX) && _map[xPos][yPos + i].player == NO_PLAYER) {
            _map[xPos][yPos + i].element = BURNING;
        } else if (!(_map[xPos][yPos + i].player == NO_PLAYER)) {
            if (_map[xPos][yPos + i].player == PLAYER1)
                result.push_back(1);
            if (_map[xPos][yPos + i].player == PLAYER2)
                result.push_back(2);
            if (_map[xPos][yPos + i].player == PLAYER3)
                result.push_back(3);
            if (_map[xPos][yPos + i].player == PLAYER4)
                result.push_back(4);
        }
    }
    return result;
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

void Map::initPlayer(std::vector<ICharacter *> characters)
{
    int counter = 0;
    for (auto &character : characters) {
        auto pos = character->getPos();
        auto x = pos.x;
        auto y = pos.y;

        // Player
        if (counter == 0 && _map[x][y].element == EMPTY)
            _map[x][y].player = PLAYER1;
        else if (counter == 1 && _map[x][y].element == EMPTY)
            _map[x][y].player = PLAYER2;
        else if (counter == 2 && _map[x][y].element == EMPTY)
            _map[x][y].player = PLAYER3;
        else if (counter == 3 && _map[x][y].element == EMPTY)
            _map[x][y].player = PLAYER4;
        counter++;
    }
}

std::vector<std::vector<cell_t>> Map::update(std::vector<ICharacter *> characters)
{
    // FILL WALLS
    for (int i = 0 ; i <= _size ; ++i) {
        for (int x = 0 ; x <= _size ; ++x) {
            // Walls
            if (_map[i][x].element == BROKEN_BOX || _map[i][x].element == BURNING)
                _map[i][x].element = EMPTY;
            if (_map[i][x].isDeadBody == true) {
                _map[i][x].player = NO_PLAYER;
                _map[i][x].isDeadBody = false;
            }
            if (_map[i][x].bombState == HAS_EXPLODED)
                _map[i][x].bombState = NO;
        }
    }

    // FILL CHARACTER
    int counter = 0;
    for (auto &character : characters) {
        auto pos = character->getPos();
        auto x = pos.x;
        auto y = pos.y;

        // Orientation
        orientation tmp = character->getOrientation();

        // Player
        if (counter == 0 && _map[x][y].element == EMPTY && _map[x][y].player != PLAYER2 && _map[x][y].player != PLAYER3 && _map[x][y].player != PLAYER4 && character->isDead() == false) {
            clean(PLAYER1);
          //  if (_map[x][y].powerup != NO_POWERUP) {character->powerUp(_map[x][y].powerup);}
            _map[x][y].player = PLAYER1;
            _map[x][y].orient = tmp;
        }
        else if (counter == 1 && _map[x][y].element == EMPTY && _map[x][y].player != PLAYER1 && _map[x][y].player != PLAYER3 && _map[x][y].player != PLAYER4 && character->isDead() == false) {
            clean(PLAYER2);
         //   if (_map[x][y].powerup != NO_POWERUP) {character->powerUp(_map[x][y].powerup);}
            _map[x][y].player = PLAYER2;
            _map[x][y].orient = tmp;
        }
        else if (counter == 2 && _map[x][y].element == EMPTY && _map[x][y].player != PLAYER1 && _map[x][y].player != PLAYER2 && _map[x][y].player != PLAYER4  && character->isDead() == false) {
            clean(PLAYER3);
         //   if (_map[x][y].powerup != NO_POWERUP) {character->powerUp(_map[x][y].powerup);}
            _map[x][y].player = PLAYER3;
            _map[x][y].orient = tmp;
        }
        else if (counter == 3 && _map[x][y].element == EMPTY && _map[x][y].player != PLAYER1 && _map[x][y].player != PLAYER2 && _map[x][y].player != PLAYER3  && character->isDead() == false) {
            clean(PLAYER4);
        //    if (_map[x][y].powerup != NO_POWERUP) {character->powerUp(_map[x][y].powerup);}
            _map[x][y].player = PLAYER4;
            _map[x][y].orient = tmp;
        } else {
            character->goToPrevPos();
        }

        // Bomb
        auto bomb = character->getBombs();
        if (bomb->isPlaced() == true) {
            auto posBomb = bomb->getPos();
            if (_map[posBomb.x][posBomb.y].bombState == NO) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION5;
                bomb->setPlace(true);
            }
            if (bomb->getPassedTime() == 0)
                bomb->setTimePass();
            std::size_t _diff = bomb->timePass() - bomb->getPassedTime();
            if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION5 && _diff > 500) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION4;
                bomb->setPassedTime(0);
            } else if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION4 && _diff > 500) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION3;
                bomb->setPassedTime(0);
            } else if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION3 && _diff > 500) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION2;
                bomb->setPassedTime(0);
            } else if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION2 && _diff > 500) {
                _map[posBomb.x][posBomb.y].bombState = EXPLOSION1;
                bomb->setPassedTime(0);
            } else if (_map[posBomb.x][posBomb.y].bombState == EXPLOSION1 && _diff > 500) {
                _map[posBomb.x][posBomb.y].bombState = HAS_EXPLODED;
                std::vector<int> player_dead = dropBomb(posBomb.x, posBomb.y, bomb);
                if (!player_dead.empty()) {
                    for (int a = 0; player_dead[a]; a++) {
                        if (player_dead[a] != 0) {
                            characters[player_dead[a] - 1]->die();
                            auto dead_pos = characters[player_dead[a] - 1]->getPos();
                            _map[dead_pos.x][dead_pos.y].isDeadBody = true;
                        }
                    }
                }
                bomb->setPlace(false);
            }
        }
        counter++;
    }
    return (_map);
}

Map::~Map()
{
}
