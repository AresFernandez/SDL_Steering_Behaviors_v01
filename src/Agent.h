#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"


class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};
	};
private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;
	Agent *targetAgent;

	float orientation;
	float max_force;
	float max_velocity;
	float mass;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	Agent();
	~Agent();

	std::vector<Agent*> CohesionNeighborhood;
	std::vector<Agent*> SeparationNeighborhood;
	std::vector<Agent*> AlignmentNeighborhood;
	std::vector<Vector2D> path;

	struct Obstacle
	{
		Obstacle(Vector2D v) {
			init = v;
			end = NULL;
		}
		Vector2D init;
		Vector2D end;
	};
	std::vector<Obstacle> obstacles;

	int currentPathPoint;

	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	Agent* getTargetAgent();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setTargetAgent(Agent*);
	void setVelocity(Vector2D velocity);
	void setMaxVelocity(float velocity);
	void update(float dtime, SDL_Event *event);
	void draw();
	void drawRadius(float);
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	void Agent::UpdateNeighborhood(std::vector<Agent*> agents, float ARadius, float CRadius, float SRadius);
};
