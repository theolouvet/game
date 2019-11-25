#ifndef HEROS_H
#define HEROS_H

#include "personnages.h"

class Heros: public Personnages
{
public:
    Heros();
    void loadTexture(irr::video::ITexture *);
    
    void avancer();
    void reculer();
    void turnright();
    void turnleft();
    void turnright(ic::vector3df);
    void turnleft(ic::vector3df);
};

#endif // HEROS_H
