#include"quake.h"
#include"heros.h"


quake::quake(IrrlichtDevice * device):mascene(device){
     device->getFileSystem()->addFileArchive("data/dataMAP/map-20kdm2.pk3");

    scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
    scene::IMeshSceneNode* q3node = 0;

    // The Quake mesh is pickable, but doesn't get highlighted.
    if (q3levelmesh)
        q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);
      scene::ITriangleSelector* selector = 0;

    if (q3node)
    {
        q3node->setPosition(core::vector3df(-1350,130,-1400));

        selector = smgr->createOctreeTriangleSelector(
                q3node->getMesh(), q3node, 128);
        q3node->setTriangleSelector(selector);
        // We're not done with this selector yet, so don't drop it.
    }

     scene::ICameraSceneNode* camera =
    smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, ID_IsNotPickable, 0, 0, true, 3.f);
    camera->setPosition(core::vector3df(50,300,-60));
    camera->setTarget(core::vector3df(-70,30,-60));

    if (selector)
    {
        scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector, camera, core::vector3df(30,50,30),
            core::vector3df(0,-10,0), core::vector3df(0,30,0));
        selector->drop(); // As soon as we're done with the selector, drop it.
        camera->addAnimator(anim);
        anim->drop();  // And likewise, drop the animator when we're done referring to it.
    }
     /*
    sydney.node->setPosition(core::vector3df(50,300,-60));
   

    if (selector)
    {
        scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
            selector, sydney.node, core::vector3df(30,50,30),
            core::vector3df(0,-10,0), core::vector3df(0,30,0));
        selector->drop(); // As soon as we're done with the selector, drop it.
        sydney.node->addAnimator(anim);
        anim->drop();  // And likewise, drop the animator when we're done referring to it.
    }*/
   
}