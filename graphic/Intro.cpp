#include "Intro.hpp"
#include <unistd.h>
#include <thread>
//#include <ITimer.h>
#include <time.h>
#include <ctime>


Intro::Intro(IrrlichtDevice *device, std::stack <IScene *> *stack)
{
    _device = device;
    _sceneManager = _device->getSceneManager();
    _guiEnv = _device->getGUIEnvironment();
    _driver = _device->getVideoDriver();
    _scenesStack = stack;
    MusicIntro();
}

Intro::~Intro()
{
    //_music.stopMusic();
}

void Intro::MusicIntro()
{
    _music.setMusic("./assets/music/Intro.wav");
    _music.musicsetVolume(5);
    _music.musicsetLoop(false);
}



void Intro::InitStartButton()
{
    IGUIButton *New = _guiEnv->addButton(rect<s32>(770,879,1100,950), 0, GUI_ID_INTRO, L"", L"Go in game");
    video::ITexture *textuNew = _driver->getTexture("./assets/images/start.png");
  	New->setUseAlphaChannel(true);
  	New->setDrawBorder(false);
	New->setImage(textuNew);

}

void Intro::hoverIntroButton()
{
    IGUIButton *Play = _guiEnv->addButton(rect<s32>(831,910,1020,920), 0, GUI_ID_BUTTON, L"", L"Go in game");
    video::ITexture *textuPlay = _driver->getTexture("./assets/images/bm.png");
  	Play->setUseAlphaChannel(true);
  	Play->setDrawBorder(false);
	Play->setImage(textuPlay);
}

