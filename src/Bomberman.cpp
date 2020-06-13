#include "Bomberman.hpp"
#include <unistd.h>

Bomberman::Bomberman()
{
    _device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1920, 1080), 16, false, false, true, 0);
    _device->setResizable(true);
    _device->setWindowCaption(L"INDIE STUDIO");

    Intro *introd = new Intro(_device, &_scenesStack);
    _scenesStack.push(introd);
}

void Bomberman::endGame()
{
    std::cout << "END GAME !" << std::endl;
    Win *_win = new Win(_device, &_scenesStack);
    _scenesStack.push(_win);
    _scenesStack.top()->init();
    _oldScene = _scenesStack.top();
}

void Bomberman::initGame()
{
    Player *player1 = new Player(Vector<unsigned int>(15,1), false);
    indie_player.push_back(player1);
    _eventReceiver = new MyEventReceiver1;
    _device->setEventReceiver(_eventReceiver);

    //if (multi_player == true) {
    Player *player2 = new Player(Vector<unsigned int>(1,1), false);
    indie_player.push_back(player2);
 /*else {
    IA *player2 = new IA(Vector<unsigned int>(1,1), false);
    indie_player.push_back(player2);
  }*/

    IA *player3 = new IA(Vector<unsigned int>(1,15), false);
    indie_player.push_back(player3);

    IA *player4 = new IA(Vector<unsigned int>(15,15), false);
    indie_player.push_back(player4);

    indie_map.initPlayer(indie_player);
    _scenesStack.top()->Init_map(_scenesStack.top()->getSceneManager(), indie_map.getMap(), 16, _scenesStack.top()->getDriver());
}

int Bomberman::getKeyPlayer2()
{
	if(_eventReceiver->IsKeyDown(irr::KEY_KEY_Q))
		return 2;
	else if(_eventReceiver->IsKeyDown(irr::KEY_KEY_D))
		return 4;
	else if(_eventReceiver->IsKeyDown(irr::KEY_KEY_S))
        return 1;
	else if(_eventReceiver->IsKeyDown(irr::KEY_KEY_Z))
		return 3;
    else if(_eventReceiver->IsKeyDown(irr::KEY_SPACE))
        return 5;
    else if(_eventReceiver->IsKeyDown(irr::KEY_ESCAPE))
		return 6;
  return 0;
}

int  Bomberman::getKeyPlayer1()
{
    if(_eventReceiver->IsKeyDown(irr::KEY_UP))
        return 3;
    else if(_eventReceiver->IsKeyDown(irr::KEY_DOWN))
        return 1;
    else if(_eventReceiver->IsKeyDown(irr::KEY_LEFT))
        return 2;
    else if(_eventReceiver->IsKeyDown(irr::KEY_RIGHT))
        return 4;
    else if(_eventReceiver->IsKeyDown(irr::KEY_RETURN))
        return 5;
    else if(_eventReceiver->IsKeyDown(irr::KEY_DELETE))
        return 6;
  return 0;
}

void Bomberman::manageGame()
{
    // WIN OR LOOSE ?
    if (indie_player[0]->isDead() == true) {
        run_game = false;
        return;
    }

    // GET KEYS
    direction_1 = getKeyPlayer1();
    direction_2 = getKeyPlayer2();

    if (direction_1 == 5) {
        if (indie_player[0]->getBombs()->isPlaced() == false) {
            indie_player[0]->getBombs()->setPlace(true);
            indie_player[0]->getBombs()->setTimePass();
            indie_player[0]->getBombs()->setPos(indie_player[0]->getPos());
        }
    } else if (direction_1 != 0) {
        indie_player[0]->move(orientation(direction_1));
    }

    if (direction_2 == 5) {
        if (indie_player[1]->getBombs()->isPlaced() == false) {
            indie_player[1]->getBombs()->setPlace(true);
            indie_player[1]->getBombs()->setTimePass();
            indie_player[1]->getBombs()->setPos(indie_player[1]->getPos());
        }
    } else if (direction_2 != 0) {
        indie_player[1]->move(orientation(direction_2));
    }
    _scenesStack.top()->updateMap(indie_map.update(indie_player));
}

void Bomberman::manageMenu()
{
    int selection = _scenesStack.top()->getButton();

    if (selection == 1) {
        Menu *mainMenu = new Menu(_device, &_scenesStack);
        _scenesStack.push(mainMenu);
        _scenesStack.top()->init();
		_oldScene = _scenesStack.top();
    }
    if (selection == 2) {
        Settings *indie_setting = new Settings(_device, _soundEngine, &_scenesStack);
        _scenesStack.push(indie_setting);
        _scenesStack.top()->init();
		_oldScene = _scenesStack.top();
    }
    if (selection == 3) {
        Help *options = new Help(_device, _soundEngine, &_scenesStack);
        _scenesStack.push(options);
        _scenesStack.top()->init();
        _oldScene = _scenesStack.top();
    }
    if (selection == 4 || selection == 5) {
        Game *_game = new Game(_device, _soundEngine, &_scenesStack);
        _scenesStack.push(_game);
        _scenesStack.top()->init();
        _oldScene = _scenesStack.top();
        run_menu = false;
        run_game = true;
        initGame();
      /* if (selection == 4)
          multi_player == false;
        if (selection == 5)
          multi_player == true;*/
    }
}

void Bomberman::scenesHandler()
{
	while (_device->run() && _scenesStack.top()->getDriver()) {

		if (_oldScene != _scenesStack.top()) {
		  _scenesStack.top()->init();
		  _oldScene = _scenesStack.top();
		}

        if (run_menu == true) {
            manageMenu();
        } else {
            if (run_game == true)
                manageGame();
            if (run_game == false) {
                endGame();
            }
        }
	    _scenesStack.top()->render();
	}
}

void Bomberman::clear()
{
	_device->drop();
	//this->soundEngine->drop();

	int size = _scenesStack.size();

	while (!_scenesStack.empty()) {
		delete _scenesStack.top();
		_scenesStack.pop();
	}
}

Bomberman::~Bomberman()
{

}
