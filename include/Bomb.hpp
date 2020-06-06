/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <Vector.hpp>

class Bomb {
    public:
        Bomb(unsigned int size, Vector<unsigned int> pos);
        Bomb(unsigned int time);
        ~Bomb();

        // getters
        unsigned int getTimeBeforeExplosion() { return 15 - (_lastCheck - _timePlaced); };
        bool isPlaced() { return _placed; };

        // setters
        unsigned int getExplosionRadius() { return _explosionRadius; };
        Vector<unsigned int> getPos() { return _pos; };

        void detonate();

        bool checkTimerChange();
        bool shouldExplode();

        void place();

    private:
        unsigned int _explosionRadius;
        Vector<unsigned int> _pos;
        unsigned int _timePlaced;
        unsigned int _lastCheck = 0;
        bool _placed = false;
};

#endif /* !BOMB_HPP_ */