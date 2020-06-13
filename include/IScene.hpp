#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "../lib/Irrlicht/include/irrlicht.h"

#include <SFML/Audio.hpp>
#include <stack>
#include "cell.hpp"
#include <memory>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class IScene {
public:
	IScene() {}
	IScene(IrrlichtDevice *, sf::Music *, std::stack<IScene *> *) {}
	virtual ~IScene() {}

	virtual void 			init() = 0;
	virtual void 			render() = 0;
	virtual int 			getButton() = 0;
	virtual void 			updateMap(std::vector<std::vector<cell_t>> map) = 0;

	virtual IrrlichtDevice 	*getDevice(void) = 0;
	virtual ISceneManager	*getSceneManager(void) = 0;
	virtual IGUIEnvironment	*getGUIEnv(void) = 0;
	virtual IVideoDriver	*getDriver(void) = 0;
	virtual sf::Music	*getSoundEngine(void) = 0;

	virtual void 			setDevice(IrrlichtDevice *) = 0;
	virtual void 			setSceneManager(ISceneManager *) = 0;
	virtual void 			setGUIEnv(IGUIEnvironment *) = 0;
	virtual void 			setDriver(IVideoDriver *) = 0;
	virtual void 			setSoundEngine(sf::Music	*) = 0;

	virtual ISceneManager* Init_map(scene::ISceneManager* smgr, std::vector<std::vector<cell_t>> _map, int _size, video::IVideoDriver* driver) = 0;

private:
	IrrlichtDevice 			*device;
	ISceneManager			*sceneManager;
	IGUIEnvironment			*guiEnv;
	IVideoDriver 			*driver;
	sf::Music			*soundEngine;
	std::stack<IScene *> 	*scenesStack;
};

#endif /* !ISCENE_HPP_ */
