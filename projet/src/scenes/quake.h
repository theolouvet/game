#ifndef QUAKE
#define QUAKE

#include<irrlicht/irrlicht.h>
#include"mascene.h"
#include"../camera/camera.h"
#include<chrono>

class quake : public mascene
{
private:
    /* data */
    std::chrono::time_point<std::chrono::system_clock> start, end;
    float dt = -1;
public:
    quake():mascene(){};
    quake(IrrlichtDevice *);
    void initiatedHeros();
    void setCam(Camera*);
    void draw() override;
};

#endif


