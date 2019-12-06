#include<irrlicht/irrlicht.h>
#include <iostream>
#include "myeventreceiver.h"
#include "scenes/quake.h"
#include "entites/heros.h"
#include "camera/camera.h"
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
Heros sydney;
MyEventReceiver receiver;
Camera cam;

bool ani = false;
bool keyrelease = true;
bool freecam = false;
irr::SKeyMap keyMap[5];
ICameraSceneNode* camfree;


void keyreception(){
    
    

    if(receiver.IsKeyDown(KEY_KEY_P) ){
        keyrelease =! keyrelease;
        cam.switchView();
    }	
        if(receiver.IsKeyDown(KEY_KEY_Z)){
            if(sydney.node != NULL)
                sydney.avancer();
            cam.updateCamera(&sydney);
            ani = true;
        }else if(receiver.IsKeyDown(KEY_KEY_S)){
            sydney.reculer();
            cam.updateCamera(&sydney);
            ani = true;
        }if(receiver.IsKeyDown(KEY_KEY_A) && cam.ActiveId != cam.IdFps){
            sydney.turnleft();
            cam.updateCamera(&sydney);
            ani = true;
        }if(receiver.IsKeyDown(KEY_KEY_E)  && cam.ActiveId != cam.IdFps ){
            sydney.turnright();
            cam.updateCamera(&sydney);
            ani = true;
        }
        if((receiver.IsKeyDown(KEY_KEY_A) ||
           receiver.IsKeyDown(KEY_KEY_Z) ||
           receiver.IsKeyDown(KEY_KEY_E) ||
           receiver.IsKeyDown(KEY_KEY_S)) && cam.ActiveId != cam.IdFps){ 
            sydney.run();
        }else
        {
            sydney.stand();
        }
        
        
        if(receiver.IsKeyDown(KEY_KEY_W)){
            device->drop();
        }
    

}


int main()
{
	
	
	device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, &receiver);
	if (!device)
		return 1;
	device->setWindowCaption(L"game");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();

    sydney = Heros();
    IAnimatedMesh* heros_mesh = smgr ->getMesh("media/sydney.md2");
	

    quake q = quake(device);
	q.addHeros(&sydney);
	q.initiatedHeros();
    
	sydney.loadTexture(driver->getTexture("media/sydney.bmp"));

	keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_Z;        // Z
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;        // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_A;        // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;        // d
    keyMap[4].Action = irr::EKA_JUMP_UP;       // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;        // barre espace
    camfree =  smgr->addCameraSceneNodeFPS(
            0,
    100,
    10.0f,
    -1,
    0,//keymap
    5
    );
    camfree->setFarValue(30000.0f);


    cam = Camera(q.smgr);
    cam.initiateFPScam(sydney.node);
    cam.initiateTPScam(sydney.node);
    q.setCam(&cam);

	
	device -> setInputReceivingSceneManager(q.smgr);

	int lastFPS = -1;
	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));
        q.draw();
        //smgr->drawAll();	
        keyreception();
		driver->endScene();
		//sydney.avancer();

      /*  if(sydney.node != NULL){
            if(cam.ActiveId == cam.IdFps)
                sydney.turnright(cam.camFPS->getRotation());
            cam.updateFPScam(sydney.node);
            cam.updateTPSCam(sydney.node);
        }*/
		
        int fps = driver->getFPS();
        if (lastFPS != fps)
        {
            core::stringw tmp(L"GAME - Irrlicht Engine [");
            tmp += driver->getName();
            tmp += L"] fps: ";
            tmp += fps;
            

            device->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
	}

	
	device->drop();

	return 0;
}
