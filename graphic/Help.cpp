#include "Help.hpp"


Help::Help(IrrlichtDevice *device, sf::Music *sound, std::stack<IScene *> *stack) { 
	this->device = device;
    this->soundEngine = sound;
    this->sceneManager = this->device->getSceneManager();
	this->guiEnv = this->device->getGUIEnvironment();
	this->driver = this->device->getVideoDriver();
	this->scenesStack = stack;
    this->stop = false;
    //_pause.stopMusic();
}

Help::~Help()
{
}

void Help::InitButtonBack()
{
    IGUIButton *Back = guiEnv->addButton(rect<s32>(874,768,1050,900), 0, GUI_ID_QUIT_BUTTON_OPT, L"", L"Return in menu");
    video::ITexture *textuBack = driver->getTexture("./assets/images/button_back.png");
  	Back->setUseAlphaChannel(true);
  	Back->setDrawBorder(false);
	Back->setImage(textuBack);
}

void Help::hoverBack()
{
    IGUIButton *Back = guiEnv->addButton(rect<s32>(940,810,990,860), 0, GUI_ID_BUTTON, L"", L"Wsh");
    video::ITexture *textuBack = driver->getTexture("./assets/images/mb.png");
  	Back->setUseAlphaChannel(true);
  	Back->setDrawBorder(false);
	Back->setImage(textuBack);
}

void Help::InitScrollBar()
{
    IGUIScrollBar* scrollbar = guiEnv->addScrollBar(true,rect<s32>(1450,830,1700,860), 0, GUI_ID_MUSIC_VOLUME);
    scrollbar->setMax(100);
   //scrollbar->setPos(soundEngine->getVolume() * 100);
}

void Help::init() {
    //_pause.stopMusic("./assets/music/Menu.wav");

    this->sceneManager->clear();
    this->guiEnv->clear();



    background = driver->getTexture("./assets/images/window.png");
    musi = driver->getTexture("./assets/images/button_music.png");
    player1 = driver->getTexture("./assets/images/player.png");
    player2 = driver->getTexture("./assets/images/ia.png");
    /*player3 = driver->getTexture("./assets/images/player2.png");
    o = driver->getTexture("./assets/images/o.jpg");
    k = driver->getTexture("./assets/images/k.jpg");
    l = driver->getTexture("./assets/images/l.jpg");
    m = driver->getTexture("./assets/images/m.jpg");*/
    up = driver->getTexture("./assets/images/up.jpg");
    left = driver->getTexture("./assets/images/left.jpg");
    right = driver->getTexture("./assets/images/right.jpg");
    down = driver->getTexture("./assets/images/down.jpg");
    z = driver->getTexture("./assets/images/z.jpg");
    q = driver->getTexture("./assets/images/q.jpg");
    s = driver->getTexture("./assets/images/s.jpg");
    d = driver->getTexture("./assets/images/d.jpg");
    background = driver->getTexture("./assets/images/window.png");
    empty_color.set(255, 255, 255, 255);

    InitButtonBack();
    InitScrollBar();

    hoverBack();



    SAppContextOpt *context = new SAppContextOpt;

    if (context) {
        context->device = this->getDevice();
        context->counter = 0;
    } else
        throw std::string(strerror(ENOMEM));

    this->eventReceiver = new OptEventReceiver(*context, this->device, this->soundEngine, this->scenesStack, &this->stop);

    if (this->eventReceiver)
        device->setEventReceiver(this->eventReceiver);
    else
        throw std::string(strerror(ENOMEM));
}


void Help::render(void) {

	this->driver->beginScene(true, true, video::SColor(0,255,255,255));
    driver->draw2DImage(background, position2d<s32> (-30, -30), rect<s32> (0,0,1980,1080), 0, empty_color, true);
    driver->draw2DImage(musi, position2d<s32> (1300, 800), rect<s32> (0,0,130,79), 0, empty_color, true);
    driver->draw2DImage(player1, position2d<s32> (200, 870), rect<s32> (0,0,60,64), 0, empty_color, true);
    driver->draw2DImage(player2, position2d<s32> (400, 870), rect<s32> (0,0,60,64), 0, empty_color, true);
    /*driver->draw2DImage(player3, position2d<s32> (600, 870), rect<s32> (0,0,60,64), 0, empty_color, true);
   driver->draw2DImage(o, position2d<s32> (600, 768), rect<s32> (0,0,50,50), 0, empty_color, true);
   driver->draw2DImage(k, position2d<s32> (550, 820), rect<s32> (0,0,50,50), 0, empty_color, true);
   driver->draw2DImage(l, position2d<s32> (600, 820), rect<s32> (0,0,50,50), 0, empty_color, true);
   driver->draw2DImage(m, position2d<s32> (650, 820), rect<s32> (0,0,50,50), 0, empty_color, true);*/
    driver->draw2DImage(up, position2d<s32> (200, 768), rect<s32> (0,0,50,50), 0, empty_color, true);
    driver->draw2DImage(down, position2d<s32> (200, 820), rect<s32> (0,0,50,50), 0, empty_color, true);
    driver->draw2DImage(left, position2d<s32> (150, 820), rect<s32> (0,0,50,50), 0, empty_color, true);
    driver->draw2DImage(right, position2d<s32> (250, 820), rect<s32> (0,0,50,50), 0, empty_color, true);
    driver->draw2DImage(z, position2d<s32> (400, 768), rect<s32> (0,0,50,50), 0, empty_color, true);
    driver->draw2DImage(q, position2d<s32> (350, 820), rect<s32> (0,0,50,50), 0, empty_color, true);
    driver->draw2DImage(s, position2d<s32> (400, 820), rect<s32> (0,0,50,50), 0, empty_color, true);
    driver->draw2DImage(d, position2d<s32> (450, 820), rect<s32> (0,0,50,50), 0, empty_color, true);
	this->guiEnv->drawAll();
	this->driver->endScene();

    if (this->stop) {
        delete scenesStack->top();
        scenesStack->pop();
    }
}
