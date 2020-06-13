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
        Bomb() {};
        ~Bomb() {};

        // getters
        bool isPlaced() { return _placed; };
        int getPassedTime() { return _time; };
        unsigned int getExplosionRadius() { return _explosionRadius; };
        Vector<unsigned int> getPos() { return _pos; };

        // Setters
        void setPassedTime(std::size_t time) {
            _time = time;
        };
        void setPlace(bool status) {
            _placed = status;
        };
        void setTimePass();
        void setPos(Vector<unsigned int> pos) {
            _pos = pos;
        };
        void setExplosionRadius(int explo) {
            _explosionRadius = explo;
        };

        // Functions
        std::size_t timePass();
      //  void detonate();
        // bool checkTimerChange();
        // bool shouldExplode();
        void place();

    private:
        unsigned int _explosionRadius = 2;
        Vector<unsigned int> _pos;
        bool _placed = false;
        std::size_t _time = 0;
};

#endif /* !BOMB_HPP_ */
