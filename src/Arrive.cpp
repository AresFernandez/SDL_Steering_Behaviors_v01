#include "Arrive.h"



Arrive::Arrive()
{
}


Arrive::~Arrive()
{
}

void Arrive::applySteeringForce(Agent *agent, float dtime)
{
	float slowingRadius = 200;
	agent->drawRadius(slowingRadius);
	///Getting Steering Force Vector
	//Get desired Direction
	Vector2D DesiredVelocity = agent->getTarget() - agent->getPosition();
	float distance = DesiredVelocity.Length();
	float factor = distance / slowingRadius;
	float auxVelocity = agent->getMaxVelocity();

	//Normalize direction and apply max speed to it
	DesiredVelocity.Normalize();
	if (distance <= slowingRadius)
		auxVelocity = agent->getMaxVelocity() * factor;

	//Don't apply force if they are too close (this is to avoid flickering moves)
	if (distance <= 1)
		return;

	DesiredVelocity *= auxVelocity;
	//Calculate Steering Force Vector necessary to correct trajectory
	Vector2D SteeringForce = DesiredVelocity - agent->getVelocity();
	SteeringForce /= auxVelocity;

	///Applying Force equations
	//Calculate acceleration (a=F/m)
	Vector2D Acceleration = SteeringForce * agent->getMaxForce() / agent->getMass();
	//Calculate velocity (v=v0+a*t)
	Vector2D Velocity = agent->getVelocity() + Acceleration * dtime;
	agent->setVelocity(Velocity.Truncate(auxVelocity));
	//Calculate position (p=p0+v*t)
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}
