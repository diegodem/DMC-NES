#pragma once

#include <SDL.h>
#include "State.h"
#include "Timer.h"


class Player
{
public:
	Player();
	void update();
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	void attackSword();
	void fire();
	void noButtonPressed();
	SDL_Rect *getRect();
	SDL_Rect *getAttackRect();
	int getCurrentFrame();
	State getState();

private:

	SDL_Rect rect;
	SDL_Rect attackRect;
	
	State state;

	Timer frameTimer;

	int currentFrame;

};