#include "Seek.h"

Seek::Seek()
{
}

Seek::~Seek()
{
}

void Seek::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D steering = agent->getTarget() - agent->getPosition();
	steering.Normalize();
	agent->setVelocity (steering * agent->getMaxVelocity());
	agent->setPosition (agent->getPosition() + agent->getVelocity() * dtime); 
	// This is NOT the Seek steering behavior! We must take into count acceleration!
}
