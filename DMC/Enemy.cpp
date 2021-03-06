#include "Enemy.h"


SDL_Rect* Enemy::getRect()
{
	return &rect;
}

void Enemy::initializeRect(int x, int y)
{
	rect = { x, y, 16, 32 };
}


void Enemy::startFrameTimer()
{
	frameTimer.start();
}

float Enemy::getFrameTimer()
{
	return frameTimer.getTime();
}

int Enemy::getCurrentFrame()
{
	return currentFrame;
}

void Enemy::moveRect(int x)
{
	rect.x -= x;
}

void Enemy::setCurrentFrame(int frame)
{
	currentFrame = frame;
}

void Enemy::update(float deltaTime)
{

	moveRect((int)(100.f * deltaTime));
	if (getFrameTimer() > 0.2)
	{
		(getCurrentFrame() == 0) ? setCurrentFrame(1) : setCurrentFrame(0);
		startFrameTimer();
	}

}