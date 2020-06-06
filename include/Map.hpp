/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Mapp
*/

#ifndef MAPP_HPP_
#define MAPP_HPP_

#include <vector>
#include <iostream>
#include "ICharacter.hpp"
// #include "Character.hpp"

// class Character;

class Map {
    public:
        Map();
        Map(int size);
        Map(int size, std::vector<std::vector<cell_t>> map);
        ~Map();

        void dump();

        int dropBomb(int x, int y, int boost, std::vector<ICharacter *> characters);

        std::vector<std::vector<cell_t>> getMap() noexcept {return _map;}
        std::vector<std::vector<cell_t>> update(std::vector<ICharacter *> character);

    protected:
    private:
        void clean(PlayerNb p);

        std::vector<std::vector<cell_t>> _map;
        int _size;
        bool _bomb_drop;
        bool _compute;
};

#endif /* !MAPP_HPP_ */
