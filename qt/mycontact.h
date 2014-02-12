#ifndef MYCONTACT_H
#define MYCONTACT_H
#include <Box2D.h>
class MyContact: public b2ContactListener 
{
private:

    //void BeginContact(b2Contact* contact);    
    void EndContact(b2Contact* contact);
	//void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	//void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
}; 
#endif MYCONTACT_H

