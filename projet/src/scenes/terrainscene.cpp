#include"terrainscene.h"



terrainscene::terrainscene(IrrlichtDevice* device, IShaderConstantSetCallBack* mc):mascene(device){
    //creation de la scene pour le terrain  
    id = tId; 
    IVideoDriver* driver = device->getVideoDriver();
    const io::path& heightMapFileName = "data/dataterrain/hm2.jpg";
    const io::path& TextureFileName = "data/dataterrain/terrain-texture.jpg";
    io::path vsFileName = "data/dataterrain/terrain.vert"; // filename for the vertex shader
    io::path psFileName = "data/dataterrain/terrain.frag"; // filename for the pixel shader
    myterrain ter = myterrain();//Creation du terrain
    ter.terrainHM(smgr, heightMapFileName);
    ter.setMaterialFlag(video::EMF_LIGHTING, false);
    ter.setMaterialTexture(0, driver->getTexture(TextureFileName));
    ter.setMaterialTexture(1, driver->getTexture("data/datawater/stones.jpg"));//non utilise a ce jour
    ter.addskybox(smgr, driver);
    ter.createTriangleSelector();
    skydome = ter.skydome;
    selector = ter.getTriangleSelector();

    //quad creation
    const io::path& vsquad = "data/datawater/vtest.vert";
    const io::path& fsquad = "data/datawater/ftest.frag";
    waterquad water = waterquad(smgr, driver,
        dimension2df(800,800), dimension2du(25,25));
  
    water.myShaders(vsquad, fsquad, driver->getGPUProgrammingServices(), mc);


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
        bill->setPosition(posPortail);
	}
    bill->setDebugDataVisible(is::EDS_BBOX);

    
    initposHeros = ic::vector3df(4332,1171,-2837);
   
    start = std::chrono::system_clock::now();
}

void terrainscene::initiateHeros(){
    heros->node = smgr->addAnimatedMeshSceneNode(heros->getMesh(),0,IDFlag_IsPickable);
    heros->node->setPosition(initposHeros);
    ic::vector3df edges[8];
    heros->node->getTransformedBoundingBox().getEdges(edges);
    auto boxMaxEdge = heros->node->getTransformedBoundingBox().MaxEdge;
    ic::vector3df boxCenter = heros->node->getTransformedBoundingBox().getCenter();
    ic::vector3df ellipseRadius = boxMaxEdge - boxCenter;
    if (selector)
    {
        is::ISceneNodeAnimatorCollisionResponse *collision = 
        smgr->createCollisionResponseAnimator(selector,
         heros->node,  ellipseRadius, vector3df(0,-10.0f,0));
        // heros->setMapSelector(metaselector);
        selector->drop(); 
        //metaselector->drop();
        heros->add_animator(collision);
        collision->drop();  
    }

    heros->node->setDebugDataVisible(is::EDS_BBOX);
}

void terrainscene::draw(){
    smgr->drawAll();

    end = std::chrono::system_clock::now();
    t = std::chrono::duration_cast<std::chrono::duration<float>>(start - end).count();
    if(heros->node != NULL && camq != NULL){
            if(camq->ActiveId == camq->IdFps)
                heros->turnright(camq->camFPS->getRotation());
            camq->updateFPScam(heros->node);
            camq->updateTPSCam(heros->node);
    }
  
    
        if(smgr->getActiveCamera()->getPosition().Y <600.0f){
            fragment = 10.0f;
            alphaw = 0.5f;
        }
        else if(smgr->getActiveCamera()->getPosition().Y >3000.0f){
            fragment = 1.0f;
            alphaw = 1.0f;
        }
        else{
            fragment =  10 * (3000.0f - smgr->getActiveCamera()->getPosition().Y)/2400.0f;
            alphaw = 0.5f + 0.5f * (3000.0f - smgr->getActiveCamera()->getPosition().Y)/2400.0f;
        }
    

    vector3df rot = skydome->getRotation();
    skydome->setRotation(rot + vector3df(0,0.01,0));

    auto bbill = bill->getTransformedBoundingBox();
    auto bheros = heros->node->getTransformedBoundingBox();
    if(bbill.intersectsWithBox(bheros)){
        std::cout<<"intersection"<<std::endl;
        inPortal = true;
    }else
    {
        inPortal = false;
    }
}