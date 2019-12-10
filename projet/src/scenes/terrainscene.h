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
  
    ic::vector3df initposHeros = ic::vector3df(4332,1171,-2837);
    ic::vector3df posPortail = ic::vector3df( 4608.09 , 1120.32 , -2720.68);
    IrrlichtDevice *device;
    vector3df ligth = vector3df(-5000,5000,14000);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    myterrain* ter;
    scene::IBillboardSceneNode* bill;
    float t;
    
    
    
public:
    terrainscene():mascene(){};
    is::IMetaTriangleSelector* metaselector;
    is::ITriangleSelector* selector;
    terrainscene(IrrlichtDevice *,IShaderConstantSetCallBack*);
    void initiateHeros();
    void draw() override;
    vector3df getligth() {return ligth;};
    float gettime(){return t;};
    scene::ISceneNode* skydome;
    float fragment = 1.0f;
    float alphaw = 1.0;
};



#endif