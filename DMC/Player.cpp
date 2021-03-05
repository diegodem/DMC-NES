#include "Player.h"
#include <SDL.h>
#include <stdio.h>




Player::Player()
{
	currentFrame = 0;
	rect = { 10, 160, 16, 32 };
	attackRect = { rect.x, rect.y, 32, 32 };
	state = STANDING_RIGHT;
}

void Player::update()
{
	if (state == ATTACKING_RIGHT && frameTimer.getTime() > 0.2f)
	{
		state = AFTER_ATTACK_RIGHT;
		currentFrame = 0;
	}
	else if (state == ATTACKING_LEFT && frameTimer.getTime() > 0.2f)
	{
		state = AFTER_ATTACK_LEFT;
		currentFrame = 2;
	}
}

void Player::moveLeft(float deltaTime)
{
	rect.x -= (int)(100.f * deltaTime);
	attackRect.x = rect.x - 16;
	if (state != MOVING_LEFT)
	{
		state = MOVING_LEFT;
		frameTimer.start();
		currentFrame = 2;
	}
	else if (frameTimer.getTime() > 0.2)
	{
		frameTimer.start();
		(currentFrame == 2) ? currentFrame = 3 : currentFrame = 2;
	}

}

void Player::moveRight(float deltaTime)
{
	rect.x += (int)(100.f * deltaTime);
	attackRect.x = rect.x;
	if (state != MOVING_RIGHT)
	{
		state = MOVING_RIGHT;
		frameTimer.start();
		currentFrame = 0;
	}
	else if (frameTimer.getTime() > 0.2f)
	{
		frameTimer.start();
		(currentFrame == 0) ? currentFrame = 1 : currentFrame = 0;
	}
}

void Player::attackSword()
{
	if (state == STANDING_RIGHT || state == MOVING_RIGHT)
	{
		state = ATTACKING_RIGHT;
		frameTimer.start();
		currentFrame = 4;
	}
	else if (state == STANDING_LEFT || state == MOVING_LEFT)
	{
		state = ATTACKING_LEFT;
		frameTimer.start();
		currentFrame = 5;
	}
	

}

void Player::fire()
{
	if (state == STANDING_RIGHT || state == MOVING_RIGHT)
	{
		state = ATTACKING_RIGHT;
		frameTimer.start();
		currentFrame = 0;
	}
	else if (state == STANDING_LEFT || state == MOVING_LEFT)
	{
		state = ATTACKING_LEFT;
		frameTimer.start();
		currentFrame = 2;
	}
}

void Player::noButtonPressed()
{
	if (state == AFTER_ATTACK_RIGHT)
	{
		state = STANDING_RIGHT;
	}
	else if (state == AFTER_ATTACK_LEFT)
	{
		state = STANDING_LEFT;
	}
}

SDL_Rect* Player::getRect()
{
	return &rect;
}

SDL_Rect* Player::getAttackRect()
{
	return &attackRect;
}

int Player::getCurrentFrame()
{
	return currentFrame;
}