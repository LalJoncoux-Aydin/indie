/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** cell
*/

#ifndef CELL_HPP_
#define CELL_HPP_

enum orientation {
    NO_ORIENT = 0,
    SOUTH = 1,
    WEST = 2,
    NORTH = 3,
    EAST = 4
};

enum PowerUp {
    NO_POWERUP = 0,
    BOMB_RADIUS = 1,
    BOMB_NUMBER = 2,
    SPEED = 3
};

enum PlayerNb {
    NO_PLAYER = 0,
    PLAYER1 = 1,
    PLAYER2 = 2,
    PLAYER3 = 3,
    PLAYER4 = 4
};

enum mapBomb {
    NO = 0,
    EXPLOSION1 = 1,
    EXPLOSION2 = 2,
    EXPLOSION3 = 3,
    EXPLOSION4 = 4,
    EXPLOSION5 = 5,
    HAS_EXPLODED = 6,
};

enum decor {
    EMPTY = 0,
    WALL = 1,
    INDESTRUCTIBLE_BOX = 2,
    DESTRUCTIBLE_BOX = 3,
    BROKEN_BOX = 4,
    BURNING = 5,
    BOMB_PLACE = 6,
};

typedef struct cell_s {
    orientation orient;
    PlayerNb player;
    mapBomb bombState;
    decor element;
    bool isBoom;
    bool isDeadBody;
    PowerUp powerup;
} cell_t;

#endif /* !CELL_HPP_ */
