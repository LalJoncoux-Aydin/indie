#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

// Standard libs
#include <iostream>
#include <cstring>
#include <list>
#include <errno.h>
#include <string.h>
// Local libs
#include "Map.hpp"

#include "IScene.hpp"
#include "Menu.hpp"
#include "Settings.hpp"
#include "Help.hpp"
#include "EventReceiver.hpp"
#include "Game.hpp"
#include "cell.hpp"
#include "Intro.hpp"

#include "ICharacter.hpp"
#include "Bomb.hpp"
// Define


// Functions
class Bomberman {
  public:
    Bomberman();

	  void 				initGame();
	  void 				scenesHandler();
	  void 				clear();

    void manageMenu();
    void manageGame();
    int getKeyPlayer1();
    int getKeyPlayer2();
    ~Bomberman();
  private:
    Map indie_map = Map(16);

    std::vector<ICharacter *> indie_player;
    std::stack<IScene *> _scenesStack;

    bool multi_player = false;
    bool saved_game = false;
    bool run_game = false;
    bool run_menu = true;

	  IScene				*_oldScene = NULL;
	  IrrlichtDevice		*_device;
	  sf::Music		*_soundEngine;
    MyEventReceiver1 *_eventReceiver;

    int direction;
    int direction_1 = 0;
    int direction_2 = 0;
    bool direction_1_posed = false;
};

#endif /* !BOMBERMAN_HPP_ */
