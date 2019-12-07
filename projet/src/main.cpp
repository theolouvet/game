#include<irrlicht/irrlicht.h>
#include <iostream>
#include "myeventreceiver.h"
#include "scenes/quake.h"
#include "entites/heros.h"
#include "camera/camera.h"
#include "scenes/terrainscene.h"
#include <map>
#include <chrono>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

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
vector3df ligth;
std::chrono::time_point<std::chrono::system_clock> start, end;
float test = 1.0f;
float alphaw = 1.0;

const static int qId = 102;
const static int tId = 201;

float t;

scene::ISceneNode* skydome;
terrainscene terrain ;
mascene* drawscene;
quake q;
std::map<int,std::pair<mascene*,bool>> scenes;

void switchScenes();

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
            skydome = terrain.skydome;
            core::vector3df pos = device->getSceneManager()->
                getActiveCamera()->getAbsolutePosition();
           // ligth.rotateXZBy(skydome->getRotation().Y/180);
            services->setVertexShaderConstant("mLightPos", reinterpret_cast<f32*>(&ligth), 3);
            services->setVertexShaderConstant("mCamPos", reinterpret_cast<f32*>(&pos), 3);

            test = terrain.test;
            alphaw = terrain.alphaw;
            services->setVertexShaderConstant("romain",&test, 1);
            services->setVertexShaderConstant("alpha",&alphaw, 1);
        
           
            core::matrix4 world = driver->getTransform(video::ETS_WORLD);
            world = world.getTransposed();
            services->setVertexShaderConstant("mTransWorld", world.pointer(), 16);
            t= terrain.gettime();
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
   

private:
    
};

MyShaderCallBack2 mc;

void keyreception(){
    
    

    if(receiver.IsKeyDown(KEY_KEY_P) ){
        keyrelease =! keyrelease;
        cam.switchView();
    }
    sydney.keyreception(&receiver);	
 /*       if(receiver.IsKeyDown(KEY_KEY_Z)){
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
        if(receiver.IsKeyDown(KEY_SPACE)){

        }
        if((receiver.IsKeyDown(KEY_KEY_A) ||
           receiver.IsKeyDown(KEY_KEY_Z) ||
           receiver.IsKeyDown(KEY_KEY_E) ||
           receiver.IsKeyDown(KEY_KEY_S)) && cam.ActiveId != cam.IdFps){ 
            sydney.run();
        }else
        {
            sydney.stand();
        }*/
        
        
        if(receiver.IsKeyDown(KEY_KEY_W)){
            device->drop();
        }

         if(receiver.IsKeyDown(KEY_KEY_L)){
            switchScenes();
        }

        if(receiver.IsKeyDown(KEY_KEY_N)){
            vector3df p = sydney.getPosition();
            std::cout<<"X "<<p.X<<" y "<<p.Y<<" z "<<p.Z<<std::endl;
        }
    

}

void initiateQuakeScene(bool active){
    q = quake(device);   
	q.addHeros(&sydney); 
	q.initiatedHeros();
    cam = Camera(q.smgr);
    cam.initiateFPScam(sydney.node);
    cam.initiateTPScam(sydney.node);
    q.setCam(&cam);
    scenes.insert(std::make_pair(qId, std::make_pair(&q,active)));
    sydney.loadTexture(driver->getTexture("media/sydney.bmp"));
}

void initiateTerrain(bool active){
    
    terrain = terrainscene(device, &mc);
    ligth = terrain.getligth();
    scenes.insert(std::make_pair(tId,std::make_pair(&terrain,active)));
}

void initiateScenes(){
    std::cout<<"brhnegzbprogrhepgprezhog"<<std::endl;
    initiateTerrain(false);
    std::cout<<"brhnegzbprogrhepgprezhog fin terrain"<<std::endl;
    initiateQuakeScene(true);
    std::cout<<"brhnegzbprogrhepgprezhog fin quake"<<std::endl;
    for(auto it = scenes.begin(); it != scenes.end(); ++it){
        if(it->second.second){
            device -> setInputReceivingSceneManager(it->second.first->smgr);
            drawscene = it->second.first;
        }
    }
}

void switchScenes(){
        bool b = false;
       for(auto it = scenes.begin(); it != scenes.end(); ++it){
        if(!it->second.second && !b){
            device->sleep(1000);
            device -> setInputReceivingSceneManager(it->second.first->smgr);
            drawscene = it->second.first;
            it->second.second = true;
            b = true;
        }else{
            it->second.second = false;
        }
    }
     for(auto it = scenes.begin(); it != scenes.end(); ++it){
         std::cout<<"scenes: "<<it->first<<" etat "<<it->second.second<<std::endl;
     }

}

int main()
{
	
	
	device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, &receiver);
	if (!device)
		return 1;
    std::cout<<"brhnegzbprogrhepgprezhog"<<std::endl;
	device->setWindowCaption(L"game");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
 
    sydney = Heros();
    IAnimatedMesh* heros_mesh = smgr ->getMesh("media/sydney.md2"); 
	
   std::cout<<"brhnegzbprogrhepgprezhog"<<std::endl;

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
    std::cout<<"brhnegzbprogrhepgprezhog"<<std::endl;
    initiateScenes();   

    sydney.anim->setGravity(vector3df(0,-10,0));
	int lastFPS = -1;
    std::cout<<"brhnegzbprogrhepgprezhog"<<std::endl;
    std::cout<<"tess   "<<std::endl;
    std::cout<<"tess   "<< sydney.anim->collisionOccurred()<<std::endl;
    sydney.anim->collisionOccurred();
    std::setvbuf(stdout, NULL, _IONBF, 0);
    int testtins = 0;
	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));
        drawscene->draw();

        keyreception();

       
      
        

		driver->endScene();
        
		
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
