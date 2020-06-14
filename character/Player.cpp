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
    _speed = 1;
    _bombRadius = 3;
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

// void Player::powerUp(PowerUp power)
// {
//     if (power == SPEED) {
//         _speed++;
//     }
//     if (power == BOMB_RADIUS) {
//         _bombRadius++;
//     }
// }
