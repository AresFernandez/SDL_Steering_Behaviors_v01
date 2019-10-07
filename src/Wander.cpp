#include "Wander.h"

Wander::Wander()
{
}

Wander::~Wander()
{
}

void Wander::applySteeringForce(Agent *agent, float dtime)
{
	float WanderRadius = 100;
	int MaxAngleChange = 180;
	static float angle = 0;
	angle += (rand() % (MaxAngleChange + 1))*0.0005f;

	Vector2D WanderTarget;
	WanderTarget.x = agent->getTarget().x + WanderRadius * cos(angle * M_PI / 180.0f);
	WanderTarget.y = agent->getTarget().y + WanderRadius * sin(angle * M_PI / 180.0f);

	draw_circle(TheApp::Instance()->getRenderer(), (int)WanderTarget.x, (int)WanderTarget.y, 15, 0, 0, 255, 255);

	///Getting Steering Force Vector
	//Get desired Direction
	Vector2D DesiredVelocity = WanderTarget - agent->getPosition();
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
