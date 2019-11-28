//#include <irrlicht.h>
#include<irrlicht/irrlicht.h>
#include <iostream>
#include"heros.h"
#include "camera.h"
#include "myeventreceiver.h"
#include "map/myterrain.h"
#include "map/waterquad.h"
#include <chrono>

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
std::chrono::time_point<std::chrono::system_clock> start, end;
bool ani = false;
bool keyrelease = true;
bool freecam = false;
float t;
scene::ISceneNode* skydome;
core::vector3df ligth = vector3df(-5000,5000,14000);




class MyShaderCallBack2 : public video::IShaderConstantSetCallBack
{
public:
    
    virtual void OnSetConstants(video::IMaterialRendererServices* services,
                s32 userData){
                    video::IVideoDriver* driver = services->getVideoDriver();
            core::matrix4 invWorld = driver->getTransform(video::ETS_WORLD);
            invWorld.makeInverse();
            services->setVertexShaderConstant("mInvWorld", invWorld.pointer(), 16);
            
            core::matrix4 worldViewProj;
            worldViewProj = driver->getTransform(video::ETS_PROJECTION);
            worldViewProj *= driver->getTransform(video::ETS_VIEW);
            worldViewProj *= driver->getTransform(video::ETS_WORLD);
            services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);
        
            // set camera position

            core::vector3df pos = device->getSceneManager()->
                getActiveCamera()->getAbsolutePosition();
            ligth.rotateXZBy(skydome->getRotation().Y/180);
            services->setVertexShaderConstant("mLightPos", reinterpret_cast<f32*>(&ligth), 3);
            services->setVertexShaderConstant("mCamPos", reinterpret_cast<f32*>(&pos), 3);
        
           
            core::matrix4 world = driver->getTransform(video::ETS_WORLD);
            world = world.getTransposed();
            services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);

            services->setVertexShaderConstant("Time",&t, 1);


            s32 TextureLayerID = 0;
            s32 TextureLayerID1 = 1;
            s32 TextureLayerID2 = 2;
            s32 TextureLayerID3 = 3;    
            services->setPixelShaderConstant("myTexture", &TextureLayerID, 1);
            services->setPixelShaderConstant("myTexture2", &TextureLayerID1, 1);
            services->setPixelShaderConstant("myTexture3", &TextureLayerID2, 1);
            services->setPixelShaderConstant("myTexture4", &TextureLayerID3, 1);
                };
   /* void add(const c8* name, const f32* floats, int count){
        std::vector<const f32*, int> v;
        v.push_back(floats);
        v.push_back(count);
    };*/

private:
    
};













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

    MyShaderCallBack2 mc;

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

    //terrain creation
    const io::path& heightMapFileName = "data/dataterrain/hm2.jpg";
    const io::path& TextureFileName = "data/dataterrain/terrain-texture.jpg";
    io::path vsFileName = "data/dataterrain/terrain.vert"; // filename for the vertex shader
    io::path psFileName = "data/dataterrain/terrain.frag"; // filename for the pixel shader
    myterrain ter = myterrain();
    ter.terrainHM(smgr, heightMapFileName);
    ter.setMaterialFlag(video::EMF_LIGHTING, false);
    ter.setMaterialTexture(0, driver->getTexture(TextureFileName));
    ter.myShaders(vsFileName, psFileName, driver->getGPUProgrammingServices(), &mc);
    ter.addskybox(smgr, driver);
    skydome = ter.skydome;

    //quad creation
    const io::path& vsquad = "data/datawater/vtest.vert";
    const io::path& fsquad = "data/datawater/ftest.frag";
    waterquad water = waterquad(smgr, driver,
        dimension2df(800,800), dimension2du(25,25));
    water.myShaders(vsquad, fsquad, driver->getGPUProgrammingServices(), &mc);
   
    mc.drop();

    int lastFPS = -1;
    start = std::chrono::system_clock::now();
    
    while(device->run())
    {
        driver->beginScene(true, true, video::SColor(255,200,200,200));
        smgr->drawAll();
        driver->endScene();
        int fps = driver->getFPS();
        end = std::chrono::system_clock::now();
        t = std::chrono::duration_cast<std::chrono::duration<float>>(start - end).count();
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



