#include"terrainscene.h"












terrainscene::terrainscene(IrrlichtDevice* device, IShaderConstantSetCallBack* mc):mascene(device){
    //terrain creation

   
   
    IVideoDriver* driver = device->getVideoDriver();
    
    const io::path& heightMapFileName = "data/dataterrain/hm2.jpg";
    const io::path& TextureFileName = "data/dataterrain/terrain-texture.jpg";
    io::path vsFileName = "data/dataterrain/terrain.vert"; // filename for the vertex shader
    io::path psFileName = "data/dataterrain/terrain.frag"; // filename for the pixel shader
    myterrain ter = myterrain();
    
    ter.terrainHM(smgr, heightMapFileName);
    ter.setMaterialFlag(video::EMF_LIGHTING, false);
    ter.setMaterialTexture(0, driver->getTexture(TextureFileName));
     ter.setMaterialTexture(1, driver->getTexture("data/datawater/stones.jpg"));
  //  ter.myShaders(vsFileName, psFileName, driver->getGPUProgrammingServices(), &mc);
    ter.addskybox(smgr, driver);
    ter.createTriangleSelector();
    //sydney.addcolision(ter.monterrain->getTriangleSelector(), smgr);
    skydome = ter.skydome;

    //quad creation
    const io::path& vsquad = "data/datawater/vtest.vert";
    const io::path& fsquad = "data/datawater/ftest.frag";
    waterquad water = waterquad(smgr, driver,
        dimension2df(800,800), dimension2du(25,25));
  
    water.myShaders(vsquad, fsquad, driver->getGPUProgrammingServices(), mc);

    
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
    keyMap[0].KeyCode = irr::KEY_KEY_Z;        // Z
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
    keyMap[1].KeyCode = irr::KEY_KEY_S;        // s
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
    keyMap[2].KeyCode = irr::KEY_KEY_A;        // a
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
    keyMap[3].KeyCode = irr::KEY_KEY_D;        // d
    keyMap[4].Action = irr::EKA_JUMP_UP;       // saut
    keyMap[4].KeyCode = irr::KEY_SPACE;        // barre espace
    camfree =  smgr->addCameraSceneNodeFPS(
            0,
    100,
    10.0f,
    -1,
    0,//keymap
    5
    );
    camfree->setFarValue(30000.0f);
   
    start = std::chrono::system_clock::now();

     device->getFileSystem()->addFileArchive("data/AspecQ3compet2.pk3");
  //  scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
  scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("AspecQ3compet2.bsp");
   scene::IMeshSceneNode* q3node = 0;

    // The Quake mesh is pickable, but doesn't get highlighted.
    if (q3levelmesh)
        q3node = smgr->addOctreeSceneNode(q3levelmesh->getMesh(0), 0, IDFlag_IsPickable);
      scene::ITriangleSelector* selector = 0;

    if (q3node)
    {
        q3node->setPosition(core::vector3df(0,100,0));

        selector = smgr->createOctreeTriangleSelector(
                q3node->getMesh(), q3node);
        q3node->setTriangleSelector(selector);
        // We're not done with this selector yet, so don't drop it.
    }

  

}

void terrainscene::draw(){
    smgr->drawAll();
    end = std::chrono::system_clock::now();
    t = std::chrono::duration_cast<std::chrono::duration<float>>(start - end).count();
           if(smgr->getActiveCamera()->getPosition().Y <600.0f){
            test = 10.0f;
            alphaw = 0.5f;
        }
        else if(smgr->getActiveCamera()->getPosition().Y >3000.0f){
            test = 1.0f;
            alphaw = 1.0f;
        }
        else{
            test =  10 * (3000.0f - smgr->getActiveCamera()->getPosition().Y)/2400.0f;
            alphaw = 0.5f + 0.5f * (3000.0f - smgr->getActiveCamera()->getPosition().Y)/2400.0f;
        }
    vector3df rot = skydome->getRotation();
    skydome->setRotation(rot + vector3df(0,0.01,0));
}