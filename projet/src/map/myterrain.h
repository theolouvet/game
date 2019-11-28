#ifndef MYTERRAIN_H
#define MYTERRAIN_H

#include<irrlicht/irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class myterrain
{
private:
    /* data */
public:
    myterrain(/* args */);
   
    scene::ITerrainSceneNode* monterrain;
    void terrainHM(ISceneManager*,const io::path& );
    void setMaterialTexture(u32, video::ITexture*);
    void setMaterialFlag(video::E_MATERIAL_FLAG, bool);
    void setMaterialType(video::E_MATERIAL_TYPE);
    void myShaders(io::path, io::path, video::IGPUProgrammingServices*);
    void myShaders(io::path, io::path, video::IGPUProgrammingServices*,
                    IShaderConstantSetCallBack*);
    void addskybox(ISceneManager*, IVideoDriver*);
    void rotationSkydome(vector3df v);
    const video::E_GPU_SHADING_LANGUAGE shadingLanguage = video::EGSL_DEFAULT;

    scene::ISceneNode* skydome;
};

#endif
