#include "Bomberman.hpp"
#include <unistd.h>



Bomberman::Bomberman()
{
  //sf::Music music;


  _device = createDevice(video::EDT_OPENGL, dimension2d<u32>(1920, 1080), 16, false, false, true, 0);
	_device->setResizable(true);
	/*if (!(soundEngine = createIrrKlangDevice())) {
		throw std::string("Failed to create a sound engine");
		return (false);
	}*/
  _device->setWindowCaption(L"INDIE STUDIO");



  Intro *introd = new Intro(_device, &_scenesStack);
  //Menu::MusicMenu();
  _scenesStack.push(introd);
  //sleep(10);
 /* Menu *mainMenu = new Menu(_device, &_scenesStack);
  _scenesStack.push(mainMenu);*/


}

void Bomberman::initGame()
{
  Player *player1 = new Player(Vector<unsigned int>(1,1), false);
  indie_player.push_back(player1);
  _eventReceiver = new MyEventReceiver1;
  _device->setEventReceiver(_eventReceiver);

  //if (multi_player == true) {
    Player *player2 = new Player(Vector<unsigned int>(1,15), false);
    indie_player.push_back(player2);
 /*else {
    IA *player2 = new IA(Vector<unsigned int>(1,15), false);
    indie_player.push_back(player2);
  }*/

  IA *player3 = new IA(Vector<unsigned int>(15,1), false);
  indie_player.push_back(player3);

  IA *player4 = new IA(Vector<unsigned int>(15,15), false);
  indie_player.push_back(player4);


  int size = 16;
	_scenesStack.top()->Init_map(_scenesStack.top()->getSceneManager(), indie_map.update(indie_player), size, _scenesStack.top()->getDriver());
  run_game = true;
}

int Bomberman::getKeyPlayer1()
{
	if(_eventReceiver->IsKeyDown(irr::KEY_KEY_Q)) {
		return 3;
  }
	else if(_eventReceiver->IsKeyDown(irr::KEY_KEY_D))
		return 1;
	else if(_eventReceiver->IsKeyDown(irr::KEY_KEY_S))
        return 2;
	else if(_eventReceiver->IsKeyDown(irr::KEY_KEY_Z))
		return 4;
  else if(_eventReceiver->IsKeyDown(irr::KEY_SPACE))
  	return 5;
  else if(_eventReceiver->IsKeyDown(irr::KEY_ESCAPE))
		return 6;
  return 0;
}

int  Bomberman::getKeyPlayer2()
{
  if(_eventReceiver->IsKeyDown(irr::KEY_UP))
    return 4;
  else if(_eventReceiver->IsKeyDown(irr::KEY_DOWN))
    return 2;
  else if(_eventReceiver->IsKeyDown(irr::KEY_LEFT))
    return 3;
  else if(_eventReceiver->IsKeyDown(irr::KEY_RIGHT))
    return 1;
  else if(_eventReceiver->IsKeyDown(irr::KEY_RETURN))
    return 5;
  else if(_eventReceiver->IsKeyDown(irr::KEY_DELETE))
    return 6;
  return 0;
}

void Bomberman::manageGame()
{
  // WIN OR LOOSE ?
  // indie_map->isEndGame();
  // CHANGE SCENE

  // GET KEYS
  int direction_1 = getKeyPlayer1();
  int direction_2 = getKeyPlayer2();

  if (direction_1 == 5) {
    indie_player[0]->dropBomb();
    std::cout << "bombberman" << std::endl;
 } else if (direction_1 != 0) {
      indie_player[0]->move(orientation(direction_1));
  }

  if (direction_2 == 5) {
    indie_player[1]->dropBomb();
  } else if (direction_2 != 0)
    indie_player[1]->move(orientation(direction_2));

  // DISPLAY LA MAP
  _scenesStack.top()->updateMap(indie_map.update(indie_player));
}

void Bomberman::manageMenu()
{
  //     sf::Music music;
  // if (!music.openFromFile("./assets/music/music.wav")) {
  //           std::cout <<"Error Music" << std::endl;
  //       }
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
      /* if (selection == 3)
          multi_player == false;
        if (selection == 4)
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
            if (run_game == false)
               initGame();
            manageGame();
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
