#ifndef HEROS_H
#define HEROS_H

#include "personnages.h"
#include<irrlicht/irrlicht.h>
#include"../myeventreceiver.h"

class Heros: public Personnages
{
public:
    Heros();
    void loadTexture(irr::video::ITexture *);
    
    void avancer();
    void saut();
    void reculer();
    void turnright();
    void turnleft();
    void turnright(ic::vector3df);
    void turnleft(ic::vector3df);
    void animation(bool);
    void add_animator(irr::scene::ISceneNodeAnimatorCollisionResponse*);
    void shoot();
    void keyreception(MyEventReceiver*, int);
    void setMapSelector(is::IMetaTriangleSelector* metaselector);
    void setDevice(irr::IrrlichtDevice* dev);
    irr::scene::ISceneNodeAnimatorCollisionResponse* anim;
    bool isjump = false;
    struct SParticleImpact
	{
		irr::u32 when;
		ic::vector3df pos;
		ic::vector3df outVector;
	};

private:
    const static int isRunning = 0;
    const static int isJumping = 0;
    const static int isStanding = 1;
    irr::core::position2di mousePostion;
    is::IMetaTriangleSelector* ms;
    irr::IrrlichtDevice* device;
    void initJump();
    ic::vector3df posinit;
    float djump = 30;
    ic::vector3df posf;
    float dt;
    irr::core::vector3df force = ic::vector3df(0,50,0);
    ic::array<SParticleImpact> Impacts;
   
};

#endif // HEROS_H
