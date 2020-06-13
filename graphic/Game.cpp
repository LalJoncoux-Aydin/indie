#include "Game.hpp"
#include <string>

Game::Game(IrrlichtDevice *device, sf::Music *sound, std::stack<IScene *> *stack)
{
	this->_driver = device->getVideoDriver();
    this->_soundEngine = sound;
	_device = device;
    this->_sceneManager = _device->getSceneManager();
	this->_guiEnv = _device->getGUIEnvironment();
	this->_scenesStack = stack;
	MusicGame();
}

void Game::init() {
		_sceneManager->clear();
		_guiEnv->clear();
		_background = _driver->getTexture("./assets/images/ground.png");
		_empty_color.set(255, 255, 255, 255);

		// create device
		ICameraSceneNode* camera = _sceneManager->addCameraSceneNode(0, vector3df(0,0,-27), vector3df(0,0,0));
		irr::gui::IGUIEnvironment *gui = _device->getGUIEnvironment();
		irr::gui::IGUIStaticText *texte = _guiEnv->addStaticText(L"SCORE :",
		irr::core::rect<irr::s32>(0,0,150,40), true, true, 0, -1, true);
		irr::gui::IGUIFont *font = _guiEnv->getFont("../../assets/WRESTLEMANIA.ttf");  // chargement de la police
}

scene::ISceneManager* Game::Init_map(scene::ISceneManager* smgr, std::vector<std::vector<cell_t>> _map, int _size, video::IVideoDriver* driver)
{
	IMeshSceneNode *bombe = _sceneManager->addSphereSceneNode(0.8);
	_bombe = bombe;
	_bombe->setVisible(false);

	IMeshSceneNode *bombe1 = _sceneManager->addSphereSceneNode(0.8);
	_bombe1 = bombe1;
	_bombe1->setVisible(false);

    for (int y = 0; y <= _size; ++y) {
        int temp_y = 14 - (y - 1) * 2;
        for (int x = 0; x <= _size; ++x) {
            int temp_x = -14 + (x - 1) * 2;

            // Walls
            if (_map[y][x].element == INDESTRUCTIBLE_BOX || _map[y][x].element == DESTRUCTIBLE_BOX || _map[y][x].element == WALL) {
					scene::ISceneNode* node = 0;

					node = _sceneManager->addLightSceneNode(0, core::vector3df(10,3,-7), video::SColorf(1.0f,1.0f,1.0f,1.0f), 4.0f);

					scene::ISceneNode* temp = _sceneManager->addCubeSceneNode();

                    cubes.push_back(temp);
					if (_map[y][x].element == DESTRUCTIBLE_BOX)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/rockwall.jpg"));
                    else if (_map[y][x].element == INDESTRUCTIBLE_BOX)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/lale.jpg"));
                    else if (_map[y][x].element == WALL)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/momo.jpg"));
                    temp->setMaterialFlag(video::EMF_LIGHTING, true);
                    temp->setPosition(irr::core::vector3df((x * 2) - 16,-((y * 2) - 16),1.5));//(doite/gauche, haut/bas, profondeur)
					temp->setScale(irr::core::vector3df(0.2, 0.2, 0.2));
                    temp->setRotation(irr::core::vector3df(0, 0, 0));
			}
            // PLAYER
			else if (_map[y][x].player == PLAYER1) {
				_Player1 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1, irr::core::vector3df(temp_x, temp_y, 2), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				if (_Player1) {
					_Player1->setMaterialFlag(irr::video::EMF_LIGHTING, true);
					_Player1->setMaterialTexture(0, _driver->getTexture("./assets/model3D/white.jpg"));
					_Player1->setFrameLoop(208,300);
					_Player1->setAnimationSpeed(10);
					player1Animation = false;
				}
			}
            else if (_map[y][x].player == PLAYER2) {
				_Player2 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1, irr::core::vector3df(temp_x, temp_y, 2), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				if (_Player2) {
					_Player2->setMaterialFlag(irr::video::EMF_LIGHTING, true);
					_Player2->setMaterialTexture(0, _driver->getTexture("./assets/model3D/rouge.jpg"));
					_Player2->setFrameLoop(208,300);
					_Player2->setAnimationSpeed(10);
					player2Animation = false;
				}
            }
            else if (_map[y][x].player == PLAYER3) {
				_Player3 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1, irr::core::vector3df(temp_x, temp_y, 2), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				if (_Player3) {
					_Player3->setMaterialFlag(irr::video::EMF_LIGHTING, true);
					_Player3->setMaterialTexture(0, _driver->getTexture("./assets/model3D/noir.jpg"));
					_Player3->setFrameLoop(208,300);
					_Player3->setAnimationSpeed(10);
					player3Animation = false;
				}
            }
            else if (_map[y][x].player == PLAYER4) {
				_Player4 = _sceneManager->addAnimatedMeshSceneNode(_sceneManager->getMesh("./assets/model3D/ninja.b3d"), 0, -1, irr::core::vector3df(temp_x, temp_y, 2), irr::core::vector3df(480,180,180), irr::core::vector3df(0.5,0.5,0.5));
				if (_Player4) {
					_Player4->setMaterialFlag(irr::video::EMF_LIGHTING, true);
					_Player4->setMaterialTexture(0, _driver->getTexture("./assets/model3D/nskinr.jpg"));
					_Player4->setFrameLoop(208,300);
					_Player4->setAnimationSpeed(10);
					player4Animation = false;
				}
            }
        }
	}
	return smgr;
}

