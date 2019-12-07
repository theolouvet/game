#include "heros.h"

#include <iostream>
Heros::Heros()
{

}

void Heros::loadTexture(irr::video::ITexture *texture){
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setMD2Animation(irr::scene::EMAT_STAND);
    node->setMaterialTexture( 0, texture);
}

void Heros::saut(){
   if(state != is::EMAT_JUMP){
        state = is::EMAT_JUMP;
        node->setMD2Animation( is::EMAT_JUMP);
    }
}



void Heros::avancer(){
    ic::vector3df pos = getPosition();
    ic::vector3df rot = getRotation();
    ic::vector3df mvt = ic::vector3df(0,0,0);
    mvt.X +=  cos(2.0f * M_PI * rot.Y/360);
    mvt.Z -=  sin(2.0f * M_PI * rot.Y/360);
    node->setPosition(pos + mvt);
}

void Heros::reculer(){
    ic::vector3df pos = getPosition();
    ic::vector3df rot = getRotation();
    ic::vector3df mvt = ic::vector3df(0,0,0);
    mvt.X +=  cos(2.0f * M_PI * rot.Y/360);
    mvt.Z -=  sin(2.0f * M_PI * rot.Y/360);
    node->setPosition(pos - mvt);
}

void Heros::turnleft(){
    ic::vector3df pos = getRotation();
    pos.Y -= 1;
    node->setRotation(pos);
}

void Heros::turnright(){
    ic::vector3df pos = getRotation();
    pos.Y += 1;
    node->setRotation(pos);
}

void Heros::turnleft(ic::vector3df rot){;
    node->setRotation(rot);
}

void Heros::turnright(ic::vector3df rot){
    node->setRotation(ic::vector3df(0,rot.Y - 90,0));
}

void Heros::keyreception(MyEventReceiver* receiver){

        if(receiver->IsKeyDown(irr::KEY_KEY_Z)){
                avancer();
                irr::scene::ISceneNodeAnimatorList A = node->getAnimators(); 
        }else if(receiver->IsKeyDown(irr::KEY_KEY_S)){
                reculer();
        }if(receiver->IsKeyDown(irr::KEY_KEY_A)){
                turnleft();
        }if(receiver->IsKeyDown(irr::KEY_KEY_E)){
                turnright();
        }
        if(anim->isFalling()){
            saut();
        }else if((receiver->IsKeyDown(irr::KEY_KEY_A) ||
           receiver->IsKeyDown(irr::KEY_KEY_Z) ||
           receiver->IsKeyDown(irr::KEY_KEY_E) ||
           receiver->IsKeyDown(irr::KEY_KEY_S))){ 
            run();
        }else
        {
            stand();
        }

         if(receiver->IsKeyDown(irr::KEY_SPACE) && !anim->isFalling()){
           
           isjump = true;
           anim->jump(4);
        }
        
}

void Heros::add_animator(irr::scene::ISceneNodeAnimatorCollisionResponse* a){
    anim = a;
    node->addAnimator(anim);
}

void Heros::initJump(){
    posinit = getPosition();
    posf = posinit;
    posf.Y += djump;
    dt = 0.1;
    isjump = true;
}





