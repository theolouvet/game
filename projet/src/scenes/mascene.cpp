#include"mascene.h"
#include "../entites/heros.h"

mascene::mascene(IrrlichtDevice *device){
   // smgr = device->getSceneManager();
   smgr = device ->getSceneManager()->createNewSceneManager(false);
}

void mascene::draw(){
    smgr->drawAll();
}

void mascene::addHeros(Heros* h){
    heros = h;
}
