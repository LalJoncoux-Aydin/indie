#include <irr/irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

struct SAppContext
{
	irr::IrrlichtDevice *device;
	irr::s32				counter;
	IGUIListBox*	listbox;
	irr::video::IVideoDriver* driver;

};

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,
	HELP = 120,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_PLAY_BUTTON,
	GUI_ID_TRANSPARENCY_SCROLL_BAR
};

class MyEventReceiver : public IEventReceiver
{
	//ETAT DES BOUTONS
public:
	MyEventReceiver(SAppContext &context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();
			irr::video::IVideoDriver* driver = Context.device->getVideoDriver ();
			switch(event.GUIEvent.EventType)
			{
        case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case GUI_ID_QUIT_BUTTON:
					Context.device->closeDevice();
					return true;
				case GUI_ID_PLAY_BUTTON:
					env->clear();
					return true;

				case GUI_ID_NEW_WINDOW_BUTTON:
					{

    				irr::video::SColor blanc;
    				blanc.set(255,255,255,255);
					irr::video::ITexture *window = driver->getTexture("window.png");
					driver->makeColorKeyTexture (window, irr::core::position2d<irr::s32> (0,0));

			        //driver->beginScene(true, true,
			          //  irr::video::SColor (0,120,120,120));
					driver->draw2DImage(window, irr::core::position2d<irr::s32> (0,-10), irr::core::rect<irr::s32> (0,0,500,500),0, blanc, true);
			          //env->drawAll();

    		    	 //driver->endScene ();
					/*IGUIWindow* window = env->addWindow(
						rect<s32>(100 + Context.counter, 100 + Context.counter, 600 + Context.counter, 500 + Context.counter), false, L"HELP");
						  env->addStaticText(L"Test", rect<s32>(35,35,140,50), true, false, window);*/
          }
          return true;
          default:
					return false;
				}
				break;
        		break;

			default:
				break;
			}
		}

		return false;
	}

private:
	SAppContext & Context;
};
