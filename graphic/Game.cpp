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
	//MusicGame();
}

void Game::initMenuButton()
{
    IGUIButton *Menu = _guiEnv->addButton(rect<s32>(187,937,400,1000), 0, GUI_ID_INTRO, L"", L"Go in game");
    video::ITexture *textuPlay = _driver->getTexture("./assets/images/button_menu2.png");
  	Menu->setUseAlphaChannel(true);
  	Menu->setDrawBorder(false);
	Menu->setImage(textuPlay);
}

void Game::initRestartButton()
{
    IGUIButton *Restart = _guiEnv->addButton(rect<s32>(1587,937,1800,1000), 0, GUI_ID_START_BUTTON, L"", L"Go in game");
    video::ITexture *textuPlay = _driver->getTexture("./assets/images/button_save-game.png");
  	Restart->setUseAlphaChannel(true);
  	Restart->setDrawBorder(false);
	Restart->setImage(textuPlay);
}

void Game::init() {
		_sceneManager->clear();
		_guiEnv->clear();
		_background = _driver->getTexture("./assets/images/ground.png");
		_empty_color.set(255, 255, 255, 255);


	//initMenuButton();
	//	initRestartButton();
		// create device
		ICameraSceneNode* camera = _sceneManager->addCameraSceneNode(0, vector3df(0,0,-27), vector3df(0,0,0));
		irr::gui::IGUIEnvironment *gui = _device->getGUIEnvironment();
		irr::gui::IGUIStaticText *texte = _guiEnv->addStaticText(L"SCORE :",
		irr::core::rect<irr::s32>(0,0,150,40), true, true, 0, -1, true);
		irr::gui::IGUIFont *font = _guiEnv->getFont("../../assets/WRESTLEMANIA.ttf");  // chargement de la police

	context = new SAppContext;
    if (context) {
        context->device = this->getDevice();
        context->counter = 0;
    }
    else
        throw std::string(strerror(ENOMEM));

    _eventReceiver = new MyEventReceiver(*context, _device, _soundEngine, _scenesStack, _music_loop);
    if (_eventReceiver)
        _device->setEventReceiver(_eventReceiver);
    else
        throw std::string(strerror(ENOMEM));

}

