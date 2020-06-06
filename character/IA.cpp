#include "ICharacter.hpp"

IA::IA(Vector<unsigned int> pos, bool isIa) : Perso{pos, isIa}// :  _pos (pos), _isIa(isIa)
{
   /* _isDead = false;
    _pos = pos;
    _isIa = isIa;*/
}

void IA::move(orientation face)
{
    _prevPos = _pos;
    if (face == NORTH)
        _pos.x--;
    if (face == SOUTH)
        _pos.x++;
    if (face == WEST)
        _pos.y--;
    if (face == EAST)
        _pos.y++;
}
/*
void Player::powerUp(PowerUp power)
{
    if (power == SPEED) {
        _speed++;
    }
    if (power == BOMB_NUMBER) {
        _maxBombs++;
    }
    if (power == BOMB_RADIUS) {
        _bombRadius++;
    }
}*/

bool IA::dropBomb()
{
    if (_maxBombs > _currentBombs.size()) {
  //      Bomb &new_bomb(_bombRadius, _pos);
        _currentBombs.push_back(new Bomb(_bombRadius, _pos));
        std::cout << _currentBombs[0]->getTimeBeforeExplosion() << std::endl;
        return (true);
    }
    return (false);
}
