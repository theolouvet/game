#ifndef PERSONNAGES_H
#define PERSONNAGES_H

//#include<irrlicht.h>
#include<irrlicht/irrlicht.h>
#include<math.h>
#include <iostream>
namespace ic = irr::core ;
namespace is = irr::scene;




class Personnages
{
public:
    Personnages();
    ic::vector3df getPosition();
    ic::vector3df getRotation();
    void run();
    void stand();
    is::IAnimatedMeshSceneNode* node;
    int state = is::EMAT_STAND;
    void addcolision(is::ITriangleSelector*, is::ISceneManager*);
    
private:
    int pdv;


};

#endif // PERSONNAGES_H
