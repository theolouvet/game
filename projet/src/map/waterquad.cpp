#include"waterquad.h"

waterquad::waterquad(ISceneManager* smgr,IVideoDriver* driver,
irr::core::dimension2d<irr::f32> csize,irr::core::dimension2d<irr::u32> nbc){
    const irr::scene::IGeometryCreator *geomentryCreator = smgr->getGeometryCreator();
      
       irr::scene::IMesh* plane = geomentryCreator->createPlaneMesh(
                   csize,
                   nbc);

        ground = smgr->addMeshSceneNode(plane);

        video::ITexture* NormalMap = driver->getTexture("data/datawater/water-heightmap.jpg");
      if (NormalMap)
      {
         driver->makeNormalMapTexture(NormalMap, 9.0f);
         ground->setMaterialTexture(0, driver->getTexture("data/datawater/water.jpg"));
         ground->setMaterialTexture(1, NormalMap);
         ground->getMaterial(0).MaterialTypeParam = 0.035f;
      }



      // ground->setMaterialTexture(0, driver->getTexture("data/datawater/water-heightmap.jpg"));
       ground->setPosition(irr::core::vector3df(0.f, 0.f, 0.f));
      // ground->setMaterialType((video::E_MATERIAL_TYPE)newMaterialType2);
      // plane->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

/*void waterquad::myShaders(io::path vs, io::path fs, video::IGPUProgrammingServices* gpu){
    s32 newMaterialType2 = 0;
    MyShaderCallBack* mc = new MyShaderCallBack();
    newMaterialType2 = gpu->addHighLevelShaderMaterialFromFiles(
           vs, "vertexMain", video::EVST_VS_1_1,
           fs, "pixelMain", video::EPST_PS_1_1,
           mc, video::EMT_TRANSPARENT_ALPHA_CHANNEL, 0, shadingLanguage);
    setMaterialType((video::E_MATERIAL_TYPE)newMaterialType2);
    mc->drop();
}*/

void waterquad::myShaders(io::path vs, io::path fs, video::IGPUProgrammingServices* gpu,
                            IShaderConstantSetCallBack* mc){
    s32 newMaterialType2 = 0;
    
    newMaterialType2 = gpu->addHighLevelShaderMaterialFromFiles(
           vs, "vertexMain", video::EVST_VS_1_1,
           fs, "pixelMain", video::EPST_PS_1_1,
           mc, video::EMT_TRANSPARENT_ALPHA_CHANNEL, 0, shadingLanguage);
    setMaterialType((video::E_MATERIAL_TYPE)newMaterialType2);
    
}

void waterquad::setMaterialType(video::E_MATERIAL_TYPE et){
      ground->setMaterialType(et);
}