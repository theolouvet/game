#include "camera.h"
#include <iostream>



Camera::Camera(){}

Camera::Camera(ism::ISceneManager* smgr){
    camsmgr = smgr;
}

/*SceneManager::addCameraSceneNodeFPS (
 ISceneNode * parent,       // le noeud parent de la caméra
 f32 rotateSpeed,           // la vitesse de rotation de la caméra
 f32 moveSpeed,             // la vitesse de déplacement
 s32 id,                    // numéro d'identification du noeud
 SKeyMap * keyMapArray,     // une map permettant de re-affecter les touches
 s32 keyMapSize,            // taille de la keyMap
 bool noVerticalMovement,   // autorise ou non les mouvements sur l'axe vertical
 f32 jumpSpeed,             // vitesse de déplacement lors d'un saut
 bool invertMouse,          // inverse ou non la rotation de la caméra
 bool makeActive)           // indique si la caméra doit être active ou non*/

void Camera::initiateTPScam(is::IAnimatedMeshSceneNode* node){
    ic::vector3df pos = node->getPosition();
    pos += relatifPos;
    cam = camsmgr->addCameraSceneNode(0,pos, node->getPosition() + relatifTarget);
    camsmgr->setActiveCamera(cam);
    ActiveId = IdTps;
    TPS = true;
}

void Camera::initiateFPScam(is::IAnimatedMeshSceneNode* node){
    /*camFPS = camsmgr->addCameraSceneNodeFPS(node);
    camsmgr->setActiveCamera(camFPS);
    camFPS->setUpVector(ic::vector3df(0,1,0));*/
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
    camFPS = camsmgr->addCameraSceneNodeFPS(
        0,
        100,
        0.1,
        -1,
        0,//keymap
        5
    );
    ic::vector3df pos = node->getPosition();
    camFPS->setPosition(pos+ ic::vector3df(-1,25,0));
    camFPS->setTarget(pos);

    FPS = true;
    ActiveId = IdFps;
}

void Camera::initiateMayacam(is::IAnimatedMeshSceneNode* node){
    camMaya = camsmgr->addCameraSceneNodeMaya(node);
    
    camMaya->setTarget(node->getPosition());
    camsmgr->setActiveCamera(camMaya);
    ActiveId = IdMaya;
    MAYA = true;
}


void Camera::setPosition(bool FPS,ic::vector3df pos){
    if(FPS)
        camFPS->setPosition(pos);
    else
        cam->setPosition(pos);
}

void Camera::setTarget(bool FPS,ic::vector3df pos){
    if(FPS)
        camFPS -> setTarget(pos);
    else
        cam-> setTarget(pos);
}

void Camera::setRotation(bool FPS,ic::vector3df pos){
    if(FPS)
        camFPS -> setRotation(pos);
    else
        cam-> setRotation(pos);
}

void Camera::updateCamera(Heros* h){
    updateFPScam(h->node);
}

void Camera::switchcamtype(int type){
    if(type == IdFps)
        camsmgr->setActiveCamera(camFPS);
    else if(type == IdTps)
        camsmgr->setActiveCamera(cam);
    else
        camsmgr->setActiveCamera(camMaya);
    ActiveId = type;
}

void Camera::updateTPSCam(is::IAnimatedMeshSceneNode* node){
   cam->setTarget(node->getPosition());
}

void Camera::updateFPScam(is::IAnimatedMeshSceneNode* node){
    camFPS->setPosition(node->getPosition()+ ic::vector3df(-1.5,25,0));
}


void Camera::switchView(){
    std::cout<<0<<std::endl;
    if(FPS && TPS && MAYA){
        std::cout<<"initialiser une camera"<<std::endl;
    }else{
        switch (ActiveId)
            {
            case IdFps:
                std::cout<<MAYA<<std::endl;
                ActiveId = IdMaya;
                if(MAYA)
                    break;
            case IdMaya:
                std::cout<<0<<std::endl;
                ActiveId = IdTps;
                if(TPS)
                    break;
            case IdTps:
                std::cout<<0<<std::endl;
                ActiveId = IdFps;
                if(FPS)
                    break;
            default:
                std::cout<<"default"<<std::endl;
                break;
            }
        switchcamtype(ActiveId);
    }
}

ic::vector3df Camera::getPosition(){ return cam->getAbsolutePosition(); };

ic::vector3df Camera::getTarget(){ return cam->getTarget(); };