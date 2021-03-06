#pragma once
#include <SDL.h>
#include "Timer.h"

class Enemy
{
public:
	void initializeRect(int x, int y);
	virtual void update(float deltaTime);
	SDL_Rect* getRect();
	void startFrameTimer();
	float getFrameTimer();
	int getCurrentFrame();
	void setCurrentFrame(int frame);
	void moveRect(int x);
private:
	SDL_Rect rect;
	Timer frameTimer;
	int currentFrame;
};