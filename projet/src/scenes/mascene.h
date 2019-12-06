#ifndef SCENE_H
#define SCENE_H

#include<irrlicht/irrlicht.h>
#include"../entites/heros.h"
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

    
public:
    mascene(){};
    mascene(IrrlichtDevice *);
    virtual void draw();
    void addHeros(Heros*);

    Heros* heros;
    ISceneManager* smgr ;
    IrrlichtDevice *dev;
    enum
{
    
    ID_IsNotPickable = 0,

    
    IDFlag_IsPickable = 1 << 0,


    IDFlag_IsHighlightable = 1 << 1
};


};

#endif


