#include"quake.h"
#include"../entites/heros.h"
#include"../camera/camera.h"

 scene::IMeshSceneNode* q3node ;
 Camera* camq;

quake::quake(IrrlichtDevice * device):mascene(device){
     device->getFileSystem()->addFileArchive("data/dataMAP/map-20kdm2.pk3");

    scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
    q3node = 0;

    // The Quake mesh is pickable, but doesn't get highlighted.
    if (q3levelmesh)
        q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);
      scene::ITriangleSelector* selector = 0;

    if (q3node)
    {
        q3node->setPosition(core::vector3df(-1350,130,-1400));

        selector = smgr->createOctreeTriangleSelector(
                q3node->getMesh(), q3node);
        q3node->setTriangleSelector(selector);
        // We're not done with this selector yet, so don't drop it.
    }
    
 
   
}

void quake::initiatedHeros(){
    IAnimatedMesh* heros_mesh = smgr ->getMesh("media/sydney.md2");
    heros->node = smgr->addAnimatedMeshSceneNode(heros_mesh,0,IDFlag_IsPickable);
    
    heros->node->setPosition(core::vector3df(40,230,-60));
    ITriangleSelector* selector = q3node -> getTriangleSelector();
     ic::vector3df edges[8];
    heros->node->getTransformedBoundingBox().getEdges(edges);
    auto boxMaxEdge = heros->node->getTransformedBoundingBox().MaxEdge;
    ic::vector3df boxCenter = heros->node->getTransformedBoundingBox().getCenter();
    ic::vector3df ellipseRadius = boxMaxEdge - boxCenter;
    if (selector)
    {
        is::ISceneNodeAnimatorCollisionResponse *collision = smgr->createCollisionResponseAnimator(selector,
         heros->node,  ellipseRadius);
        selector->drop(); // As soon as we're done with the selector, drop it.
        heros->node->addAnimator(collision);
        collision->drop();  // And likewise, drop the animator when we're done referring to it.
    }
}

void quake::setCam(Camera* cam){
   camq = cam;
   cam->initiateFPScam(heros->node);
   cam->initiateTPScam(heros->node);
   
 
}

void quake::draw(){
    smgr->drawAll();
    if(heros->node != NULL && camq != NULL){
            if(camq->ActiveId == camq->IdFps)
                heros->turnright(camq->camFPS->getRotation());
            camq->updateFPScam(heros->node);
            camq->updateTPSCam(heros->node);
    }
}