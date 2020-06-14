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
#include "Win.hpp"
#include "WinMulti.hpp"
#include "Loose.hpp"

#include "ICharacter.hpp"
#include "Bomb.hpp"
#include "SaveLoad.hpp"
// Define


// Functions
class Bomberman {
  public:
    Bomberman();

	void scenesHandler();
	void clear();
    void endGame();
    void manageEnd();
    void manageMenu();
    void initGame();
    void manageGame();

    int getKeyPlayer1();
    int getKeyPlayer2();

    void readJson(std::string file_name);
    void dumpJson(std::string file_name);

    ~Bomberman();
  private:
    Map indie_map = Map(16);
    SaveLoad indie_save = SaveLoad();

    std::vector<std::shared_ptr<ICharacter>> indie_player;
    std::stack<IScene *> _scenesStack;

    bool multi_player = false;
    bool saved_game = false;
    bool run_game = false;
    bool run_menu = true;
    int win_game = 0; // 1 : player 1 win // 2 : player 2 win // 3 : loose

	IScene				*_oldScene = NULL;
	IrrlichtDevice		*_device;
	sf::Music		*_soundEngine;
    MyEventReceiver1 *_eventReceiver;

    int direction_1 = 0;
    int direction_2 = 0;
};

#endif /* !BOMBERMAN_HPP_ */
