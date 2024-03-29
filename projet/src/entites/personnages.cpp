#include "personnages.h"

Personnages::Personnages()
{

}

ic::vector3df Personnages::getPosition(){
    return node->getPosition();
}

ic::vector3df Personnages::getRotation(){
    return node->getRotation();
}

void Personnages::run(){
    if(state != is::EMAT_RUN){
        state = is::EMAT_RUN;
        node->setMD2Animation( is::EMAT_RUN);
    }
}

void Personnages::stand(){
    if(state != is::EMAT_STAND){
        state = is::EMAT_STAND;
        node->setMD2Animation( is::EMAT_STAND);
    }
}

void Personnages::addcolision(is::ITriangleSelector* selector, is::ISceneManager* smgr){
    auto m_collision = smgr->createCollisionResponseAnimator(
                selector, node, ic::vector3df(30,30,30),
                ic::vector3df(0,-10,0),ic::vector3df(0,30,0));
    node->addAnimator(m_collision);
    selector->drop();
    m_collision->drop();
}

void Personnages::setMesh(is::IAnimatedMesh* m){
    mesh = m;
}

is::IAnimatedMesh* Personnages::getMesh(){
    return mesh;
}
