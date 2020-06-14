#include "ICharacter.hpp"

IA::IA(Vector<unsigned int> pos, bool isIa) : Perso{pos, isIa}// :  _pos (pos), _isIa(isIa)
{
    _isDead = false;
    _speed = 1;
    _bombRadius = 3;
}

static int checkBomb(std::vector<std::vector<cell_t>> map, unsigned int savedX, unsigned int savedY)
{
    for (int x = savedX; x > 0; x--) {
        if (map[x][savedY].element == INDESTRUCTIBLE_BOX) {break;}
        if (map[x][savedY].bombState != NO) {
            return (1);
        }
    }
    for (int x = savedX; map[x].size() < x; x++) {
        if (map[x][savedY].element == INDESTRUCTIBLE_BOX) {break;}
        if (map[x][savedY].bombState != NO) {
            return (1);
        }
    }
    for (int y = savedY; map[savedX].size() < y; y++) {
        if (map[savedX][y].element == INDESTRUCTIBLE_BOX) {break;}
        if (map[savedX][y].bombState != NO) {
            return (1);
        }
    }
    for (int y = savedY; y > 0; y++) {
        if (map[savedX][y].element == INDESTRUCTIBLE_BOX) {break;}
        if (map[savedX][y].bombState != NO) {
            return (1);
        }
    }
    return (0);
}

void IA::move(std::vector<std::vector<cell_t>> map)
{
    if (checkBomb(map, _pos.x, _pos.y) == 0 && _currentBombs->isPlaced() == false) {
        _currentBombs->setPos(_pos);
        _currentBombs->setPlace(true);
        _currentBombs->setExplosionRadius(_bombRadius);
        _currentBombs->setTimePass();
    }
    int direction = 0;
    for (int i = 0; i < 3; i++) {
        int wichOne = std::rand() % 3;
        if (wichOne == 0 && map[_pos.x + 1][_pos.y].element == EMPTY && last_direction != 2) {
            _pos.x++;
            direction = 1;
            break;
        }
        if (wichOne == 1 && map[_pos.x - 1][_pos.y].element == EMPTY && last_direction != 1) {
            _pos.x--;
            direction = 2;
            break;
        }
        if (wichOne == 2 && map[_pos.x][_pos.y - 1].element == EMPTY && last_direction != 4) {
            _pos.y--;
            direction = 3;
            break;
        }
        if (wichOne == 3 && map[_pos.x][_pos.y + 1].element == EMPTY && last_direction != 3) {
            _pos.y++;
            direction = 4;
            break;
        }
    }
    last_direction = direction;
}
