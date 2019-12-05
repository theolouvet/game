#include"mascene.h"
#include "heros.h"

mascene::mascene(IrrlichtDevice *device){
   // smgr = device->getSceneManager();
   smgr = device ->getSceneManager()->createNewSceneManager(false);
}

void mascene::draw(){
    smgr->drawAll();
}

