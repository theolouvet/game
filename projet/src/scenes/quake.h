#ifndef QUAKE
#define QUAKE

#include<irrlicht/irrlicht.h>
#include"mascene.h"
#include"../camera/camera.h"

class quake : public mascene
{
private:
    /* data */
public:
    quake():mascene(){};
    quake(IrrlichtDevice *);
    void initiatedHeros();
    void setCam(Camera*);
    void draw() override;
};

#endif


