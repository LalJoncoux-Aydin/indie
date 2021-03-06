#include "Loose.hpp"

Loose::Loose(IrrlichtDevice *device, std::stack<IScene *> *stack)
{
    _device = device;
    _sceneManager = _device->getSceneManager();
    _guiEnv = _device->getGUIEnvironment();
    _driver = _device->getVideoDriver();
    _scenesStack = stack;
    MusicLoose();
}

void Loose::MusicLoose()
{
    _music.setMusic("./assets/music/Loose.wav");
    _music.musicsetVolume(30);
    _music.musicsetLoop(false);
}

void Loose::initMenuButton()
{
    IGUIButton *Menu = _guiEnv->addButton(rect<s32>(109,913,400,1000), 0, GUI_ID_START_BUTTON, L"", L"Go in game");
    video::ITexture *textuPlay = _driver->getTexture("./assets/images/button_menu.png");
  	Menu->setUseAlphaChannel(true);
  	Menu->setDrawBorder(false);
	Menu->setImage(textuPlay);
}

void Loose::initRestartButton()
{
    IGUIButton *Restart = _guiEnv->addButton(rect<s32>(1510,915,1800,1000), 0, GUI_ID_START_BUTTON, L"", L"Go in game");
    video::ITexture *textuPlay = _driver->getTexture("./assets/images/button_restart.png");
  	Restart->setUseAlphaChannel(true);
  	Restart->setDrawBorder(false);
	Restart->setImage(textuPlay);
}



void Loose::init()
{
    _sceneManager->clear();
    _guiEnv->clear();
    _background = _driver->getTexture("./assets/images/Loose.jpg");
    _empty_color.set(255, 255, 255, 255);


   // initRestartButton();
    //initMenuButton();
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

void Loose::render(void) {

    _driver->beginScene(true, true, video::SColor(0,255,255,255));
    _driver->draw2DImage(_background, position2d<s32> (0,0), rect<s32>(0,0,1920,1080), 0, _empty_color, true);
    _guiEnv->drawAll();
    _driver->endScene();
}

Loose::~Loose()
{
    //_music.stopMusic();
}
