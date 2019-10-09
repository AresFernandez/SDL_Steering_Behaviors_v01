#include "SceneFlocking.h"
#include "Flocking.h"

using namespace std;

SceneFlocking::SceneFlocking()
{
	NeighborRadius = 300;
	lastFrame = false;
}

SceneFlocking::~SceneFlocking()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlocking::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT && !lastFrame)
		{
			lastFrame = true;
			Agent *agent = new Agent;
			agent->setBehavior(new Flocking);
			agent->setPosition(Vector2D(event->button.x, event->button.y));
			agent->setVelocity(Vector2D(agent->getMaxVelocity(), 0));
			agent->loadSpriteTexture("../res/zombie1.png", 8);
			agents.push_back(agent);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		lastFrame = false;
		break;
	default:
		break;
	}

	for each (Agent* agent in agents)
	{
		agent->UpdateNeighborhood(agents, NeighborRadius);
		agent->update(dtime, event);
	}
}

void SceneFlocking::draw()
{
	for each (Agent* agent in agents)
	{
		agent->draw();
	}
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}