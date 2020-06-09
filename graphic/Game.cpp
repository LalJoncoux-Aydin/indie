#include "Game.hpp"
#include <string>

Game::Game(IrrlichtDevice *device, sf::Music *sound, std::stack<IScene *> *stack) {

	this->_driver = device->getVideoDriver();

	//this->_device = createDevice(_driver, core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
    this->_soundEngine = sound;
	_device = device;
    this->_sceneManager = _device->getSceneManager();
	this->_guiEnv = _device->getGUIEnvironment();
	this->_scenesStack = stack;
	//_music_loop = NULL;
	MusicGame();
}

scene::ISceneManager* Game::Init_map(scene::ISceneManager* smgr, std::vector<std::vector<cell_t>> _map, int _size, video::IVideoDriver* driver)
{
    int temp = 0;
	int axisX = -18;//hait/bas
	int axisY = -18;//droite gauche
	int axisZ = 1.5;

	int tmp = 0;
	int tmp1 = 0;

	IMeshSceneNode *bombe = _sceneManager->addSphereSceneNode(0.5);
	_bombe = bombe;
	_bombe->setVisible(false);

	IMeshSceneNode *bombe1 = _sceneManager->addSphereSceneNode(0.5);
	_bombe1 = bombe1;
	_bombe1->setVisible(false);

    for (int i = 0 ; i <= _size ; ++i) {
        temp++;
		axisZ += -2;
		axisY += 2;
		axisX = -18;
        for (int x = 0 ; x <= _size ; ++x) {
            temp++;
			axisX += 2;
			tmp1++;
            if (_map[i][x].element == INDESTRUCTIBLE_BOX || _map[i][x].element == DESTRUCTIBLE_BOX || _map[i][x].element == WALL) {
					tmp++;
					scene::ISceneNode* node = 0;

					node = _sceneManager->addLightSceneNode(0, core::vector3df(10,3,-7), video::SColorf(1.0f,1.0f,1.0f,1.0f), 4.0f);

					scene::ISceneNode* temp = _sceneManager->addCubeSceneNode();
                    cubes.push_back(temp);
					if (_map[i][x].element == DESTRUCTIBLE_BOX)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/rockwall.jpg"));
                    else if (_map[i][x].element == INDESTRUCTIBLE_BOX)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/lale.jpg"));
                    else if (_map[i][x].element == WALL)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/momo.jpg"));
                    temp->setMaterialFlag(video::EMF_LIGHTING, true);
                    temp->setPosition(irr::core::vector3df(axisY,axisX,1.5));//(doite/gauche, haut/bas, profondeur)
					temp->setScale(irr::core::vector3df(0.2, 0.2, 0.2));
                    temp->setRotation(irr::core::vector3df(0, 0, 0));

					//temp->setDebugDataVisible(irr::scene::EDS_NORMALS);

			}
			else if (_map[i][x].player == PLAYER1) {
				IAnimatedMeshSceneNode *player1 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1,
				irr::core::vector3df(_x - 10, 0.0f, _y - 0.5), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				_Player1 = player1;
				if (player1) {
					player1->setMaterialFlag(irr::video::EMF_LIGHTING, true);
					player1->setMaterialTexture(0, _driver->getTexture("./assets/model3D/white.jpg"));
					player1->setFrameLoop(208,300);
					player1->setAnimationSpeed(10);
					//player1->setScale(irr::core::vector3df(100, 100, 100));
					player1Animation = false;
				}
			} else if (_map[i][x].player == PLAYER2) {
				IAnimatedMeshSceneNode *player1 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1,
				irr::core::vector3df(_x - 10, 0.0f, _y - 0.5), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				_Player2 = player1;
				if (player1) {
					player1->setMaterialFlag(irr::video::EMF_LIGHTING, true);
					player1->setMaterialTexture(0, _driver->getTexture("./assets/model3D/nskinr.jpg"));
					player1->setFrameLoop(208,300);
					player1->setAnimationSpeed(10);
					//player1->setScale(irr::core::vector3df(100, 100, 100));
					player1Animation = false;
				}
			} else if (_map[i][x].player == PLAYER3) {
				IAnimatedMeshSceneNode *player1 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1,
				irr::core::vector3df(_x - 10, 0.0f, _y - 0.5), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				_Player3 = player1;
				if (player1) {
					player1->setMaterialFlag(irr::video::EMF_LIGHTING, true);
					player1->setMaterialTexture(0, _driver->getTexture("./assets/model3D/noir.jpg"));
					player1->setFrameLoop(208,300);
					player1->setAnimationSpeed(10);
					//player1->setScale(irr::core::vector3df(100, 100, 100));
					player1Animation = false;
				}
			} else if (_map[i][x].player == PLAYER4) {
				IAnimatedMeshSceneNode *player1 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1,
				irr::core::vector3df(_x - 10, 0.0f, _y - 0.5), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				_Player4 = player1;
				if (player1) {
					player1->setMaterialFlag(irr::video::EMF_LIGHTING, true);
					player1->setMaterialTexture(0, _driver->getTexture("./assets/model3D/nskinbl.jpg"));
					player1->setFrameLoop(208,300);
					player1->setAnimationSpeed(10);
					//player1->setScale(irr::core::vector3df(100, 100, 100));
					player1Animation = false;
				}
			}
        }
	}
	return smgr;
}
/*
scene::ISceneManager* Game::delete_cube(scene::ISceneManager* smgr, std::vector<std::vector<cell_t>> _map, int _size, video::IVideoDriver* driver)
{
    int temp = 0;
	int axisX = -18;//hait/bas
	int axisY = -18;//droite gauche
	int axisZ = 1.5;

	for (int i = 0 ; i <= _size ; ++i) {
        temp++;
		axisZ += -2;
		axisY += 2;
		axisX = -18;
        for (int x = 0 ; x <= _size ; ++x) {
            temp++;
			axisX += 2;
			if (_map[i][x].element == DESTROYED_WALL) {
				cubes[temp]->setScale(irr::core::vector3df(0, 0, 0));
                   ;
			}
		}
	}
}*/
void Game::MusicGame()
{
    _music.setMusic("./assets/music/Game.wav");
    _music.musicsetVolume(30);
    _music.musicsetLoop(false);
}
scene::ISceneManager* Game::draw_map(scene::ISceneManager* smgr, std::vector<std::vector<cell_t>> _map, int _size, video::IVideoDriver* driver)
{
    int temp = 0;
	int axisX = -18;//hait/bas
	int axisY = -18;//droite gauche
	int axisZ = 1.5;
	bool drop = false;

	int tmp = 0;
	int tmp1 = 0;

	for (int i = 0 ; i <= _size ; ++i) {
        temp++;
		axisZ += -2;
		axisY += 2;
		axisX = -18;
        for (int x = 0 ; x <= _size ; ++x) {
            temp++;
			axisX += 2;
			tmp1++;
            /*if (_map[i][x].element == INDESTRUCTIBLE_BOX || _map[i][x].element == DESTRUCTIBLE_BOX || _map[i][x].element == WALL) {
					tmp++;
					scene::ISceneNode* temp = smgr->addCubeSceneNode();
                    if (_map[i][x].element == DESTRUCTIBLE_BOX)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/rockwall.jpg"));
                    else if (_map[i][x].element == INDESTRUCTIBLE_BOX)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/lale.jpg"));
                    else if (_map[i][x].element == WALL)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/momo.jpg"));
                    temp->setMaterialFlag(video::EMF_LIGHTING, false);
                    temp->setPosition(irr::core::vector3df(axisY,axisX,1.5));//(doite/gauche, haut/bas, profondeur)
					temp->setScale(irr::core::vector3df(0.2, 0.2, 0.2));
                    temp->setRotation(irr::core::vector3df(0, 0, 0));

					//PLAYER
            } */if (_map[i][x].player == PLAYER1) {
					//player1->remove();
					_Player1->setPosition(irr::core::vector3df(axisY,axisX,1.5));
				} else if (_map[i][x].player == PLAYER2) {
					_Player2->setPosition(irr::core::vector3df(axisY,axisX,1.5));
				} else if (_map[i][x].player == PLAYER3) {
					_Player3->setPosition(irr::core::vector3df(axisY,axisX,1.5));
				} else if (_map[i][x].player == PLAYER4) {
					_Player4->setPosition(irr::core::vector3df(axisY,axisX,1.5));
				}
			/*}else if (_map[i][x].player == PLAYER2) {
				IAnimatedMeshSceneNode *player2 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1,
				irr::core::vector3df(_x - 0.5, 0.0f, _y - 0.5), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				if (player2) {
					player2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
					player2->setMaterialTexture(0, _driver->getTexture("./assets/model3D/nskinrd.jpg"));
					player2->setFrameLoop(208,300);
					player2->setAnimationSpeed(10);
					player2Animation = false;
				}
			}else if (_map[i][x].player == PLAYER3) {
				IAnimatedMeshSceneNode *player3 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1,
				irr::core::vector3df(_x - 5, 0.0f, _y - 0.5), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				if (player3) {
					player3->setMaterialFlag(irr::video::EMF_LIGHTING, false);
					player3->setMaterialTexture(0, _driver->getTexture("./assets/model3D/nskinbl.jpg"));
					player3->setFrameLoop(208,300);
					player3->setAnimationSpeed(10);
					player3Animation = false;
				}
			}else if (_map[i][x].player == PLAYER4) {
				IAnimatedMeshSceneNode *player4 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1,
				irr::core::vector3df(_x + 2.5, 0.0f, _y - 0.5), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				if (player4) {
					player4->setMaterialFlag(irr::video::EMF_LIGHTING, false);
					player4->setMaterialTexture(0, _driver->getTexture("./assets/model3D/noir.jpg"));
					player4->setFrameLoop(208,300);
					player4->setAnimationSpeed(10);
					player4Animation = false;
				}

			}*/
			if (_map[i][x].bombState == EXPLOSION1) {
				std::cout << "bombe" << std::endl;
				_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/rouge.jpg"));
				_bombe->setVisible(false);
				_bombe->setPosition(irr::core::vector3df(axisY,axisX,1.5));
			} if (_map[i][x].bombState == EXPLOSION2) {
				std::cout << "bombe2" << std::endl;
				_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/white.jpg"));
				_bombe->setVisible(true);
				_bombe->setPosition(irr::core::vector3df(axisY,axisX,1.5));
			} 	if (_map[i][x].bombState == EXPLOSION3) {
				std::cout << "bombe3" << std::endl;
				_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/nskinbl.jpg"));
				_bombe->setVisible(true);
				_bombe->setPosition(irr::core::vector3df(axisY,axisX,1.5));
			} 	if (_map[i][x].bombState == EXPLOSION4) {
				drop = false;
				std::cout << "bombe4" << std::endl;
				_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/rouge.jpg"));
				_bombe->setVisible(true);
				_bombe->setPosition(irr::core::vector3df(axisY,axisX,1.5));
			}	if (_map[i][x].bombState == EXPLOSION5) {
				if (drop == false) {
					drop = true;
					std::cout << "bombe5" << std::endl;
					//_map[i][x].bombState = EXPLOSION4;
					_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/noir.jpg"));
					_bombe->setVisible(true);
					_bombe->setPosition(irr::core::vector3df(axisY,axisX,1.5));
				} else {
					std::cout << "bombe5" << std::endl;
					//_map[i][x].bombState = EXPLOSION4;
					_bombe1->setMaterialTexture(0, _driver->getTexture("./assets/model3D/noir.jpg"));
					_bombe1->setVisible(true);
					_bombe1->setPosition(irr::core::vector3df(axisY,axisX,1.5));
				}
			}
        }
   }
   return smgr;
}

