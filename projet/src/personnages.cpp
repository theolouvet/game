#include "personnages.h"

Personnages::Personnages()
{

}

ic::vector3df Personnages::getPosition(){
    return node->getPosition();
}

ic::vector3df Personnages::getRotation(){
    return node->getRotation();
}
