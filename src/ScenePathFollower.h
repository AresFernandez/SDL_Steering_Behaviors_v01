#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class ScenePathFollower :
	public Scene
{
public:
	ScenePathFollower();
	~ScenePathFollower();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();

	bool lastFrame;
private:
	std::vector<Agent*> agents;
	Vector2D target;
};

