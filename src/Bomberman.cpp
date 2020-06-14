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
    if (win_game == 1) {
        WinPlayer *_win = new WinPlayer(_device, &_scenesStack);
        _scenesStack.push(_win);
        _scenesStack.top()->init();
        _oldScene = _scenesStack.top();
        _scenesStack.top()->Init_map(_scenesStack.top()->getSceneManager(), indie_map.getMap(), 16, _scenesStack.top()->getDriver());
    } else if (win_game == 2) {
        WinMulti *_win = new WinMulti(_device, &_scenesStack);
        _scenesStack.push(_win);
        _scenesStack.top()->init();
        _oldScene = _scenesStack.top();
        _scenesStack.top()->Init_map(_scenesStack.top()->getSceneManager(), indie_map.getMap(), 16, _scenesStack.top()->getDriver());
    } else if (win_game == 3) {
        Loose *_loose = new Loose(_device, &_scenesStack);
        _scenesStack.push(_loose);
        _scenesStack.top()->init();
        _oldScene = _scenesStack.top();
        _scenesStack.top()->Init_map(_scenesStack.top()->getSceneManager(), indie_map.getMap(), 16, _scenesStack.top()->getDriver());
    }
}

void Bomberman::initGame()
{
    std::shared_ptr<Player> player1 = std::make_shared<Player>(Vector<unsigned int>(15,1), false);
    indie_player.push_back(player1);
    _eventReceiver = new MyEventReceiver1;
    _device->setEventReceiver(_eventReceiver);

    if (multi_player == true) {
        std::shared_ptr<Player> player2 = std::make_shared<Player>(Vector<unsigned int>(1,1), false);
        indie_player.push_back(player2);
    } else {
        std::shared_ptr<IA> player2 = std::make_shared<IA>(Vector<unsigned int>(1,1), true);
        indie_player.push_back(player2);
    }

    std::shared_ptr<IA> player3 = std::make_shared<IA>(Vector<unsigned int>(1,15), true);
    indie_player.push_back(player3);

    std::shared_ptr<IA> player4 = std::make_shared<IA>(Vector<unsigned int>(15,15), true);
    indie_player.push_back(player4);
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

void Bomberman::manageEnd()
{
    _scenesStack.top()->updateMap(indie_map.update(indie_player));
}

void Bomberman::manageGame()
{
    // WIN OR LOOSE ?
    if (indie_player[0]->isDead() == true) {
        run_game = false;
        win_game = 3;
        endGame();
        return;
    }
    if (multi_player == true) {
        if (indie_player[2]->isDead() == true && indie_player[3]->isDead() == true) {
            run_game = false;
            win_game = 2;
            endGame();
            return;
        }
    } else {
        if (indie_player[1]->isDead() == true && indie_player[2]->isDead() == true && indie_player[3]->isDead() == true) {
            run_game = false;
            win_game = 1;
            endGame();
            return;
        }
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

    if (multi_player == true) {
        if (direction_2 == 5) {
            if (indie_player[1]->getBombs()->isPlaced() == false) {
                indie_player[1]->getBombs()->setPlace(true);
                indie_player[1]->getBombs()->setTimePass();
                indie_player[1]->getBombs()->setPos(indie_player[1]->getPos());
            }
        } else if (direction_2 != 0) {
            indie_player[1]->move(orientation(direction_2));
        }
    } else {
        if (indie_player[1]->isDead() == false)
            indie_player[1]->move(indie_map.getMap());
    }
    if (indie_player[2]->isDead() == false)
        indie_player[2]->move(indie_map.getMap());
    if (indie_player[3]->isDead() == false)
        indie_player[3]->move(indie_map.getMap());
    _scenesStack.top()->updateMap(indie_map.update(indie_player));
}

void Bomberman::manageMenu()
{
    int selection = _scenesStack.top()->getButton();

    if (selection == 1) {
        Menu *_menu = new Menu(_device, &_scenesStack);
        _scenesStack.push(_menu);
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
    if (selection == 4 || selection == 5 || selection == 6) {
        Game *_game = new Game(_device, _soundEngine, &_scenesStack);
        _scenesStack.push(_game);
        _scenesStack.top()->init();
        _oldScene = _scenesStack.top();
        run_menu = false;
        run_game = true;
        if (selection == 4)
            multi_player = false;
        if (selection == 5)
            multi_player = true;
        initGame();
        indie_map.initPlayer(indie_player);
        if (selection == 6) {
            readJson("save.json");
        }
        _scenesStack.top()->Init_map(_scenesStack.top()->getSceneManager(), indie_map.getMap(), 16, _scenesStack.top()->getDriver());
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
            if (run_game == false)
                manageEnd();
        }
	    _scenesStack.top()->render();
	}
}

void Bomberman::clear()
{
	//_device->drop();
	//this->soundEngine->drop();

	int size = _scenesStack.size();

	while (!_scenesStack.empty()) {
		delete _scenesStack.top();
		_scenesStack.pop();
	}
}

void Bomberman::readJson(std::string file_name)
{
    pt::ptree iroot;
    std::ifstream ifile;
    ifile.open("save.json");
    if (!ifile)
        return;

    pt::read_json(file_name, iroot);
    indie_save.getPlayer(&iroot, "player1", indie_player[0]);
    indie_save.getPlayer(&iroot, "player2", indie_player[1]);
    indie_save.getPlayer(&iroot, "player3", indie_player[2]);
    indie_save.getPlayer(&iroot, "player2", indie_player[3]);

    std::vector<std::vector<cell_t>> new_map = indie_save.getMatrix(&iroot);
    indie_map.setMap(new_map);
}

void Bomberman::dumpJson(std::string file_name)
{
    pt::ptree oroot;
    indie_save.dumpNbPlayer(&oroot, multi_player);
    indie_save.dumpPlayer(&oroot, indie_save.characterPrep(indie_player[0]), "player1");
    indie_save.dumpPlayer(&oroot, indie_save.characterPrep(indie_player[1]), "player2");
    indie_save.dumpPlayer(&oroot, indie_save.characterPrep(indie_player[2]), "player3");
    indie_save.dumpPlayer(&oroot, indie_save.characterPrep(indie_player[3]), "player4");

    indie_save.dumpMatrix(&oroot, indie_map.getMap());
    std::ofstream my_output_file(file_name);
    pt::write_json(my_output_file, oroot);
}

Bomberman::~Bomberman()
{
    dumpJson("save.json");
  //  readJson("save.json");
}