void Intro::init() {
    _sceneManager->clear();
    _guiEnv->clear();


    //IGUIImage *caca = _device->

    IGUISkin    *skin = _guiEnv->getSkin();
    skin->setFont(_guiEnv->getBuiltInFont(), EGDF_TOOLTIP);
    _background = _driver->getTexture("./assets/images/menu.png");
    _empty_color.set(255, 255, 255, 255);
        //sleep(2);


    _lal = _driver->getTexture("./assets/images/Lal.png");

    _logo = _driver->getTexture("./assets/images/logo.png");
    _armand = _driver->getTexture("./assets/images/Armand.png");
    _camille = _driver->getTexture("./assets/images/Camille.png");
    _louis = _driver->getTexture("./assets/images/Louis.png");
    _zoe = _driver->getTexture("./assets/images/Zoe.png");
    _jo = _driver->getTexture("./assets/images/Jo.png");
    _pres = _driver->getTexture("./assets/images/pres.png");
    _ent = _driver->getTexture("./assets/images/sents.png");
    _t = _driver->getTexture("./assets/images/t.png");
    _pied = _driver->getTexture("./assets/images/pied.png");
    _bomb = _driver->getTexture("./assets/images/bomb.png");
    _title = _driver->getTexture("./assets/images/logobom.png");


       /*scene::IParticleSystemSceneNode* ps =
        _sceneManager->addParticleSystemSceneNode(false);

    scene::IParticleEmitter* em = ps->createBoxEmitter(
        core::aabbox3d<f32>(-7,0,-7,7,1,7), // taille de l'émetteur
        core::vector3df(0.0f,0.06f,0.0f),   // position initiale
        80,100,                             // taux d'émission
        video::SColor(0,255,255,255),       // la couleur la plus sombre
        video::SColor(0,255,255,255),       // la couleur la plus lumineuse
        800,2000,0,                         // minimum et maximum âge, angle
        core::dimension2df(10.f,10.f),         // taille minimum
        core::dimension2df(20.f,20.f));        // taille maximum

    ps->setEmitter(em); // Ceci prend l'émetteur
    em->drop(); // Donc on peut le jeter sans qu'il soit supprimé.

    scene::IParticleAffector* paf = ps->createFadeOutParticleAffector();

    ps->addAffector(paf); // de même pour l'affecteur
    paf->drop();

    ps->setPosition(core::vector3df(-70,60,40));
    ps->setScale(core::vector3df(2,2,2));
    ps->setMaterialFlag(video::EMF_LIGHTING, false);
    ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialTexture(0, _driver->getTexture("./assets/images/fire.bmp"));
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    */

   // _logo->




    //displayImage();
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

int Intro::getButton()
{
    if (_eventReceiver->getIntroStatus() == true)
        return 1;
    return 0;
}

void Intro::render(void) {

    //static clock_t start;
    //irr::core::recti *_rect;
    //clock_t end;
    long lck = CLOCKS_PER_SEC;
    static u32 time = _device->getTimer()->getTime();
    //auto start = std::chrono::high_resolution_clock::now();
    //irr::ITimer *caca;
    //caca->start();

    //std::cout << caca->getTime() << std::endl;
    //time_t start;
   // start = 0;
    //_rect[0].operator+=(vector2di(10,0));

    //IMeshSceneNode *de = _sceneManager->
    //start = clock();
  //   sf::Music music;
  //u32 caca = 2;

//std::this_thread::sleep_for(std::chrono::milliseconds(2000));


	_driver->beginScene(true, true, video::SColor(0,0,0,0));
   // sleep(1);
    //start = clock();

    //sleep(3);
    //750000
    //start = clock();
    if (_device->getTimer()->getTime() - time / 1000.f > 3300) {
    _driver->draw2DImage(_logo, position2d<s32> (675, 0), rect<s32> (0,0,500,500), 0, _empty_color, true);
    }

    if (_device->getTimer()->getTime() - time / 1000.f > 6300) {

    _driver->draw2DImage(_lal, position2d<s32> (150, 100), rect<s32> (0,0,110,147), 0, _empty_color, true);
    }






    if (_device->getTimer()->getTime() - time / 1000.f > 8000) {
    _driver->draw2DImage(_armand, position2d<s32> (1600, 100), rect<s32> (0,0,110,147), 0, _empty_color, true);
    }



    if (_device->getTimer()->getTime() - time / 1000.f > 10000) {
    _driver->draw2DImage(_camille, position2d<s32> (150, 450), rect<s32> (0,0,110,147), 0, _empty_color, true);
    }


    if (_device->getTimer()->getTime() - time / 1000.f > 12000) {
    _driver->draw2DImage(_jo, position2d<s32> (1600, 450), rect<s32> (0,0,110,147), 0, _empty_color, true);
    }

    if (_device->getTimer()->getTime() - time / 1000.f > 14000) {
    _driver->draw2DImage(_louis, position2d<s32> (150, 800), rect<s32> (0,0,110,147), 0, _empty_color, true);
    }

    if (_device->getTimer()->getTime() - time / 1000.f > 14200) {
    _driver->draw2DImage(_zoe, position2d<s32> (1600, 800), rect<s32> (0,0,110,147), 0, _empty_color, true);
    }

    if (_device->getTimer()->getTime() - time / 1000.f > 16500) {
    _driver->draw2DImage(_pres, position2d<s32> (665, 500), rect<s32> (0,0,250,104), 0, _empty_color, true);
    }

    if (_device->getTimer()->getTime() - time / 1000.f > 16700) {
    _driver->draw2DImage(_ent, position2d<s32> (905, 507), rect<s32> (0,0,250,83), 0, _empty_color, true);
    }


    if (_device->getTimer()->getTime() - time / 1000.f > 16800) {
    _driver->draw2DImage(_t, position2d<s32> (1150, 502), rect<s32> (0,0,50,93), 0, _empty_color, true);
    }

    if (_device->getTimer()->getTime() - time / 1000.f > 18000) {
    _driver->draw2DImage(_pied, position2d<s32> (400, 270), rect<s32> (0,0,150,150), 0, _empty_color, true);
    }

    if (_device->getTimer()->getTime() - time / 1000.f > 18500) {
    _driver->draw2DImage(_bomb, position2d<s32> (1300, 270), rect<s32> (0,0,150,150), 0, _empty_color, true);
    }

    if (_device->getTimer()->getTime() - time / 1000.f > 22300) {
    _driver->draw2DImage(_title, position2d<s32> (675, 700), rect<s32> (0,0,500,139), 0, _empty_color, true);
    }

   // if (start > 2100000)
    //{

   // if (_device->getTimer()->getTime() - time / 1000.f > 24300) {
        InitStartButton();
        hoverIntroButton();
   // _driver->draw2DImage(_title, position2d<s32> (675, 700), rect<s32> (0,0,500,139), 0, _empty_color, true);
    //}
    //}
    //system("pause");
    //timer();


   // end = clock();
//        music.play();
    //sleep(10);

	_guiEnv->drawAll();
    //displayImage();

    _driver->endScene();

}
