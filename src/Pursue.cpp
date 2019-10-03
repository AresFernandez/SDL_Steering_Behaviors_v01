#include "Pursue.h"

Pursue::Pursue()
{
}

Pursue::~Pursue()
{
}

void Pursue::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D PredictedTarget = agent->getTargetAgent()->getPosition() + agent->getTargetAgent()->getVelocity();
	float distanceToPT = (agent->getPosition() - agent->getTargetAgent()->getPosition()).Length();
	float T = distanceToPT /  agent->getTargetAgent()->getMaxVelocity();

	PredictedTarget = agent->getTargetAgent()->getPosition() + agent->getTargetAgent()->getVelocity() * T;
	draw_circle(TheApp::Instance()->getRenderer(), PredictedTarget.x, PredictedTarget.y, 15, 0, 0, 255, 255);

	///Getting Steering Force Vector
	//Get desired Direction
	Vector2D DesiredVelocity = PredictedTarget - agent->getPosition();
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
