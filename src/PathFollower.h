#pragma once
#include "Agent.h"

class PathFollower :
	public Agent::SteeringBehavior
{
public:
	PathFollower();
	~PathFollower();
	void applySteeringForce(Agent *agent, float dtime);
};
