#ifndef CAMERA_H
#define CAMERA_H

#include<irrlicht/irrlicht.h>
#include "heros.h"

namespace ism = irr::scene;
namespace ic = irr::core;

class Camera
{
public:
    Camera();
    Camera(ism::ISceneManager*);

    void setPosition(bool,ic::vector3df);
    void setTarget(bool,ic::vector3df);
    void setRotation(bool,ic::vector3df);

    void updateCamera(Heros*);
    void switchcamtype(int);
    void initiateTPScam(is::IAnimatedMeshSceneNode*);
    void initiateFPScam(is::IAnimatedMeshSceneNode*);
    void initiateMayacam(is::IAnimatedMeshSceneNode*);
    void updateTPSCam(is::IAnimatedMeshSceneNode*);
    void updateFPScam(is::IAnimatedMeshSceneNode*);
    void switchView();

    ic::vector3df getPosition();
    ic::vector3df getTarget();  
    ism::ICameraSceneNode* cam;//TPS
    ism::ICameraSceneNode* camFPS;
    ism::ICameraSceneNode* camMaya;
    ism::ISceneManager* camsmgr;

    bool FPS = false;
    int ActiveId = -1;
    const static int IdFps = 0;
    const static int IdTps = 1;
    const static int IdMaya = 2;

    irr::SKeyMap keyMap[5];                    // re-assigne les commandes
    
    

private:
    ic::vector3df relatifPos = ic::vector3df(-25.0f,45.0f,0.0f);
    ic::vector3df relatifTarget = ic::vector3df(30.0f,0.0f,0.0f);
    

};

#endif 