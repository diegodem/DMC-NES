// Code by Diego de Miguel (https://github.com/diegodem) - March 2021

#pragma once
#include <SDL.h>

class Projectile
{
public:
	Projectile(int x, int direction);
	void update(float deltaTime);
	SDL_Rect* getRect();
	Projectile* getProjectile();
	int getFrame();
private:
	int speed;
	int frame;
	SDL_Rect rect;

};