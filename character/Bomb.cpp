/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include <stdlib.h>
#include <time.h>
#include "ICharacter.hpp"

Bomb::Bomb(unsigned int size, Vector<unsigned int> pos)
{
    _timePlaced = time(NULL);
    _pos = pos;
    _explosionRadius = size;
    _lastCheck = _timePlaced;
    _placed = false;
}

Bomb::Bomb(unsigned int time)
{
    _timePlaced = time;
    _lastCheck = _timePlaced;
}

Bomb::~Bomb()
{
}

void Bomb::timePass()
{
    std::chrono::high_resolution_clock::time_point _timepoint = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(_timepoint.time_since_epoch());
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
    _time = ms.count() % 10000;
}

int Bomb::getPassedTime()
{
    return _time;
}

bool Bomb::checkTimerChange()
{
    unsigned int tmp = time(NULL);

    if (tmp -_lastCheck >= 1) {
        _lastCheck = tmp;
        return true;
    }
    return false;
}

bool Bomb::shouldExplode()
{
    if (time(NULL) - _timePlaced >= 5)
        return true;
    return false;
}

void Bomb::place()
{
    _placed = true;
}