#pragma once
#include <SDL.h>

class Projectile
{
public:
	Projectile();
	void update();
	SDL_Rect* getRect();
private:
	float speed;
	SDL_Rect rect;

};