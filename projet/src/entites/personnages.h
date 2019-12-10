#ifndef PERSONNAGES_H
#define PERSONNAGES_H

//#include<irrlicht.h>
#include<irrlicht/irrlicht.h>
#include<math.h>
#include <iostream>
namespace ic = irr::core ;
namespace is = irr::scene;
namespace iv = irr::video;




class Personnages
{
public:
    Personnages();
    ic::vector3df getPosition();
    ic::vector3df getRotation();
    void setMesh(is::IAnimatedMesh*);
    is::IAnimatedMesh* getMesh();
    void run();
    void stand();
    is::IAnimatedMeshSceneNode* node;
    int state = is::EMAT_STAND;
    void addcolision(is::ITriangleSelector*, is::ISceneManager*);
    
private:
    int pdv;
    is::IAnimatedMesh* mesh;


};

#endif // PERSONNAGES_H
