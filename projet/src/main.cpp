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
bool keyrelease = true;

void keyreception(){
    
  
    if(receiver.IsKeyDown(KEY_KEY_P) ){
        keyrelease =! keyrelease;
        cam.switchView();
    }
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
        if((receiver.IsKeyDown(KEY_KEY_A) ||
           receiver.IsKeyDown(KEY_KEY_Z) ||
           receiver.IsKeyDown(KEY_KEY_E) ||
           receiver.IsKeyDown(KEY_KEY_S)) && cam.ActiveId != cam.IdFps){ 
            sydney.run();
        }else
        {
            sydney.stand();
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


     /*terraingen terrain = terraingen(smgr);
    terrain.initTexture(driver->getTexture("media/terrain-texture.jpg"),  driver->getTexture("media/detailmap3.jpg"));
    terrain.setTerrainSelector(smgr->createTerrainTriangleSelector(terrain.terrain, 0));
    terrain.createAnimator(smgr, cam.cam);
*/

    // add terrain scene node
    scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
        "media/terrain-heightmap.bmp",
        0,                  // parent node
        -1,                 // node id
        core::vector3df(0.f,-550.f, 0.f),     // position
        core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df(40.f, 4.4f, 40.f),  // scale
        video::SColor ( 255, 255, 255, 255 ),   // vertexColor
        5,                  // maxLOD
        scene::ETPS_17,             // patchSize
        4                   // smoothFactor
        );

    terrain->setMaterialFlag(video::EMF_LIGHTING, false);

    terrain->setMaterialTexture(0,
            driver->getTexture("media/terrain-texture.jpg"));
    terrain->setMaterialTexture(1,
            driver->getTexture("media/detailmap3.jpg"));

    terrain->setMaterialType(video::EMT_DETAIL_MAP);

    terrain->scaleTexture(1.0f, 20.0f);

    // create triangle selector for the terrain
       scene::ITriangleSelector* selector
           = smgr->createTerrainTriangleSelector(terrain, 0);
       terrain->setTriangleSelector(selector);

       // create collision response animator and attach it to the camera
       scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
           selector, cam.cam, core::vector3df(60,100,60),
           core::vector3df(0,0,0),
           core::vector3df(0,50,0));
       selector->drop();
       cam.cam->addAnimator(anim);
       anim->drop();
       scene::CDynamicMeshBuffer* buffer = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_16BIT);
       terrain->getMeshBufferForLOD(*buffer, 0);
       video::S3DVertex2TCoords* data = (video::S3DVertex2TCoords*)buffer->getVertexBuffer().getData();
       // Work on data or get the IndexBuffer with a similar call.
       buffer->drop(); // When done drop the buffer again.
       // create skybox and skydome
       driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

       scene::ISceneNode* skybox=smgr->addSkyBoxSceneNode(
           driver->getTexture("media/irrlicht2_up.jpg"),
           driver->getTexture("media/irrlicht2_dn.jpg"),
           driver->getTexture("media/irrlicht2_lf.jpg"),
           driver->getTexture("media/irrlicht2_rt.jpg"),
           driver->getTexture("media/irrlicht2_ft.jpg"),
           driver->getTexture("media/irrlicht2_bk.jpg"));
       scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("media/skydome.jpg"),16,8,0.95f,2.0f);

       driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

        sydney.addcolision(selector, smgr);


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



