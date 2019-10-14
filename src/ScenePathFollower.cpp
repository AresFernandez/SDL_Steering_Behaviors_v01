#include "ScenePathFollower.h"
#include "PathFollower.h"

using namespace std;

ScenePathFollower::ScenePathFollower()
{
	lastFrame = false;

	Agent *agent = new Agent;
	agent->setBehavior(new PathFollower);
	agent->setPosition(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
}

ScenePathFollower::~ScenePathFollower()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFollower::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT && !lastFrame)
		{
			lastFrame = true;

			agents[0]->path.push_back(Vector2D(event->button.x, event->button.y));
		}
		break;
	case SDL_MOUSEBUTTONUP:
		lastFrame = false;
		break;
	default:
		break;
	}

	agents[0]->update(dtime, event);
}

void ScenePathFollower::draw()
{
	agents[0]->draw();

	for each (Vector2D pathPoint in agents[0]->path)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)pathPoint.x, (int)pathPoint.y, 15, 0, 0, 255, 255);
	}
}

const char* ScenePathFollower::getTitle()
{
	return "SDL Steering Behaviors :: Path Follower Demo";
}