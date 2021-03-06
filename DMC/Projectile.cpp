#include "Projectile.h"
#include <stdio.h>


Projectile::Projectile(int x, int direction)
{
	frame = direction;
	if (direction == 1)
	{
		speed = 2;
		rect = { x + 11, 166, 8, 8 };
	}
	else
	{
		rect = { x - 3, 166, 8, 8 };
		speed = - 2;
	}
	
}
void Projectile::update(float deltaTime)
{
	rect.x += (int)(100.f * deltaTime) * speed;
}
Projectile *Projectile::getProjectile()
{
	return this;
}

SDL_Rect *Projectile::getRect()
{
	return &rect;
}

int Projectile::getFrame()
{
	return frame;
}