void Game::MusicGame()
{
    _music.setMusic("./assets/music/Game.wav");
    _music.musicsetVolume(30);
    _music.musicsetLoop(false);
}

void Game::updateMap(std::vector<std::vector<cell_t>> _map)
{
    for (int y = 0; y <= 16; ++y) {
        int temp_y = 14 - (y - 1) * 2;
        for (int x = 0; x <= 16; ++x) {
            int temp_x = -14 + (x - 1) * 2;

            // Walls
            if (_map[y][x].element == BROKEN_BOX) {
                for (int i = 0; cubes[i]; i++) {
                    irr::core::vector3df test = cubes[i]->getPosition();
                    if (test == irr::core::vector3df(temp_x,temp_y,1.5)) {
                        cubes[i]->setVisible(false);
                    }
                }
            }
            // CAMILLE CODE ICI
           // if (_map[y][x].element == BURNING) {
           //
           // }

           // Dead or life
            if (_map[y][x].isDeadBody == true) {
                if (_map[y][x].player == PLAYER1) {
    				_Player1->setVisible(false);
    			} else if (_map[y][x].player == PLAYER2) {
    				_Player2->setVisible(false);
    			} else if (_map[y][x].player == PLAYER3) {
    				_Player3->setVisible(false);
    			} else if (_map[y][x].player == PLAYER4) {
    				_Player4->setVisible(false);
    			}
            }
            // PLAYER
            if (_map[y][x].player == PLAYER1) {
				_Player1->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
			} else if (_map[y][x].player == PLAYER2) {
				_Player2->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
			} else if (_map[y][x].player == PLAYER3) {
				_Player3->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
			} else if (_map[y][x].player == PLAYER4) {
				_Player4->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
			}

            // Bombes
			if (_map[y][x].bombState == EXPLOSION1) {
				_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/rouge.jpg"));
				_bombe->setVisible(false);
				_bombe->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
			} if (_map[y][x].bombState == EXPLOSION2) {
				_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/white.jpg"));
				_bombe->setVisible(true);
				_bombe->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
			} 	if (_map[y][x].bombState == EXPLOSION3) {
				_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/nskinbl.jpg"));
				_bombe->setVisible(true);
				_bombe->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
			} 	if (_map[y][x].bombState == EXPLOSION4) {
				_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/rouge.jpg"));
				_bombe->setVisible(true);
				_bombe->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
			}	if (_map[y][x].bombState == EXPLOSION5) {
				_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/noir.jpg"));
				_bombe->setVisible(true);
				_bombe->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
			}
        //    std::cout << "isDeadBody = " << _map[y][x].isDeadBody << std::endl;
        }
	}
}

void Game::render(void) {
	const f32 MOVEMENT_SPEED = 25.f;
	int lastFPS = -1;
	u32 then = _device->getTimer()->getTime();
	const u32 now = _device->getTimer()->getTime();
	then = now;
	const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds

	_driver->beginScene(true, true, video::SColor(255,113,113,133));
    _driver->draw2DImage(_background, position2d<s32> (-5, -25), rect<s32> (0,0,1920,1080), 0, _empty_color, true);
	_sceneManager->drawAll(); // draw the 3d scene
	_device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)
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