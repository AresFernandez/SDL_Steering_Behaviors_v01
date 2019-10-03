#include "ScenePursue.h"
#include "Arrive.h"
#include "Pursue.h"

using namespace std;

ScenePursue::ScenePursue()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Arrive);
	agent->setPosition(Vector2D(600, 50));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);

	agent = new Agent();
	agent->setBehavior(new Pursue);
	agent->setTargetAgent(agents[0]);
	agent->setMaxVelocity(150);
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);
}

ScenePursue::~ScenePursue()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePursue::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}

}

void ScenePursue::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* ScenePursue::getTitle()
{
	return "SDL Steering Behaviors :: Pursue Demo";
}