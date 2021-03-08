#include "Projectile.h"
#include <stdio.h>


Projectile::Projectile(int x, int direction)
{
	frame = direction;
	if (direction == 1)
	{
		speed = 2;
		rect = { x + 12, 168, 5, 4 };
	}
	else
	{
		rect = { x - 1, 168, 5, 4 };
		speed = - 2;
	}
	
}
void Projectile::update(float deltaTime)
{
	rect.x += (int)(60.f * deltaTime) * speed;
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