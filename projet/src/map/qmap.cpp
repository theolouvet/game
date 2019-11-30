#include"qmap.h"

qmap::qmap(){}

qmap::qmap(ISceneManager* smgr, IrrlichtDevice* device){
    device->getFileSystem()->addFileArchive("data/dataMAP/map-20kdm2.pk3");
    mesh = smgr->getMesh("20kdm2.bsp");
    node = 0;

    if (mesh)
        node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
//      node = smgr->addMeshSceneNode(mesh->getMesh(0));
    if (node)
        node->setPosition(core::vector3df(0,4500,0));
    smgr->addCameraSceneNodeFPS();
}

void qmap::createTriangleSelector(){
selector  = node ->getSceneManager()->createOctreeTriangleSelector(mesh, node, 128);
node->setTriangleSelector(selector);
    node->setTriangleSelector(selector);
    node->setMaterialType(EMT_SOLID);
    //node->setMaterialFlag(EMF_LIGHTING, true);
}