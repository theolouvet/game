#include<irrlicht/irrlicht.h>
#include <iostream>
#include "myeventreceiver.h"
#include "quake.h"
#include "heros.h"
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

	Heros sydney = Heros();
	

    quake q = quake(device);
	q.addHeros(&sydney);
	q.initiatedHeros();
	sydney.loadTexture(driver->getTexture("media/sydney.bmp"));


	device -> setInputReceivingSceneManager(q.smgr);
	
	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));
        q.draw();	
		driver->endScene();
		sydney.avancer();
	}

	
	device->drop();

	return 0;
}
