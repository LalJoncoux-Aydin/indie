#ifndef MENU_HPP_
#define MENU_HPP_

#include "IScene.hpp"
#include "EventReceiver.hpp"
#include "GameMusic.hpp"

class Menu : public IScene {

public:
	Menu(IrrlichtDevice *,std::stack<IScene *> *);
	~Menu();

	void init();
	void render(void);
    void InitPlayButton();
    void InitHelpButton();
    void InitExitButton();
    void InitNewButton();
    void hoverPlayButton();
    void hoverHelpButton();
    void hoverExitButton();
    void hoverNewButton();
    void MusicMenu();

    void updateMap(__attribute__((unused)) std::vector<std::vector<cell_t>> map) {
    };
     ISceneManager* Init_map(__attribute__((unused)) scene::ISceneManager* smgr, __attribute__((unused)) std::vector<std::vector<cell_t>> _map, __attribute__((unused)) int _size, __attribute__((unused)) video::IVideoDriver* driver){
         return smgr;
    };
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
    MyEventReceiver *getEventReceiver(void) {
        return (_eventReceiver);
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

private:

	IrrlichtDevice 			*_device;
	ISceneManager			*_sceneManager;
	IGUIEnvironment			*_guiEnv;
	IVideoDriver 			*_driver;
    sf::Music            *_soundEngine;
	std::stack<IScene *> 	*_scenesStack;
     GameMusic _music;

    MyEventReceiver         *_eventReceiver;
    sf::Sound                  *_music_loop;
    ITexture                *_banner;
    ITexture                *_background;
    SColor                  _empty_color;

    SAppContext             *context;

};

#endif
