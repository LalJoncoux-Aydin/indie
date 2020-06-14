#ifndef GAME_HPP_
#define GAME_HPP_

#include "IScene.hpp"
#include "EventReceiver.hpp"
#include "ICharacter.hpp"
#include "GameMusic.hpp"

#include <stdlib.h>
#include <vector>

using namespace irr;


class Game : public IScene {

public:
	Game(IrrlichtDevice *, sf::Music *, std::stack<IScene *> *);
	~Game();

	void init();

    void initPlayer1(float x, float z);
    void initMenuButton();
    void initRestartButton();
    void displayPlayer();
	void render(void);
	void updateMap(std::vector<std::vector<cell_t>> map);
    ISceneManager* Init_map(scene::ISceneManager* smgr, std::vector<std::vector<cell_t>> _map, int _size, video::IVideoDriver* driver);
    void MusicGame();
    void MusicTimer();
    void MusicExplosion();
    void MusicDeath();

    int getButton();

    IrrlichtDevice *getDevice(void) {
        return (_device);
    }

	ISceneManager *getSceneManager(void) {
        return (_sceneManager);
    }

	IGUIEnvironment *getGUIEnv(void) {
        return (_guiEnv);
    }

	IVideoDriver *getDriver(void) {
        return (_driver);
    }

    sf::Music *getSoundEngine(void) {
        return (_soundEngine);
    }
    MyEventReceiver1 *getEventReceiver(void) {
        return (receiver);
    }

	void setDevice(IrrlichtDevice *deviceI) {
        _device = deviceI;
    }
	void setSceneManager(ISceneManager *smg) {
        _sceneManager = smg;
    }

	void setGUIEnv(IGUIEnvironment *gui) {
        _guiEnv = gui;
    }

	void setDriver(IVideoDriver *vdriver) {
        _driver = vdriver;
    }

    void setSoundEngine(sf::Music *sound) {
        _soundEngine = sound;
    }

    void setBombe(IMeshSceneNode *bombe) {
        _bombe = bombe;
    }

private:

	IrrlichtDevice 			*_device;
	ISceneManager			*_sceneManager;
	IGUIEnvironment			*_guiEnv;
	IVideoDriver 			*_driver;
  sf::Music            *_soundEngine;
	std::stack<IScene *> 	*_scenesStack;
    IAnimatedMeshSceneNode *_Player1;
    IAnimatedMeshSceneNode *_Player2;
    IAnimatedMeshSceneNode *_Player3;
    IAnimatedMeshSceneNode *_Player4;
    IMeshSceneNode *_bombe;
    IMeshSceneNode *_bombe1;
    std::vector<scene::ISceneNode *> list_bomb;
    GameMusic _music;
    std::vector<scene::ISceneNode *> cubes;

  sf::Sound                  *_music_loop;
  ITexture                *_banner;
  ITexture                *_background;
  ITexture                *_blood;
  SColor                  _empty_color;
  float _x;
  float _y;

  SAppContext             *context;
	MyEventReceiver1				*receiver;
        MyEventReceiver         *_eventReceiver;


    bool isDraw;
    bool isDrawPlayer;
    bool player1Animation;
    bool player2Animation;
    bool player3Animation;
    bool player4Animation;
};

#endif
