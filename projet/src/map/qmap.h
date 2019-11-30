#ifndef QMAP
#define QMAP
#include<irrlicht/irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class qmap
{
private:
    /* data */
   
public:
    qmap(/* args */);
    qmap(ISceneManager* smgr, IrrlichtDevice* device);
    scene::ISceneNode* node;
    void createTriangleSelector();
    ITriangleSelector* selector = 0;
     scene::IAnimatedMesh* mesh;
};

#endif