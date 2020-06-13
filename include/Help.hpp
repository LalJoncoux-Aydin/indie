#ifndef HELP_HPP__
#define HELP_HPP__

#include "IScene.hpp"
#include "EventReceiver.hpp"
#include "GameMusic.hpp"


class Help : public IScene {

public:
	Help(IrrlichtDevice *, sf::Music *, std::stack<IScene *> *);
	~Help();
	void init();
	void render(void);
    void updateMap(__attribute__((unused)) std::vector<std::vector<cell_t>> map) {
    };
     ISceneManager* Init_map(__attribute__((unused)) scene::ISceneManager* smgr, __attribute__((unused)) std::vector<std::vector<cell_t>> _map, __attribute__((unused)) int _size, __attribute__((unused)) video::IVideoDriver* driver){
         return smgr;
    };


    int getButton() {
        return 0;
    };
    void InitButtonBack();
    void InitScrollBar();
    void hoverBack();

    IrrlichtDevice *getDevice(void) {
        return (device);
    };

	ISceneManager *getSceneManager(void) {
        return (sceneManager);
    };

	IGUIEnvironment	*getGUIEnv(void) {
        return (guiEnv);
    };

	IVideoDriver *getDriver(void) {
        return (driver);
    };

    sf::Music *getSoundEngine(void) {
        return (soundEngine);
    };
    OptEventReceiver *getEventReceiver(void) {
        return (eventReceiver);
    };

	void setDevice(IrrlichtDevice *deviceI) {
        device = deviceI;
    };
	void setSceneManager(ISceneManager *smg) {
        sceneManager = smg;
    };

	void setGUIEnv(IGUIEnvironment *gui) {
        guiEnv = gui;
    };

	void setDriver(IVideoDriver *vdriver) {
        driver = vdriver;
    };

    void setSoundEngine(sf::Music *sound) {
        soundEngine = sound;
    };

    void setEventReceiver(OptEventReceiver *event) {
        eventReceiver = event;
    };

private:

	IrrlichtDevice 			*device;
	ISceneManager			*sceneManager;
	IGUIEnvironment			*guiEnv;
	IVideoDriver 			*driver;
    sf::Music            *soundEngine;
	std::stack<IScene *> 	*scenesStack;
    ITexture                *background;
    GameMusic _pause;
    ITexture                *d;
    ITexture                *q;
    ITexture                *s;
    ITexture                *z;
    ITexture                *up;
    ITexture                *left;
    ITexture                *right;
    ITexture                *down;
    ITexture                *o;
    ITexture                *k;
    ITexture                *l;
    ITexture                *m;
    ITexture                *player1;
    ITexture                *player2;
    ITexture                *player3;
    ITexture                *musi;
    SColor                  empty_color;
    OptEventReceiver        *eventReceiver;
    bool                    stop;
};

#endif
