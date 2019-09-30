#include "Flee.h"

Flee::Flee()
{
}

Flee::~Flee()
{
}

void Flee::applySteeringForce(Agent *agent, float dtime)
{
	///Getting Steering Force Vector
	//Get desired Direction
	Vector2D DesiredVelocity = agent->getPosition() - agent->getTarget();
	//Normalize direction and apply max speed to it
	DesiredVelocity.Normalize();
	DesiredVelocity *= agent->getMaxVelocity();
	//Calculate Steering Force Vector necessary to correct trajectory
	Vector2D SteeringForce = DesiredVelocity - agent->getVelocity();
	SteeringForce /= agent->getMaxVelocity();

	///Applying Force equations
	//Calculate acceleration (a=F/m)
	Vector2D Acceleration = SteeringForce * agent->getMaxForce() / agent->getMass();
	//Calculate velocity (v=v0+a*t)
	Vector2D Velocity = agent->getVelocity() + Acceleration * dtime;
	agent->setVelocity(Velocity.Truncate(agent->getMaxVelocity()));
	//Calculate position (p=p0+v*t)
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}
