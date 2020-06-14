#include "Menu.hpp"
#include <time.h>
#include <unistd.h>
#include <thread>

Menu::Menu(IrrlichtDevice *device, std::stack<IScene *> *stack) {



	_device = device;
    //_soundEngine = sound;
    _sceneManager = _device->getSceneManager();
	_guiEnv = _device->getGUIEnvironment();
	_driver = _device->getVideoDriver();
	_scenesStack = stack;
    MusicMenu();

    //_music_loop = NULL;

}

void Menu::MusicMenu()
{
    _music.setMusic("./assets/music/Menu.wav");
    _music.musicsetVolume(30);
    _music.musicsetLoop(false);
}


void Menu::InitNewButton()
{

	//static auto			timer = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double, std::milli>	time_span = std::chrono::high_resolution_clock::now() - timer;

    IGUIButton *New = _guiEnv->addButton(rect<s32>(700,341,1200,425), 0, GUI_ID_PLAY_BUTTON, L"", L"Go in game");
    video::ITexture *textuNew = _driver->getTexture("./assets/images/button_new-game.png");
  	New->setUseAlphaChannel(true);
  	New->setDrawBorder(false);
	New->setImage(textuNew);

}

void Menu::hoverPlayButton()
{
    IGUIButton *New = _guiEnv->addButton(rect<s32>(861,370,1050,390), 0, GUI_ID_BUTTON, L"", L"Go in game");
    video::ITexture *textuNew = _driver->getTexture("./assets/images/bm.png");
  	New->setUseAlphaChannel(true);
  	New->setDrawBorder(false);
	New->setImage(textuNew);
}

void Menu::InitPlayButton()
{
    IGUIButton *Play = _guiEnv->addButton(rect<s32>(700,518,1200,600), 0, GUI_ID_START_BUTTON, L"", L"Go in game");
    video::ITexture *textuPlay = _driver->getTexture("./assets/images/button_play.png");
  	Play->setUseAlphaChannel(true);
  	Play->setDrawBorder(false);
	Play->setImage(textuPlay);
}

void Menu::hoverNewButton()
{
    IGUIButton *Play = _guiEnv->addButton(rect<s32>(861,545,1050,565), 0, GUI_ID_BUTTON, L"", L"Go in game");
    video::ITexture *textuPlay = _driver->getTexture("./assets/images/bm.png");
  	Play->setUseAlphaChannel(true);
  	Play->setDrawBorder(false);
	Play->setImage(textuPlay);
}

void Menu::InitHelpButton()
{
    IGUIButton *Help = _guiEnv->addButton(rect<s32>(700,700,1200,790), 0, GUI_ID_OPTIONS_BUTTON, L"", L"Help and Settings");
    video::ITexture *textuHelp = _driver->getTexture("./assets/images/button_help.png");
  	Help->setUseAlphaChannel(true);
  	Help->setDrawBorder(false);
	Help->setImage(textuHelp);
}

void Menu::hoverHelpButton()
{
    IGUIButton *Help = _guiEnv->addButton(rect<s32>(861,735,1050,755), 0, GUI_ID_BUTTON, L"", L"Help and Settings");
    video::ITexture *textuHelp = _driver->getTexture("./assets/images/bm.png");
  	Help->setUseAlphaChannel(true);
  	Help->setDrawBorder(false);
	Help->setImage(textuHelp);
}

void Menu::InitExitButton()
{
    IGUIButton *Quit = _guiEnv->addButton(rect<s32>(700,889,1200,970), 0, GUI_ID_QUIT_BUTTON, L"", L"Exit");
    video::ITexture *textuQuit = _driver->getTexture("./assets/images/button_exit.png");
  	Quit->setUseAlphaChannel(true);
  	Quit->setDrawBorder(false);
	Quit->setImage(textuQuit);
}

void Menu::hoverExitButton()
{
    IGUIButton *Quit = _guiEnv->addButton(rect<s32>(861,915,1050,935), 0, GUI_ID_BUTTON, L"", L"Exit");
    video::ITexture *textuQuit = _driver->getTexture("./assets/images/bm.png");
  	Quit->setUseAlphaChannel(true);
  	Quit->setDrawBorder(false);
	Quit->setImage(textuQuit);
}

void Menu::init() {
    _sceneManager->clear();
    _guiEnv->clear();


    IGUISkin    *skin = _guiEnv->getSkin();
    skin->setFont(_guiEnv->getBuiltInFont(), EGDF_TOOLTIP);
    _background = _driver->getTexture("./assets/images/title_bg.png");
    _empty_color.set(255, 255, 255, 255);

    /*if (music_loop == NULL)
        this->music_loop = this->soundEngine->play("", true, false, true);
*/
    InitNewButton();
    InitPlayButton();

    InitHelpButton();
    InitExitButton();
    hoverPlayButton();
    hoverNewButton();
    hoverHelpButton();
    hoverExitButton();


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

int Menu::getButton() {
    if (_eventReceiver->getGameStatus() == true)
        return 2;
    if (_eventReceiver->getOptionStatus() == true)
        return 3;

    if (_eventReceiver->getStartStatus() == true)
        return 6;
    return 0;
}

void Menu::render(void) {


  //   sf::Music music;



	_driver->beginScene(true, true, video::SColor(0,255,255,255));
   // sleep(1);
    _driver->draw2DImage(_background, position2d<s32> (0, 0), rect<s32> (0,0,1920,1080), 0, _empty_color, true);
//        music.play();
    //sleep(10);

	_guiEnv->drawAll();
    _driver->endScene();

}

Menu::~Menu()
{
   // _music.stopMusic();
}
