#include "SceneEvade.h"
#include "Arrive.h"
#include "Evade.h"

using namespace std;

SceneEvade::SceneEvade()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Arrive);
	agent->setPosition(Vector2D(600, 50));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);

	agent = new Agent();
	agent->setBehavior(new Evade);
	agent->setPosition(Vector2D(400,400));
	agent->setTargetAgent(agents[0]);
	agent->setMaxVelocity(50);
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);
}

SceneEvade::~SceneEvade()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneEvade::update(float dtime, SDL_Event *event)
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

void SceneEvade::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneEvade::getTitle()
{
	return "SDL Steering Behaviors :: Evade Demo";
}