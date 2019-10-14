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
	float K_COHESION_FORCE = 0.3f, K_SEPARATION_FORCE = 0.4f, K_ALIGNMENT_FORCE = 0.3f, K_MAX_FLOCKING_FORCE = 500.0f;
	Vector2D FlockingForce = Vector2D(0,0);
	Vector2D SteeringForce;

	for each (Agent* neighbor in agent->AlignmentNeighborhood)
	{
		averageVelocity += neighbor->getVelocity();
	}

	for each (Agent* neighbor in agent->CohesionNeighborhood)
	{
		averagePosition += neighbor->getPosition();
	}

	for each (Agent* neighbor in agent->SeparationNeighborhood)
	{
		averageFlee += agent->getPosition() - neighbor->getPosition();
	}

	Vector2D CohesionDirection = Vector2D(0,0);
	Vector2D SeparationDirection = Vector2D(0, 0);
	Vector2D AlignmentDirection = Vector2D(0, 0);


	if (agent->CohesionNeighborhood.size() > 0)
	{
		averagePosition /= agent->CohesionNeighborhood.size();
		CohesionDirection = averagePosition - agent->getPosition();
		CohesionDirection = Vector2D::Normalize(CohesionDirection);
	}
	
	if (agent->SeparationNeighborhood.size() > 0)
	{
		averageFlee /= agent->SeparationNeighborhood.size();
		SeparationDirection = Vector2D::Normalize(averageFlee);
	}

	if (agent->AlignmentNeighborhood.size() > 0)
	{
		averageVelocity /= agent->AlignmentNeighborhood.size();
		AlignmentDirection = Vector2D::Normalize(averageVelocity);
	}
	
	if (agent->AlignmentNeighborhood.size() > 0 || agent->SeparationNeighborhood.size() > 0 || agent->CohesionNeighborhood.size() > 0) {
		FlockingForce = CohesionDirection * K_COHESION_FORCE +
			SeparationDirection * K_SEPARATION_FORCE +
			AlignmentDirection * K_ALIGNMENT_FORCE;

		FlockingForce *= K_MAX_FLOCKING_FORCE;

		Vector2D DesiredVelocity = FlockingForce;
		SteeringForce = DesiredVelocity - agent->getVelocity();
		SteeringForce /= agent->getMaxVelocity();
	}



	///Applying Force equations
	//Calculate acceleration (a=F/m)
	Vector2D Acceleration = SteeringForce * agent->getMaxForce() / agent->getMass();
	//Calculate velocity (v=v0+a*t)
	Vector2D Velocity = agent->getVelocity() + Acceleration * dtime;
	agent->setVelocity(Velocity.Truncate(agent->getMaxVelocity()));
	//Calculate position (p=p0+v*t)
	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}
