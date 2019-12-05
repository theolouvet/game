#ifndef SCENE_H
#define SCENE_H

#include<irrlicht/irrlicht.h>
#include"heros.h"
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
    mascene(IrrlichtDevice *);
    void draw();
    void addHeros(Heros*);

    Heros* heros;
    ISceneManager* smgr ;
    IrrlichtDevice *dev;
    enum
{
    // I use this ISceneNode ID to indicate a scene node that is
    // not pickable by getSceneNodeAndCollisionPointFromRay()
    ID_IsNotPickable = 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be picked by ray selection.
    IDFlag_IsPickable = 1 << 0,

    // I use this flag in ISceneNode IDs to indicate that the
    // scene node can be highlighted.  In this example, the
    // homonids can be highlighted, but the level mesh can't.
    IDFlag_IsHighlightable = 1 << 1
};


};

#endif


