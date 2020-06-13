/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include <stdlib.h>
#include <time.h>
#include "ICharacter.hpp"

std::size_t Bomb::timePass()
{
    std::chrono::high_resolution_clock::time_point _timepoint = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(_timepoint.time_since_epoch());
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
    std::size_t new_time = ms.count() % 10000;
    return new_time;
}

void Bomb::setTimePass() {
    std::chrono::high_resolution_clock::time_point _timepoint = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(_timepoint.time_since_epoch());
    std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);
    _time = ms.count() % 10000;
}

void Bomb::place()
{
    _placed = true;
}
