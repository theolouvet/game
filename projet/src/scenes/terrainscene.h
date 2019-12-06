#ifndef TERRAINSCENE_H
#define TERRAINSCENE_H

#include "mascene.h"
#include"../camera/camera.h"
#include"../map/myterrain.h"
#include"../map/waterquad.h"
#include<chrono>

class terrainscene : public mascene
{
private:
    /* data */
  
    irr::SKeyMap keyMap[5];
    ICameraSceneNode* camfree;
    IrrlichtDevice *device;
    vector3df ligth = vector3df(-5000,5000,14000);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    
    
    float t;
    
    
    
public:
    terrainscene():mascene(){};
    terrainscene(IrrlichtDevice *,IShaderConstantSetCallBack*);
    void draw() override;
    vector3df getligth() {return ligth;};
    float gettime(){return t;};
    scene::ISceneNode* skydome;
    float test = 1.0f;
    float alphaw = 1.0;
};



#endif