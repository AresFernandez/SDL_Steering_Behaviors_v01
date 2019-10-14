#include "SceneFlocking.h"
#include "Flocking.h"

using namespace std;

SceneFlocking::SceneFlocking()
{
	NeighborSRadius = 50;
	NeighborCRadius = 300;
	NeighborARadius = 150;
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
			//agent->setMaxVelocity(agent->getMaxVelocity() / 2.f);
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
		agent->UpdateNeighborhood(agents, NeighborARadius, NeighborCRadius, NeighborSRadius);
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
	return "SDL Steering Behaviors :: Flocking Demo";
}