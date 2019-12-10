#include"mascene.h"
#include "../entites/heros.h"

mascene::mascene(IrrlichtDevice *device){
   // smgr = device->getSceneManager();
   smgr = device ->getSceneManager()->createNewSceneManager(false);
   initiateFreecam();
}

void mascene::draw(){
    smgr->drawAll();    
}

void mascene::addHeros(Heros* h){
    heros = h;
}

void mascene::setActiveCamera(ICameraSceneNode* activeCam){
    activeCamera = activeCam;
    setActiveCamera();
}

void mascene::setActiveCamera(){
    smgr->setActiveCamera(activeCamera);
}

void mascene::setCam(Camera* cam){
   camq = cam;
   cam->initiateFPScam(heros->node);
   cam->initiateTPScam(heros->node); 
   setActiveCamera(cam->cam);
}

ICameraSceneNode* mascene::getActiveCamera(){
    return activeCamera;
}

void mascene::switchFreecam(){
    if(useFreeCam)
        setActiveCamera(camq->cam);
    else
        setActiveCamera(camfree);
    useFreeCam != useFreeCam;
}

bool mascene::portalUsed(){
    return inPortal;
}

void mascene::initiateFreecam(){
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
    camfree->setName("free camera terrain");
}