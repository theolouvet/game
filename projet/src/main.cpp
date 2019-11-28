//#include <irrlicht.h>
#include<irrlicht/irrlicht.h>
#include <iostream>
#include"heros.h"
#include "camera.h"
#include "myeventreceiver.h"



using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

ISceneManager* smgr ;
IrrlichtDevice *device;
Camera cam;
MyEventReceiver receiver;
irr::SKeyMap keyMap[5];
Heros sydney;
bool ani = false;
bool keyrelease = true;
bool freecam = false;

void keyreception(){
    
  
    if(receiver.IsKeyDown(KEY_KEY_P) && !freecam ){
        keyrelease =! keyrelease;
        cam.switchView();
    }
    else if(!freecam){
        if(receiver.IsKeyDown(KEY_KEY_Z)){
            sydney.avancer();
            cam.updateCamera(&sydney);
            ani = true;
        }else if(receiver.IsKeyDown(KEY_KEY_S)){
            sydney.reculer();
            cam.updateCamera(&sydney);
            ani = true;
        }if(receiver.IsKeyDown(KEY_KEY_E) && cam.ActiveId != cam.IdFps){
            sydney.turnleft();
            cam.updateCamera(&sydney);
            ani = true;
        }if(receiver.IsKeyDown(KEY_KEY_A)  && cam.ActiveId != cam.IdFps ){
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

        if(receiver.IsKeyDown(KEY_KEY_M) && !freecam){
            freecam = true;
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
            ICameraSceneNode* camfree =  smgr->addCameraSceneNodeFPS(
                    0,
            100,
            10.0f,
            -1,
            0,//keymap
            5
            );
            camfree->setFarValue(30000.0f);
        }
        
        
    }

    
    
    

}



int main(){


    video::E_DRIVER_TYPE driverType= video::EDT_OPENGL ;
    if (driverType==video::EDT_COUNT)
        return 1;
    device = createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
                           false, false, false, &receiver);
    if (!device)
        return 1;
    device->setWindowCaption(L"Game");


    IVideoDriver* driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    IGUIEnvironment* guienv = device->getGUIEnvironment();

    sydney = Heros();
    IAnimatedMesh* sydney_mesh = smgr ->getMesh("media/sydney.md2");
    sydney.node = smgr->addAnimatedMeshSceneNode(sydney_mesh);
    sydney.loadTexture(driver->getTexture("media/sydney.bmp"));
    
    cam = Camera(smgr);
    cam.initiateFPScam(sydney.node);
    cam.initiateTPScam(sydney.node);
  //  cam.initiateMayacam(sydney.node);
    cam.switchcamtype(cam.IdFps);
    
 
    vector3df r = sydney.getRotation();
    vector3df p = sydney.getPosition();
    std::cout<<"rotation"<<r.X<<" "<<r.Y<<" "<<r.Z<<std::endl;
    r = sydney.getRotation().rotationToDirection();
    std::cout<<"rotation"<<r.X<<" "<<r.Y<<" "<<r.Z;
    
    device->getCursorControl()->setVisible(false);

    cam.cam->setParent(sydney.node);


   

    int lastFPS = -1;
    
    while(device->run())
    {
        driver->beginScene(true, true, video::SColor(255,200,200,200));
        smgr->drawAll();
        driver->endScene();
        int fps = driver->getFPS();
        p += vector3df(0.1,0,0);
        //sydney.node->setPosition(p);
        r +=  vector3df(0,0.1,0);
        //sydney.node->setRotation(r);
        if(cam.ActiveId == cam.IdFps)
            sydney.turnright(cam.camFPS->getRotation());
        cam.updateFPScam(sydney.node);
        keyreception();
        cam.updateTPSCam(sydney.node);
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



