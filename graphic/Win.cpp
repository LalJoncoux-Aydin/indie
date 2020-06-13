#include "Win.hpp"

Win::Win(IrrlichtDevice *device, std::stack<IScene *> *stack)
{
    _device = device;
    _sceneManager = _device->getSceneManager();
    _guiEnv = _device->getGUIEnvironment();
    _driver = _device->getVideoDriver();
    _scenesStack = stack;
}


void Win::init()
{
    _sceneManager->clear();
    _guiEnv->clear();
    _background = _driver->getTexture("./assets/images/Win.jpg");
    _empty_color.set(255, 255, 255, 255);

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

void Win::render(void) {

    _driver->beginScene(true, true, video::SColor(0,255,255,255));
    _driver->draw2DImage(_background, position2d<s32> (0,0), rect<s32>(0,0,1920,1080), 0, _empty_color, true);
    _guiEnv->drawAll();
    _driver->endScene();
}

Win::~Win()
{
}