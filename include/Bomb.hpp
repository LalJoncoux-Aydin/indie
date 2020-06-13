/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <Vector.hpp>
#include <chrono>

class Bomb {
    public:
        Bomb(unsigned int _bombRadius) {
            _explosionRadius = _bombRadius;
        };
        ~Bomb() {};

        // getters
        unsigned int getExplosionRadius() { return _explosionRadius; };
        Vector<unsigned int> getPos() { return _pos; };
        bool isPlaced() { return _placed; };
        int getPassedTime() { return _time; };

        // Setters
        void setExplosionRadius(int explo) {
            _explosionRadius = explo;
        };
        void setPos(Vector<unsigned int> pos) {
            _pos = pos;
        };
        void setPlace(bool status) {
            _placed = status;
        };
        void setPassedTime(std::size_t time) {
            _time = time;
        };

        // Functions
        std::size_t timePass();
        void setTimePass();
        void place();

    private:
        unsigned int _explosionRadius;
        Vector<unsigned int> _pos;
        bool _placed = false;
        std::size_t _time = 0;
};

#endif /* !BOMB_HPP_ */