scene::ISceneManager* Game::Init_map(scene::ISceneManager* smgr, std::vector<std::vector<cell_t>> _map, int _size, video::IVideoDriver* driver)
{
    for (int y = 0; y <= _size; ++y) {
        int temp_y = 14 - (y - 1) * 2;
        for (int x = 0; x <= _size; ++x) {
            int temp_x = -14 + (x - 1) * 2;


            // Walls
            if (_map[y][x].element == INDESTRUCTIBLE_BOX || _map[y][x].element == DESTRUCTIBLE_BOX || _map[y][x].element == WALL ||
				_map[y][x].powerup == BOMB_RADIUS || _map[y][x].powerup == SPEED) {

					scene::ISceneNode* node = 0;

					node = _sceneManager->addLightSceneNode(0, core::vector3df(10,3,-7), video::SColorf(1.0f,1.0f,1.0f,1.0f), 4.0f);
					scene::ISceneNode* temp = _sceneManager->addCubeSceneNode();


                    cubes.push_back(temp);
					if (_map[y][x].element == DESTRUCTIBLE_BOX)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/rockwall.jpg"));
                    else if (_map[y][x].element == INDESTRUCTIBLE_BOX)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/lale.jpg"));
					else if (_map[y][x].powerup == BOMB_RADIUS)
						temp->setMaterialTexture(0, _driver->getTexture("./assets/images/Black.jpg"));
					else if (_map[y][x].powerup == SPEED)
						temp->setMaterialTexture(0, _driver->getTexture("./assets/images/Speed.jpg"));
                    else if (_map[y][x].element == WALL)
                        temp->setMaterialTexture(0, driver->getTexture("./assets/images/momo.jpg"));
                    temp->setMaterialFlag(video::EMF_LIGHTING, true);
                    temp->setPosition(irr::core::vector3df((x * 2) - 16,-((y * 2) - 16),1.5));//(doite/gauche, haut/bas, profondeur)
					temp->setScale(irr::core::vector3df(0.2, 0.2, 0.2));
                    temp->setRotation(irr::core::vector3df(0, 0, 0));

			}

			/*if (_map[y][x].powerup == BOMB_RADIUS) {
                temp->setMaterialTexture(0, _driver->getTexture("./assets/images/Black.jpg"));
            }
			if (_map[y][x].powerup == SPEED) {
                temp->setMaterialTexture(0, _driver->getTexture("./assets/images/Speed.jpg"));
			} else if ((_map[y][x].powerup == BOMB_RADIUS || _map[y][x].powerup == SPEED) && _map[y][x].player != NO_PLAYER) {
				temp2->setVisible(false);
			}
                temp2->setMaterialFlag(video::EMF_LIGHTING, true);
                temp2->setPosition(irr::core::vector3df(temp_x, temp_y, 1.5));//(doite/gauche, haut/bas, profondeur)
				temp2->setScale(irr::core::vector3df(0.2, 0.2, 0.2));
            	temp2->setRotation(irr::core::vector3df(0, 0, 0));*/

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
					_Player2->setMaterialTexture(0, _driver->getTexture("./assets/model3D/nskinr.jpg"));
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

void Game::MusicTimer()
{
    _music.setMusic("./assets/music/Exposed.wav");
    _music.musicsetVolume(30);
    _music.musicsetLoop(false);
}

void Game::MusicExplosion()
{
    _music.setMusic("./assets/music/Explosion.wav");
    _music.musicsetVolume(30);
    _music.musicsetLoop(false);
}

void Game::MusicDeath()
{
    _music.setMusic("./assets/music/Death.wav");
    _music.musicsetVolume(80);
    _music.musicsetLoop(false);
}


void Game::updateMap(std::vector<std::vector<cell_t>> _map)
{
    int size = 16;
    for (int y = 0; (y + 1) <= size; ++y) {
        int temp_y = 14 - (y - 1) * 2;
        for (int x = 0; (x + 1) <= size; ++x) {
            int temp_x = -14 + (x - 1) * 2;

            // Walls
            if (_map[y][x].element == BROKEN_BOX) {
                if (!cubes.empty()) {
                    for (int i = 0; i < cubes.size(); i++) {
                        irr::core::vector3df test = cubes[i]->getPosition();
                        if (test == irr::core::vector3df(temp_x,temp_y,1.5)) {
                            cubes[i]->setVisible(false);
                        }
                    }
                }
            }

           // Dead or life
            if (_map[y][x].isDeadBody == true) {
                if (_map[y][x].player == PLAYER1) {
					MusicDeath();
    				_Player1->setVisible(false);
    			} else if (_map[y][x].player == PLAYER2) {
					MusicDeath();
    				_Player2->setVisible(false);
    			} else if (_map[y][x].player == PLAYER3) {
					MusicDeath();
    				_Player3->setVisible(false);
    			} else if (_map[y][x].player == PLAYER4) {
					MusicDeath();
    				_Player4->setVisible(false);
    			}
            } else {
               // std::cout << "is not dead body" << std::endl;
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
            }

            if (_map[y][x].element == BOMB_PLACE && _map[y][x].bombState != NO) {
        		MusicTimer();
                IMeshSceneNode *_bombe = _sceneManager->addSphereSceneNode(0.8);
                _bombe->setVisible(false);
            	_bombe->setMaterialTexture(0, _driver->getTexture("./assets/model3D/rouge.jpg"));
                _bombe->setVisible(true);
                _bombe->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
                list_bomb.push_back(_bombe);
            } else if (_map[y][x].element != BOMB_PLACE && _map[y][x].bombState != NO) {
                for(int it = 0; it < list_bomb.size(); it++) {
                    irr::core::vector3df temp_bomb_pos = list_bomb[it]->getPosition();
                    if (temp_bomb_pos == irr::core::vector3df(temp_x,temp_y,1.5)) {
                        if (_map[y][x].bombState == HAS_EXPLODED) {
                            list_bomb.erase(list_bomb.begin());
                            continue;
                        }
                   	    if (_map[y][x].bombState == EXPLOSION1) {
        					//MusicExplosion();
                    	    list_bomb[it]->setMaterialTexture(0, _driver->getTexture("./assets/model3D/rouge.jpg"));
                        	list_bomb[it]->setVisible(false);
                        	list_bomb[it]->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
                        } if (_map[y][x].bombState == EXPLOSION2) {
                        	list_bomb[it]->setMaterialTexture(0, _driver->getTexture("./assets/model3D/Explosion.jpg"));
                        	list_bomb[it]->setVisible(true);
                        	list_bomb[it]->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
                        } 	if (_map[y][x].bombState == EXPLOSION3) {
                        	list_bomb[it]->setMaterialTexture(0, _driver->getTexture("./assets/model3D/rouge.jpg"));
                        	list_bomb[it]->setVisible(true);
                        	list_bomb[it]->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
                        } 	if (_map[y][x].bombState == EXPLOSION4) {
                            list_bomb[it]->setMaterialTexture(0, _driver->getTexture("./assets/model3D/BlackBomb.jpg"));
                        	list_bomb[it]->setVisible(true);
                        	list_bomb[it]->setPosition(irr::core::vector3df(temp_x,temp_y,1.5));
                        }
                    }
                }
            }
        }
	}
}


int Game::getButton()
{
    if (_eventReceiver->getStartStatus() == true)
        return 1;
    return 0;
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
//	_device->drop();
}
