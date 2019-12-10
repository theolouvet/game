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
Heros sydney2;
MyEventReceiver receiver;
Camera cam;
Camera cam2;
irr::SKeyMap keyMap[5];
ICameraSceneNode* camfree;
vector3df ligth;
std::chrono::time_point<std::chrono::system_clock> start, end;
scene::ISceneNode* skydome;
terrainscene terrain ;
mascene* drawscene;
quake q;
std::map<int,std::pair<mascene*,bool>> scenes;


float alphaw = 1.0;
const static int qId = 102;
const static int tId = 201;
float t;

void switchScenes();

//Gestion des shaders
class MyShaderCallBack2 : public video::IShaderConstantSetCallBack
{
public:
    
    //Appeler a chaque refresh de la scene
    virtual void OnSetConstants(video::IMaterialRendererServices* services,
                s32 userData){

            video::IVideoDriver* driver = services->getVideoDriver();
            
            //passage matrice de projection -> shader
            core::matrix4 worldViewProj;
            worldViewProj = driver->getTransform(video::ETS_PROJECTION);
            worldViewProj *= driver->getTransform(video::ETS_VIEW);
            worldViewProj *= driver->getTransform(video::ETS_WORLD);
            services->setVertexShaderConstant("mWorldViewProj", worldViewProj.pointer(), 16);
        
            //passage du vecteur lumière et position de la caméra
            skydome = terrain.skydome;
            core::vector3df pos = device->getSceneManager()->
                getActiveCamera()->getAbsolutePosition();
           // ligth.rotateXZBy(skydome->getRotation().Y/180);
            services->setVertexShaderConstant("mLightPos", reinterpret_cast<f32*>(&ligth), 3);
            services->setVertexShaderConstant("mCamPos", reinterpret_cast<f32*>(&pos), 3);

            //Passage de alpha pour gérer la transparence suivant 
            //la distance entre la quad et la caméra
            //fragment pour repeter plusieurs fois la texture sur le quad lorsque 
            //l observateur est proche de ce dernier
            float fragment = terrain.fragment;
            alphaw = terrain.alphaw;
            services->setVertexShaderConstant("fragmentation",&fragment, 1);
            services->setVertexShaderConstant("alpha",&alphaw, 1);
        
            //Passage du temps
            t= terrain.gettime();
            services->setVertexShaderConstant("Time",&t, 1);

            //Initialisation des textures (seulement deux sont utlisees)
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
        //cam.switchView();
        drawscene->camq->switchView();
    }
    sydney.keyreception(&receiver);	
    sydney2.keyreception(&receiver);        
        
        if(receiver.IsKeyDown(KEY_KEY_W)){
            device->drop();
        }

         if(receiver.IsKeyDown(KEY_KEY_L)){
            switchScenes();
        }

        if(receiver.IsKeyDown(KEY_KEY_N)){
            vector3df p = drawscene->smgr->getActiveCamera()->getPosition();
            std::cout<<"X "<<p.X<<" y "<<p.Y<<" z "<<p.Z<<std::endl;
        }

         if(receiver.IsKeyDown(KEY_KEY_F)){
            drawscene->switchFreecam();
        }
    

}

/*
Pour chaque scene on cree un nouveau scene manager 
*/

//Initialisation d'une scene (map de counter strike)
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
    //q.freecamera(); //utiliser lors du developpement
}

//Initialialisation d une scene (terrain)
void initiateTerrain(bool active){
    
    terrain = terrainscene(device, &mc);
    terrain.addHeros(&sydney2);
    terrain.initiateHeros();
    cam2 = Camera(terrain.smgr);
    cam2.initiateFPScam(sydney2.node);
    cam2.initiateTPScam(sydney2.node);
    terrain.setCam(&cam2);
    ligth = terrain.getligth();
    scenes.insert(std::make_pair(tId,std::make_pair(&terrain,active)));
}

//Initialisation de toutes les scenes
void initiateScenes(){
    
    initiateQuakeScene(true);
    initiateTerrain(false);
    for(auto it = scenes.begin(); it != scenes.end(); ++it){
        if(it->second.second){
            device -> setInputReceivingSceneManager(it->second.first->smgr);
            drawscene = it->second.first;
        }
    }
}

//Changement de scene 
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

     drawscene->setActiveCamera();

}


//Initialisation d une camera libre pour survoler le terrain
void camfreeInitialisation(){
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
}

//Initialisation du Héros
void InitialisationHeros(){
    sydney = Heros();
    sydney.setMesh(smgr ->getMesh("media/sydney.md2")); 
	sydney.setDevice(device);
    sydney2 = Heros();
    sydney2.setMesh(smgr ->getMesh("media/sydney.md2")); 
	sydney2.setDevice(device);
}

//initialisation
void Init(){
    device =
		createDevice( video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, &receiver);
	if (!device)
		exit(0);
	device->setWindowCaption(L"game");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
 
    
    InitialisationHeros();

	camfreeInitialisation();
    
    initiateScenes();   

  
	
}

int main()
{
    	
	
   
    Init();
    
    int lastFPS = -1;
	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));
        drawscene->draw();
        keyreception();
		driver->endScene();
        
		
        int fps = driver->getFPS();
        if (lastFPS != fps)
        {
            core::stringw tmp(L"GAME - ");
            tmp += L" fps: ";
            tmp += fps;
            device->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
	}

	
	device->drop();

	return 0;
}
