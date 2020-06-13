#include "Settings.hpp"

Settings::Settings(IrrlichtDevice *device, sf::Music *sound, std::stack<IScene *> *stack) {
	this->device = device;
    this->soundEngine = sound;
    this->sceneManager = this->device->getSceneManager();
	this->guiEnv = this->device->getGUIEnvironment();
	this->driver = this->device->getVideoDriver();
	this->scenesStack = stack;
    this->stop = false;
}

Settings::~Settings()
{
}

void Settings::InitPlayerButton()
{
    IGUIButton *Player = guiEnv->addButton(rect<s32>(520,529,750,670), 0, GUI_ID_START_BUTTON);
    video::ITexture *textuPlayer = driver->getTexture("./assets/images/solo.png");
  	Player->setUseAlphaChannel(true);
  	Player->setDrawBorder(false);
	Player->setImage(textuPlayer);
}

void Settings::InitIAButton()
{
    IGUIButton *IA = guiEnv->addButton(rect<s32>(820,529,1050,670), 0, GUI_ID_MULTI_BUTTON);
    video::ITexture *textuIA = driver->getTexture("./assets/images/multi.png");
  	IA->setUseAlphaChannel(true);
  	IA->setDrawBorder(false);
	IA->setImage(textuIA);
}

void Settings::InitBackButton()
{
    IGUIButton *Back = guiEnv->addButton(rect<s32>(24,868,200,1000), 0, GUI_ID_QUIT_BUTTON_CG, L"", L"Back to main menu");
    video::ITexture *textuBack = driver->getTexture("./assets/images/button_back.png");
  	Back->setUseAlphaChannel(true);
  	Back->setDrawBorder(false);
	Back->setImage(textuBack);
}

/*void Settings::InitStartButton()
{
    IGUIButton *Start = guiEnv->addButton(rect<s32>(1520,899,1850,970), 0, GUI_ID_START_BUTTON);
    video::ITexture *textuStart = driver->getTexture("./assets/images/start.png");
  	Start->setUseAlphaChannel(true);
  	Start->setDrawBorder(false);
	Start->setImage(textuStart);
}*/


void 	Settings::init() {

    this->sceneManager->clear();
    this->guiEnv->clear();

    IGUISkin    *skin = guiEnv->getSkin();
    IGUIFont    *font = guiEnv->getFont("./assets/fonts/bigfont.png");
    background = driver->getTexture("./assets/images/Background.jpg");
    box = driver->getTexture("./assets/images/box.png");
    empty_color.set(255, 255, 255, 255);

    if (!font) {
        std::cout << "not found" << std::endl;
    }

    InitPlayerButton();
    InitIAButton();
    InitBackButton();
    //InitStartButton();

    if (font)
        skin->setFont(font);

    skin->setFont(guiEnv->getBuiltInFont(), EGDF_TOOLTIP);

    SAppContextCG *context = new SAppContextCG;
    if (context) {
       context->device = this->getDevice();
       context->counter = 0;
       //context->listbox = guiEnv->addListBox(rect<s32>(750,560,1000,800));
    } else
        throw std::string(strerror(ENOMEM));

    this->eventReceiver = new CGEventReceiver(*context, this->device, this->soundEngine, this->scenesStack, &this->stop);

    if (this->eventReceiver)
        device->setEventReceiver(this->eventReceiver);
    else
        throw std::string(strerror(ENOMEM));
}

int Settings::getButton()
{
    if (eventReceiver->getStartStatus() == true)
        return 4;
    if (eventReceiver->getMultiStatus() == true)
        return 5;
    return 0;
}


void 	Settings::render(void) {

	this->driver->beginScene(true, true, video::SColor(0,255,255,255));
    driver->draw2DImage(background, position2d<s32> (0, 0), rect<s32> (0,0,1920,1080), 0, empty_color, true);
    //driver->draw2DImage(box, position2d<s32> (670, 530), rect<s32> (0,0,350,210), 0, empty_color, true);

	this->guiEnv->drawAll();
	this->driver->endScene();

    if (this->stop) {
        delete scenesStack->top();
        scenesStack->pop();
    }
}
