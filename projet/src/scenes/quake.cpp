#include"quake.h"
#include<iostream>
#include"../entites/heros.h"
#include"../camera/camera.h"

 scene::IMeshSceneNode* q3node ;
 Camera* camq;

quake::quake(IrrlichtDevice * device):mascene(device){
    // device->getFileSystem()->addFileArchive("data/dataMAP/map-20kdm2.pk3");
    device->getFileSystem()->addFileArchive("data/AspecQ3compet2.pk3");
  //  scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
  scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("AspecQ3compet2.bsp");
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

    scene::IBillboardSceneNode* bill = 0;
    core::vector3df waypoint[2];
	waypoint[0].set(-150,40,100);
	waypoint[1].set(350,40,100);
    // create animation for portals;
    scene::ISceneNodeAnimator* anim = 0;
	core::array<video::ITexture*> textures;
	for (s32 g=1; g<8; ++g)
	{
		core::stringc tmp("media/portal");
		tmp += g;
		tmp += ".bmp";
		video::ITexture* t = device->getVideoDriver()->getTexture( tmp );
		textures.push_back(t);
	}

	anim = smgr->createTextureAnimator(textures, 100);
	for(int r=0; r<2; ++r)
	{
		bill = smgr->addBillboardSceneNode(0, core::dimension2d<f32>(100,100),
			waypoint[r]+ core::vector3df(0,20,0));
		bill->setMaterialFlag(video::EMF_LIGHTING, false);
		bill->setMaterialTexture(0, device->getVideoDriver()->getTexture("media/portal1.bmp"));
		bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		bill->addAnimator(anim);
        bill->setPosition(ic::vector3df(-1365.35,-156.458,-2897.09));
	}
    
    
        start = std::chrono::system_clock::now();
   
}

void quake::initiatedHeros(){
    IAnimatedMesh* heros_mesh = smgr ->getMesh("media/sydney.md2");
    heros->node = smgr->addAnimatedMeshSceneNode(heros_mesh,0,IDFlag_IsPickable);
    
    heros->node->setPosition(ic::vector3df(-1365.35,-156.458,-3333.88));
    ITriangleSelector* selector = q3node -> getTriangleSelector();
     ic::vector3df edges[8];
    heros->node->getTransformedBoundingBox().getEdges(edges);
    auto boxMaxEdge = heros->node->getTransformedBoundingBox().MaxEdge;
    ic::vector3df boxCenter = heros->node->getTransformedBoundingBox().getCenter();
    ic::vector3df ellipseRadius = boxMaxEdge - boxCenter;
    if (selector)
    {
        is::ISceneNodeAnimatorCollisionResponse *collision = smgr->createCollisionResponseAnimator(selector,
         heros->node,  ellipseRadius, vector3df(0,-10.0f,0));
        selector->drop(); // As soon as we're done with the selector, drop it.
        heros->add_animator(collision);
        collision->drop();  // And likewise, drop the animator when we're done referring to it.
    }
}

void quake::freecamera(){
    ICameraSceneNode* camf = smgr->addCameraSceneNodeFPS(0);
    camf->setPosition(ic::vector3df(-1328,-195,-2978));
}

void quake::setCam(Camera* cam){
   camq = cam;
   cam->initiateFPScam(heros->node);
   cam->initiateTPScam(heros->node); 
}

void quake::draw(){
    smgr->drawAll();
    
    end = std::chrono::system_clock::now();
    dt = abs(std::chrono::duration_cast<std::chrono::duration<float>>(start - end).count());

   
    if(heros->node != NULL && camq != NULL){
            if(camq->ActiveId == camq->IdFps)
                heros->turnright(camq->camFPS->getRotation());
            camq->updateFPScam(heros->node);
            camq->updateTPSCam(heros->node);
    }
}