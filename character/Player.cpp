/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ICharacter
*/

#include "ICharacter.hpp"

Player::Player(Vector<unsigned int> pos, bool isIa) :  Perso{pos, isIa}//_pos(pos), _isIa(isIa)
{
    _isDead = false;
    _maxBombs = 2;
    _speed = 1;
    _bombRadius = 3;
    std::cout << _bombRadius << std::endl;
}

void Player::move(orientation face)
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
}
/*
void Player::dropBomb()
{
    _currentBombs.push_back(Bomb(_bombRadius, _pos));
}*/

bool Player::dropBomb()
{
    std::cout << "current bomb camille la plus belle " << _currentBombs.size() << std::endl;
    
    std::cout << "maxbomb caca le sang " << _maxBombs << std::endl;
    if (_maxBombs > _currentBombs.size()) {


  //      Bomb &new_bomb(_bombRadius, _pos);
        _currentBombs.push_back(new Bomb(_bombRadius, _pos));
        std::cout << _currentBombs[0]->getTimeBeforeExplosion() << std::endl;
        return (true);
    }
    return (false);
}

// int main(void)
// {
//     ICharacter player(Vector<unsigned int>(1,1), false);

//     std::cout << "x => " << player.getX() << " y => " << player.getY() << "\n";
//     player.move(SOUTH);
//     std::cout << "x => " << player.getX() << " y => " << player.getY() << "\n";
//     player.move(WEST);
//     std::cout << "x => " << player.getX() << " y => " << player.getY() << "\n";
//     player.dropBomb();
//     player.move(EAST);
//     std::cout << "x => " << player.getX() << " y => " << player.getY() << "\n";
//     player.dropBomb();
//     player.move(EAST);
//     std::cout << "x => " << player.getX() << " y => " << player.getY() << "\n";

//     int count = 0;
//     while (count < 8) {
//         int i = 0;
//         for (auto &bb : player.getBombs()) {
//             std::cout << "bomb : " << std::to_string(i) << "time => " << bb.shouldExplode() << "\n";
//             i++;
//         }
//         sleep(1.0);
//         count++;
//     }
//     return (0);
// }