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

void Heros::avancer(){
    ic::vector3df pos = getPosition();
    ic::vector3df rot = getRotation();
    ic::vector3df mvt = ic::vector3df(0,0,0);
    mvt.X +=  cos(2.0f * M_PI * rot.Y/360)/10;
    mvt.Z -=  sin(2.0f * M_PI * rot.Y/360)/10;
    node->setPosition(pos + mvt);
}

void Heros::reculer(){
    ic::vector3df pos = getPosition();
    ic::vector3df rot = getRotation();
    pos.X -= 1;
    pos.X = pos.X * cos(2.0f * M_PI * rot.Y/360);
    pos.Y = pos.Y * sin(2.0f * M_PI * rot.Y/360);
    node->setPosition(pos);
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