/*void Game::initPlayer1(float x, float y)
{
	if (!players[0]->getAlive()) {
		std::cout << "mange" << std::endl;
		_Player1->setVisible(false);
		std::cout << "tes pieds" << std::endl;
		return ;
	}
	if (!isDrawPlayer) {
		std::cout << "stp" << std::endl;
		_Player1 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/models/ninja.b3d"), 0, -1, irr::core::vector3df(x - 0.5, 0.0f, y - 0.5), irr::core::vector3df(0,0,180), irr::core::vector3df(0.2,0.2,0.2));
		std::cout <<"wsh" << std::endl;
		_Player1->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_Player1->setMaterialTexture(0, _driver->getTexture("./assets/models/white.jpg"));
		_Player1->setFrameLoop(208,300);
		_Player1->setAnimationSpeed(15);
		player1Animation = false;
	} else {
		irr::core::vector3df v = _Player1->getPosition();
		irr::core::vector3df r = _Player1->getRotation();
		if (v.X > x - 0.5)
	r.Y = 90;
		if (v.X < x - 0.5)
	r.Y = 270;
		if (v.Z > y - 0.5)
	r.Y = 180;
		if (v.Z < y - 0.5)
			r.Y = 0;
		if (v.X > x - 0.5 || v.X < x - 0.5 || v.Z > y - 0.5 || v.Z < y - 0.5) {
			if (player1Animation == false) {
				_Player1->setFrameLoop(0, 13);
				player1Animation = true;
			}
		} else {
			if (player1Animation == true) {
				_Player1->setFrameLoop(208, 300);
				player1Animation = false;
			}
		}
			v.X = x - 0.5;
			v.Z = y - 0.5;
			_Player1->setPosition(v);
			_Player1->setRotation(r);
	}
}*/

