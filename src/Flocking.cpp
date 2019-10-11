#include "Flocking.h"

Flocking::Flocking()
{
}

Flocking::~Flocking()
{
}

void Flocking::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D averagePosition, averageFlee, averageVelocity;
	float K_COHESION_FORCE = 0.2f, K_SEPARATION_FORCE = 0.7f, K_ALIGNMENT_FORCE = 0.1f, K_MAX_FLOCKING_FORCE = 1000.0f;
	Vector2D FlockingForce = Vector2D(0, 0);
	Vector2D SteeringForce;

	for each (Agent* neighbor in agent->neighborhood)
	{
		averagePosition += neighbor->getPosition();
		averageFlee += agent->getPosition() - neighbor->getPosition();
		averageVelocity += neighbor->getVelocity();
	}

	if (agent->neighborhood.size() > 0)
	{
		averagePosition /= agent->neighborhood.size();
		Vector2D CohesionDirection = averagePosition - agent->getPosition();
		CohesionDirection = Vector2D::Normalize(CohesionDirection);

		averageFlee /= agent->neighborhood.size();
		Vector2D SeparationDirection = Vector2D::Normalize(averageFlee);

		averageVelocity /= agent->neighborhood.size();
		Vector2D AlignmentDirection = Vector2D::Normalize(averageVelocity);

		FlockingForce = CohesionDirection * K_COHESION_FORCE +
			SeparationDirection * K_SEPARATION_FORCE +
			averageVelocity * K_ALIGNMENT_FORCE;

		FlockingForce *= K_MAX_FLOCKING_FORCE;

		Vector2D DesiredVelocity = FlockingForce;
		SteeringForce = DesiredVelocity - agent->getVelocity();
		SteeringForce /= agent->getMaxVelocity();
	}
	draw_circle(TheApp::Instance()->getRenderer(), (int)averagePosition.x, (int)averagePosition.y, 15, 0, 0, 255, 255);

	///Applying Force equations
	//Calculate acceleration (a=F/m)
	Vector2D Acceleration = SteeringForce * agent->getMaxForce() / agent->getMass();
	//Calculate velocity (v=v0+a*t)
	Vector2D Velocity = agent->getVelocity() + Acceleration * dtime;
	agent->setVelocity(Velocity.Truncate(agent->getMaxVelocity()));
	//Calculate position (p=p0+v*t)
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}
