#include<irrlicht/irrlicht.h>
#include <iostream>
#include "myeventreceiver.h"
#include "quake.h"
#include <chrono>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
std::chrono::time_point<std::chrono::system_clock> start, end;
float t;
IVideoDriver* driver;
ISceneManager* smgr ;
IrrlichtDevice *device;

    enum
{
    // I use this ISceneNode ID to indicate a scene node that is
    // not pickable by getSceneNodeAndCollisionPointFromRay()
    ID_IsNotPickable = 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be picked by ray selection.
    IDFlag_IsPickable = 1 << 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be highlighted.  In this example, the
    // homonids can be highlighted, but the level mesh can't.
    IDFlag_IsHighlightable = 1 << 1
};

int main()
{
	MyEventReceiver receiver;
	
	device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, &receiver);
	if (!device)
		return 1;
	device->setWindowCaption(L"game");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
    quake q = quake(device);
	device -> setInputReceivingSceneManager(q.smgr);
	
	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));
        q.draw();	
		driver->endScene();
	}

	
	device->drop();

	return 0;
}
