#include "SceneArrive.h"
#include "Arrive.h"

using namespace std;

SceneArrive::SceneArrive()
{
	Agent *agent = new Agent;
	agent->setBehavior(new Arrive);
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	showArriveRadius = true;
}

SceneArrive::~SceneArrive()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneArrive::update(float dtime, SDL_Event *event)
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
		if (event->button.button == SDL_BUTTON_RIGHT)
		{
			showArriveRadius = false;
		}
		break;
	default:
		break;
	}
	agents[0]->update(dtime, event);
}

void SceneArrive::draw()
{
	if(showArriveRadius)
		draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* SceneArrive::getTitle()
{
	return "SDL Steering Behaviors :: Arrive Demo";
}