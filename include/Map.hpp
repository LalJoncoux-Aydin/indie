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
#include <iterator>
#include "ICharacter.hpp"

class Map {
    public:
        Map();
        Map(int size);
        Map(int size, std::vector<std::vector<cell_t>> map);
        ~Map();

        void dump();
        void initPlayer(std::vector<std::shared_ptr<ICharacter>> characters);
        std::vector<int> dropBomb(int xPos, int yPos, std::shared_ptr<Bomb> bomb);

        std::vector<std::vector<cell_t>> getMap() noexcept {return _map;}
        std::vector<std::vector<cell_t>> update(std::vector<std::shared_ptr<ICharacter>> character);

        void setMap(std::vector<std::vector<cell_t>> new_map) {
            _map = new_map;
        }

    protected:
    private:
        void clean(PlayerNb p);

        std::vector<std::vector<cell_t>> _map;
        int _size;
        bool _bomb_drop;
        bool _compute;
};

#endif /* !MAPP_HPP_ */