/*void Game::displayPlayer()
{
	//if (!players.empty())
	std::cout << "salut" << std::endl;
		initPlayer1(players[0]->getX() / 10, players[0]->getY() / 10);
	//std::cout << "dzdz" << std::endl;
}*/


void Game::init() {
		// ask user for driver
		//video::E_DRIVER_TYPE driverType=driverChoiceConsole();
		//if (driverType==video::EDT_COUNT)
			//return 1;
		_sceneManager->clear();
		_guiEnv->clear();
		_background = _driver->getTexture("./assets/images/ground.png");
		_empty_color.set(255, 255, 255, 255);

		// create device
		ICameraSceneNode* camera = _sceneManager->addCameraSceneNode(0, vector3df(0,0,-27), vector3df(0,0,0));
		//ICameraSceneNode* camera = _sceneManager->addCameraSceneNode(0, vector3df(0,0,-27), vector3df(0,0,0));

		irr::gui::IGUIEnvironment *gui = _device->getGUIEnvironment();

		irr::gui::IGUIStaticText *texte = _guiEnv->addStaticText(L"SCORE :",
		irr::core::rect<irr::s32>(0,0,150,40), true, true, 0, -1, true);
		irr::gui::IGUIFont *font = _guiEnv->getFont("../../assets/WRESTLEMANIA.ttf");  // chargement de la police

		//texte->setOverrideFont(font);
}

