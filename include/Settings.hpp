#ifndef SETTINGS_HPP__
#define SETTINGS_HPP__
#include "IScene.hpp"
#include "EventReceiver.hpp"
#include "GameMusic.hpp"
#include <errno.h>
#include <string.h>

class Settings : public IScene {

public:
	Settings(IrrlichtDevice *, sf::Music *, std::stack<IScene *> *);
	~Settings();
    void InitPlayerButton();
    void InitIAButton();
    void InitBackButton();
    void InitStartButton();
    void updateMap(__attribute__((unused)) std::vector<std::vector<cell_t>> map) {
    };
     ISceneManager* Init_map(__attribute__((unused)) scene::ISceneManager* smgr, __attribute__((unused)) std::vector<std::vector<cell_t>> _map, __attribute__((unused)) int _size, __attribute__((unused)) video::IVideoDriver* driver){
         return smgr;
    };


	void init();
	void render(void);
    int getButton();

	IrrlichtDevice *getDevice(void) {
        return (device);
    }

	ISceneManager *getSceneManager(void) {
        return (sceneManager);
    }

	IGUIEnvironment *getGUIEnv(void) {
        return (guiEnv);
    }

	IVideoDriver *getDriver(void) {
        return (driver);
    }

    sf::Music *getSoundEngine(void) {
        return (soundEngine);
    }
    CGEventReceiver *getEventReceiver(void) {
        return (eventReceiver);
    }

	void setDevice(IrrlichtDevice *deviceI) {
        device = deviceI;
    }
	void setSceneManager(ISceneManager *smg) {
        sceneManager = smg;
    }

	void setGUIEnv(IGUIEnvironment *gui) {
        guiEnv = gui;
    }

	void setDriver(IVideoDriver *vdriver) {
        driver = vdriver;
    }

    void setSoundEngine(sf::Music *sound) {
        soundEngine = sound;
    }

    void setEventReceiver(CGEventReceiver *event) {
        eventReceiver = event;
    }
    void printCharacter(int);

private:
	IrrlichtDevice 			*device;
	ISceneManager			*sceneManager;
	IGUIEnvironment			*guiEnv;
	IVideoDriver 			*driver;
    sf::Music            *soundEngine;
	std::stack<IScene *> 	    *scenesStack;
    CGEventReceiver        *eventReceiver;
    MyEventReceiver *_eventReceiver;
    ITexture                *background;
    ITexture                *box;
    bool                    stop;
    SColor                  empty_color;

};

#endif
