#include"quake.h"
#include<iostream>
#include"../entites/heros.h"
#include"../camera/camera.h"

 scene::IMeshSceneNode* q3node ;


quake::quake(IrrlichtDevice * device):mascene(device){

    id = qId;
    
    device->getFileSystem()->addFileArchive("data/map_oxodm1.pk3");
  
  scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("oxodm1.bsp");
    q3node = 0;
    metaselector = smgr->createMetaTriangleSelector();
    
    if (q3levelmesh)
        q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);
      scene::ITriangleSelector* selector = 0;

    if (q3node)
    {
        q3node->setPosition(core::vector3df(-1350,130,-1400));

        selector = smgr->createOctreeTriangleSelector(
                q3node->getMesh(), q3node);
        q3node->setTriangleSelector(selector);
        metaselector->addTriangleSelector(selector);
    }


    bill = 0;
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
        bill->setPosition(ic::vector3df(62,322.982,1675.53));
	}
    bill->setDebugDataVisible(is::EDS_BBOX);
    initposHeros = ic::vector3df(66,322.982,1541.53);
    
        start = std::chrono::system_clock::now();
   
}

void quake::initiatedHeros(){
    
    heros->node = smgr->addAnimatedMeshSceneNode(heros->getMesh(),0,IDFlag_IsPickable);
    
    heros->node->setPosition(initposHeros);
    

    ITriangleSelector* selector = q3node -> getTriangleSelector();
     ic::vector3df edges[8];
    heros->node->getTransformedBoundingBox().getEdges(edges);
    auto boxMaxEdge = heros->node->getTransformedBoundingBox().MaxEdge;
    ic::vector3df boxCenter = heros->node->getTransformedBoundingBox().getCenter();
    ic::vector3df ellipseRadius = boxMaxEdge - boxCenter;
    if (selector)
    {
        is::ISceneNodeAnimatorCollisionResponse *collision = smgr->createCollisionResponseAnimator(metaselector,
         heros->node,  ellipseRadius, vector3df(0,-10.0f,0));
         heros->setMapSelector(metaselector);
        selector->drop(); 
        metaselector->drop();
        heros->add_animator(collision);
        collision->drop();  
    }

    heros->node->setDebugDataVisible(is::EDS_BBOX);
    
}

void quake::freecamera(){
    ICameraSceneNode* camf = smgr->addCameraSceneNodeFPS(0);
    camf->setPosition(ic::vector3df(66,322.982,1541.53));
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

    
   
    auto bbill = bill->getTransformedBoundingBox();
    auto bheros = heros->node->getTransformedBoundingBox();
    if(bbill.intersectsWithBox(bheros)){
        std::cout<<"intersection"<<std::endl;
        inPortal = true;
    }else
    {
        inPortal = false;
    }
    
    if(getActiveCamera() != smgr->getActiveCamera()){
        setActiveCamera(smgr->getActiveCamera());
    }

    
}