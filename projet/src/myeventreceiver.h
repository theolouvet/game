#ifndef MYEVENTRECEIVER
#define MYEVENTRECEIVER

#include<irrlicht/irrlicht.h>

class MyEventReceiver: public irr::IEventReceiver
{
public:
    virtual bool OnEvent(const irr::SEvent&);
    virtual bool IsKeyDown(irr::EKEY_CODE) const;
    bool KeyDown = false;
    MyEventReceiver();
private:
   
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
};

#endif 