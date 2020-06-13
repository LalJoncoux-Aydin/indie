#ifndef EVENTRECEIVER_HPP_
#define EVENTRECEIVER_HPP_

// Standard libs
#include <iostream>
#include <cstring>
#include <list>
#include <errno.h>
#include <string.h>
#include <stack>
#include "GameMusic.hpp"
// Local libs
#include "IScene.hpp"
// Define


// Struct
struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};


struct SAppContextCG {
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

struct SAppContextOpt {
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

// Enum
enum
{
    GUI_ID_PLAY_BUTTON = 101,
    GUI_ID_START_BUTTON,
    GUI_ID_SCORE_BUTTON,
    GUI_ID_OPTIONS_BUTTON,
    GUI_ID_INTRO,
    GUI_ID_BUTTON,
    GUI_ID_QUIT_BUTTON,
    GUI_ID_MULTI_BUTTON,
    GUI_ID_QUIT_BUTTON_CG = 101,
    GUI_ID_ADDPLAYER_BUTTON,
    GUI_ID_ADDIA_BUTTON,
    GUI_ID_PLAYBUTTON_CG,
    GUI_ID_QUIT_BUTTON_OPT = 101,
    GUI_ID_MUSIC_VOLUME

};


class MyEventReceiver1 : public IEventReceiver
{
  public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
      // Remember whether each key is down or up
      if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

      return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
      return KeyIsDown[keyCode];
    }

    MyEventReceiver1()
    {
      for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
    }

  private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

// Class
class MyEventReceiver : public IEventReceiver
{
public:
    MyEventReceiver(SAppContext & context, IrrlichtDevice *_device, sf::Music *_engine, std::stack<IScene *> *_scenesStack, sf::Sound *_music_loop)
    : Context(context), device(_device), engine(_engine), scenesStack(_scenesStack), music_loop(_music_loop) { }

    virtual bool OnEvent(const SEvent& event)
    {

        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType) {

            case EGET_ELEMENT_HOVERED:
                switch(id) {
                    case GUI_ID_BUTTON:
                    _music.setMusic("./assets/music/button.wav");
                    _music.musicsetVolume(30);
                }
                return true;

            case EGET_BUTTON_CLICKED:
                switch(id) {

                case GUI_ID_PLAY_BUTTON: {
                    _game = true;
                    }
                    return true;

                case GUI_ID_INTRO: {
                    _intro = true;
                }
                return true;


                case GUI_ID_START_BUTTON: {
                    _start = true;

                    _music.setMusic("./assets/music/Shit.wav");
                    _music.musicsetVolume(100);
                    _music.soundsetLoop(false);
                    //music.play();
                    }
                    return true;

                case GUI_ID_OPTIONS_BUTTON: {
                    _options = true;
                    }
                    return true;


                case GUI_ID_QUIT_BUTTON:
                    Context.device->closeDevice();
                    return true;

                default:
                    return false;
                }
                break;

            default:
                break;
            }
        }

        return false;
    }

    virtual bool getGameStatus()
    {
        return _game;
    }

    virtual bool getOptionStatus()
    {
        return _options;
    }

virtual bool getStartStatus()
    {
        return _start;
    }
    
    virtual bool getIntroStatus()
    {
        return _intro;
    }

private:
    SAppContext             &Context;
    bool                    _start = false;
    bool                    _multi = false;
    IrrlichtDevice          *device;
    GameMusic _music;
    sf::Music            *engine;
    sf::Sound                  *music_loop;
    std::stack<IScene *>    *scenesStack;
    bool                    _game = false;
    bool                    _options = false;
    bool                    _intro = false;
};

class CGEventReceiver : public IEventReceiver
{
public:
    CGEventReceiver(SAppContextCG & context, IrrlichtDevice *_device, sf::Music *_engine, std::stack<IScene *> *_scenesStack, bool *_stop)
    : Context(context), device(_device), engine(_engine), scenesStack(_scenesStack), stop(_stop) { }
    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType) {

            case EGET_BUTTON_CLICKED:
                switch(id) {

                case GUI_ID_QUIT_BUTTON_CG:
                    *(stop) = true;
                    return true;

                case GUI_ID_START_BUTTON: {
                    _start = true;
                    _music.setMusic("./assets/music/Start.wav");
                    _music.musicsetVolume(30);
                    _music.soundsetLoop(false);
                    }
                    return true;

                case GUI_ID_MULTI_BUTTON: {
                    _multi = true;

                    _music.setMusic("./assets/music/Start.wav");
                    _music.musicsetVolume(100);
                    _music.soundsetLoop(false);
                    //music.play();
                    }
                    return true;

                default:
                    return false;
                }
                break;

                return true;

            default:
                break;
            }
        }

        return false;
    }

virtual bool getStartStatus()
    {
        return _start;
    }
    virtual bool getMultiStatus()
    {
        return _multi;
    }

private:
    SAppContextCG           &Context;
    IrrlichtDevice          *device;
    sf::Music            *engine;
    GameMusic _music;
    std::stack<IScene *>    *scenesStack;
    bool                    *stop;
    bool                    _start = false;
    bool                    _multi = false;


};

class OptEventReceiver : public IEventReceiver
{
public:
    OptEventReceiver(SAppContextOpt & context, IrrlichtDevice *_device, sf::Music *_engine, std::stack<IScene *> *_scenesStack, bool *_stop)
    : Context(context), device(_device), engine(_engine), scenesStack(_scenesStack), stop(_stop){ }

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType) {

            case EGET_ELEMENT_HOVERED:
                switch(id) {
                    case GUI_ID_BUTTON:
                    _music.setMusic("./assets/music/button.wav");
                    _music.musicsetVolume(30);
                }
                return true;
            case EGET_BUTTON_CLICKED:
                switch(id) {

                case GUI_ID_QUIT_BUTTON_OPT:
                    *(stop) = true;
                    return true;

                default:
                    return false;
                }
                break;

            case EGET_SCROLL_BAR_CHANGED:
                if (id == GUI_ID_MUSIC_VOLUME)
                {
                    s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                    //float volume = (float)pos / (float)100;
                    //engine->setVolume(volume);
                }
                break;

            case EGET_LISTBOX_CHANGED: {
                    *mapID = Context.listbox->getSelected();
                }
                return true;

            default:
                break;
            }
        }

        return false;
    }

private:
    SAppContextOpt          &Context;
    IrrlichtDevice          *device;
    sf::Music            *engine;
    GameMusic _music;
    std::stack<IScene *>    *scenesStack;
    bool                    *stop;
    int                     *mapID;
    bool                    _start = false;

};

#endif /* !EVENTRECEIVER_HPP_ */
