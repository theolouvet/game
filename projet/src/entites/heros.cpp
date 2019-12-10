#include "heros.h"

#include <iostream>
Heros::Heros()
{

}

void Heros::loadTexture(irr::video::ITexture *texture){
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    node->setMD2Animation(irr::scene::EMAT_STAND);
    node->setMaterialTexture( 0, texture);
}

void Heros::saut(){
   if(state != is::EMAT_JUMP && isjump){
        state = is::EMAT_JUMP;
        node->setMD2Animation( is::EMAT_JUMP);
    }
}

void Heros::shoot(){
    is::ISceneManager* sm = node->getSceneManager();
	is::ICameraSceneNode* camera = sm->getActiveCamera();

	SParticleImpact imp;
	imp.when = 0;

	// get line of camera
   

    auto size = device->getVideoDriver()->getScreenSize();
     ic::vector2df mp = ic::vector2df(mousePostion.X*1.0f, mousePostion.Y*1.0f);
    mp.X = (1.0f*mp.X/size.Width -0.5f)/2.0f;
    mp.Y = (1.0f*mp.Y/size.Height -0.5f)/2.0f;
    float d = sqrt(pow(mp.X/size.Width,2)+ 
     pow(mp.Y/size.Height,2));
  
 //  d = d/ds;
    float angle = acos((1.0f*mp.X/size.Width)/d) *  180.0f /M_PI;
    std::cout<<"distance "<<d<<"  "<< 1.0f *mp.X<<" "<<mp.Y<<" "<<angle<<std::endl;


	
	ic::vector3df start = getPosition();
	ic::vector3df end = (camera->getTarget() - start)*cos(angle);
    
	end.normalize();
	start += end*8.0f;
	end = start + (end * camera->getFarValue());

	ic::triangle3df triangle;

	ic::line3d<irr::f32> line(start, end);

	// get intersection point with map
	is::ISceneNode* hitNode;
	if (sm->getSceneCollisionManager()->getCollisionPoint(
		line, ms, end, triangle, hitNode))
	{
		// collides with wall
		ic::vector3df out = triangle.getNormal();
		out.setLength(0.03f);

		imp.when = 1;
		imp.outVector = out;
		imp.pos = end;
	}
	else
	{
		// doesnt collide with wall
		ic::vector3df start = camera->getPosition();
		ic::vector3df end = (camera->getTarget() - start);
//        ic::vector3df end = (ic::vector3df(mousePostion.X, mousePostion.Y, 0) - start);
		end.normalize();
		start += end*8.0f;
		end = start + (end * camera->getFarValue());
	}

	// create fire ball
	is::ISceneNode* node = 0;
	node = sm->addBillboardSceneNode(0,
		ic::dimension2d<irr::f32>(25,25), start);

	node->setMaterialFlag(iv::EMF_LIGHTING, false);
	node->setMaterialTexture(0, sm->getVideoDriver()->getTexture("media/fireball.bmp"));
	node->setMaterialType(iv::EMT_TRANSPARENT_ADD_COLOR);

	irr::f32 length = (irr::f32)(end - start).getLength();
	const irr::f32 speed = 0.6f;
	irr::u32 time = (irr::u32)(length / speed);

	is::ISceneNodeAnimator* anim = 0;

	// set flight line

	anim = sm->createFlyStraightAnimator(start, end, time);
	node->addAnimator(anim);
	anim->drop();

	anim = sm->createDeleteAnimator(time);
	node->addAnimator(anim);
	anim->drop();

	if (imp.when)
	{
		// create impact note
		imp.when = device->getTimer()->getTime() + (time - 100);
		Impacts.push_back(imp);
	}
}


void Heros::avancer(){
    ic::vector3df pos = getPosition();
    ic::vector3df rot = getRotation();
    float pas = 1;
    ic::vector3df mvt = ic::vector3df(0,0,0);
    mvt.X +=  pas*cos(2.0f * M_PI * rot.Y/360);
    mvt.Z -=  pas*sin(2.0f * M_PI * rot.Y/360);
    node->setPosition(pos + mvt);
}

void Heros::reculer(){
     float pas = 1;
    ic::vector3df pos = getPosition();
    ic::vector3df rot = getRotation();
    ic::vector3df mvt = ic::vector3df(0,0,0);
    mvt.X +=  pas*cos(2.0f * M_PI * rot.Y/360);
    mvt.Z -=  pas*sin(2.0f * M_PI * rot.Y/360);
    node->setPosition(pos - mvt);
}

void Heros::turnleft(){
    ic::vector3df pos = getRotation();
    pos.Y -= 1;
    node->setRotation(pos);
}

void Heros::turnright(){
    ic::vector3df pos = getRotation();
    pos.Y += 1;
    node->setRotation(pos);
}

void Heros::turnleft(ic::vector3df rot){;
    node->setRotation(rot);
}

void Heros::turnright(ic::vector3df rot){
    node->setRotation(ic::vector3df(0,rot.Y - 90,0));
}

void Heros::keyreception(MyEventReceiver* receiver){

        if(receiver->IsKeyDown(irr::KEY_KEY_Z)){
                avancer();
                irr::scene::ISceneNodeAnimatorList A = node->getAnimators(); 
        }else if(receiver->IsKeyDown(irr::KEY_KEY_S)){
                reculer();
        }if(receiver->IsKeyDown(irr::KEY_KEY_A)){
                turnleft();
        }if(receiver->IsKeyDown(irr::KEY_KEY_E)){
                turnright();
        }
        if(anim->isFalling()){
            saut();
        }else if((receiver->IsKeyDown(irr::KEY_KEY_A) ||
           receiver->IsKeyDown(irr::KEY_KEY_Z) ||
           receiver->IsKeyDown(irr::KEY_KEY_E) ||
           receiver->IsKeyDown(irr::KEY_KEY_S))){ 
            run();
        }else
        {
            stand();
        }

        if(isjump && !anim->isFalling()){
            isjump = false;
        }

         if(receiver->IsKeyDown(irr::KEY_SPACE) && !anim->isFalling()){
           
           isjump = true;
           anim->jump(2);
        }

        if(receiver->MouseState.LeftButtonDown){
            shoot();
        }

       mousePostion = receiver->MouseState.Position; 
        
}

void Heros::add_animator(irr::scene::ISceneNodeAnimatorCollisionResponse* a){
    anim = a;
    node->addAnimator(anim);
}

void Heros::initJump(){
    posinit = getPosition();
    posf = posinit;
    posf.Y += djump;
    dt = 0.1;
    isjump = true;
}


void Heros::setMapSelector(is::IMetaTriangleSelector* metaselector){
    ms = metaselector;
}

void Heros::setDevice(irr::IrrlichtDevice* dev){
    device = dev;
}


