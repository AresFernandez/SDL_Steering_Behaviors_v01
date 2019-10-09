#include "Flocking.h"

Flocking::Flocking()
{
}

Flocking::~Flocking()
{
}

void Flocking::applySteeringForce(Agent *agent, float dtime)
{
	Vector2D averagePosition;

	for each (Agent* neighbor in agent->neighborhood)
	{
		averagePosition += neighbor->getPosition();
	}

	averagePosition /= agent->neighborhood.size();
	draw_circle(TheApp::Instance()->getRenderer(), (int)averagePosition.x, (int)averagePosition.y, 15, 0, 0, 255, 255);
}