void Game::updateMap(std::vector<std::vector<cell_t>> map)
{
	int size = 16;
	//std::cout << "ta mere" << std::endl;
	draw_map(_sceneManager, map, size, _driver);
}

void Game::render(void) {
	const f32 MOVEMENT_SPEED = 25.f;
	int lastFPS = -1;
	u32 then = _device->getTimer()->getTime();
	const u32 now = _device->getTimer()->getTime();
	then = now;
	const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds


			//bomberman->setPosition(deplacement_joueur(MOVEMENT_SPEED, frameDeltaTime, bomberman, receiver));
	_driver->beginScene(true, true, video::SColor(255,113,113,133));
    _driver->draw2DImage(_background, position2d<s32> (-5, -25), rect<s32> (0,0,1920,1080), 0, _empty_color, true);
	_sceneManager->drawAll(); // draw the 3d scene
	_device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)
	//std::cout << "ta mere" << std::endl;
	//displayPlayer();
//std::cout << "yes" << std::endl;

	_driver->endScene();

	int fps = _driver->getFPS();

	if (lastFPS != fps)
	{
		core::stringw tmp(L"Bomber Man");
		tmp += _driver->getName();
		tmp += L"] fps: ";
		tmp += fps;

		_device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
}

Game::~Game()
{
	_device->drop();
}
