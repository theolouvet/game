#ifndef WATERQUAD
#define WATERQUAD

#include<irrlicht/irrlicht.h>



using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class waterquad
{
private:
    /* data */
public:
    waterquad(ISceneManager*,IVideoDriver*,
    irr::core::dimension2d<irr::f32>,irr::core::dimension2d<irr::u32>);
    void myShaders(io::path, io::path, video::IGPUProgrammingServices*);
    void myShaders(io::path, io::path, video::IGPUProgrammingServices*,
                    IShaderConstantSetCallBack*);
    void setMaterialType(video::E_MATERIAL_TYPE);

    irr::scene::ISceneNode* ground;
    const video::E_GPU_SHADING_LANGUAGE shadingLanguage = video::EGSL_DEFAULT;
};

#endif
