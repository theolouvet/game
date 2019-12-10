#ifndef QUAKE
#define QUAKE

#include<irrlicht/irrlicht.h>
#include"mascene.h"
#include"../camera/camera.h"
#include<chrono>

class quake : public mascene
{
private:
    /* data */
    std::chrono::time_point<std::chrono::system_clock> start, end;
    float dt = -1;
    IMetaTriangleSelector* metaselector;
    scene::IBillboardSceneNode* bill;

public:
    quake():mascene(){};
    bool portalUsed();
    quake(IrrlichtDevice *);
    void initiatedHeros();
    void draw() override;
    void freecamera();
    const static int qId = 102;
};

#endif


