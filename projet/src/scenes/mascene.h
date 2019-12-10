#ifndef SCENE_H
#define SCENE_H

#include<irrlicht/irrlicht.h>
#include"../entites/heros.h"
#include"../camera/camera.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class mascene
{
private:
    /* data */
    ICameraSceneNode* activeCamera;
    
public:
    mascene(){};
    mascene(IrrlichtDevice *);
    virtual void draw();
    void setCam(Camera*);
    void addHeros(Heros*);
    void setActiveCamera(ICameraSceneNode*);
    void setActiveCamera();
    void initiateFreecam();
    void switchFreecam();
    bool useFreeCam = false;
    irr::SKeyMap keyMap[5];
    ICameraSceneNode* camfree;
    is::ICameraSceneNode* getActiveCamera();
    Heros* heros;
    ISceneManager* smgr ;
    IrrlichtDevice *dev;
     Camera* camq;
    enum
{
    
    ID_IsNotPickable = 0,

    
    IDFlag_IsPickable = 1 << 0,


    IDFlag_IsHighlightable = 1 << 1
};


};

#endif


