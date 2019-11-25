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
Heros sydney;
bool ani = false;

void keyreception(){
    ani = false;
    if(receiver.IsKeyDown(KEY_KEY_P))
        cam.switchView();
    else{
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
    }

    if(ani){
        //TO DO animate_sydney
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
    cam.initiateMayacam(sydney.node);
    cam.switchcamtype(cam.IdFps);
    
 
    vector3df r = sydney.getRotation();
    vector3df p = sydney.getPosition();
    std::cout<<"rotation"<<r.X<<" "<<r.Y<<" "<<r.Z<<std::endl;
    r = sydney.getRotation().rotationToDirection();
    std::cout<<"rotation"<<r.X<<" "<<r.Y<<" "<<r.Z;
    
    device->getCursorControl()->setVisible(false);

    cam.cam->setParent(sydney.node);


       device->getFileSystem()->addFileArchive("media/map-20kdm2.pk3");

       device->maximizeWindow();


       //smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));
       scene::IAnimatedMesh* mesh_map = smgr->getMesh("20kdm2.bsp");
           scene::ISceneNode* node_map = 0;

           if (mesh_map)
               node_map = smgr->addOctreeSceneNode(mesh_map->getMesh(0), 0, -1, 128);

           if (node_map)
               node_map->setPosition(core::vector3df(-1300,-144,-1249));


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



