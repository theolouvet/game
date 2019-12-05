#ifndef QUAKE
#define QUAKE

#include<irrlicht/irrlicht.h>
#include"mascene.h"

class quake : public mascene
{
private:
    /* data */
public:
    quake(IrrlichtDevice *);
    void initiatedHeros();
};

#endif


