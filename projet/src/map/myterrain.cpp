#include"myterrain.h"
#include<iostream>
myterrain::myterrain(){

}

void myterrain::terrainHM(ISceneManager* smgr,
const io::path& heightMapFileName){
    std::cout<<"generation terrain"<<std::endl;
    monterrain = smgr->addTerrainSceneNode(
        heightMapFileName,
        0,                  // parent node
        -1,                 // node id
        core::vector3df(-3000,-144,-6049),     // position
        core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df(50.f, 5.f, 50.f),  // scale (40,4,)
        video::SColor ( 255, 255, 255, 255 ),   // vertexColor
        5,                  // maxLOD
        scene::ETPS_17,             // patchSize
        4                   // smoothFactor
        );
     monterrain->scaleTexture(1.0f, 20.0f);

}

void myterrain::setMaterialTexture(u32 i, video::ITexture* t){
    monterrain->setMaterialTexture(i,t);
}
void myterrain::setMaterialFlag(video::E_MATERIAL_FLAG ef, bool b){
    monterrain->setMaterialFlag(ef, b);
}
void myterrain::setMaterialType(video::E_MATERIAL_TYPE et){
      monterrain->setMaterialType(et);
}

void myterrain::myShaders(io::path vs, io::path fs, video::IGPUProgrammingServices* gpu,
                            IShaderConstantSetCallBack* mc){
    
    s32 newMaterialType1 = 0;

    // create material from high level shaders (hlsl, glsl or cg)

    newMaterialType1 = gpu->addHighLevelShaderMaterialFromFiles(
        vs, "vertexMain", video::EVST_VS_1_1,
        fs, "pixelMain", video::EPST_PS_1_1,
        mc, video::EMT_SOLID, 0, shadingLanguage);
    setMaterialType((video::E_MATERIAL_TYPE)newMaterialType1);
    
}

void myterrain::addskybox(ISceneManager* smgr, IVideoDriver* driver){
    scene::ISceneNode* skybox=smgr->addSkyBoxSceneNode(
           driver->getTexture("data/datasky/irrlicht2_up.jpg"),
           driver->getTexture("data/datasky/irrlicht2_dn.jpg"),
           driver->getTexture("data/datasky/irrlicht2_lf.jpg"),
           driver->getTexture("data/datasky/irrlicht2_rt.jpg"),
           driver->getTexture("data/datasky/irrlicht2_ft.jpg"),
           driver->getTexture("data/datasky/irrlicht2_bk.jpg"));
       //scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("data/datasky/skydome.jpg"),16,8,0.95f,2.0f);
        skydome=smgr->addSkyDomeSceneNode(
            driver->getTexture("data/datasky/skydome.jpg"),30,8,0.96f,2.f);
       driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

       
}

void myterrain::createTriangleSelector(){
selector  = monterrain->getSceneManager()->createTerrainTriangleSelector(monterrain, 0);

       monterrain->setTriangleSelector(selector);
}

ITriangleSelector* myterrain::getTriangleSelector(){return monterrain->getTriangleSelector();}