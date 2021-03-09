#include "Player.h"
#include <SDL.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>




Player::Player()
{
	maxHealth = 128;
	health = maxHealth;
	speed = 2;
	currentFrame = 0;
	rect = { 128, 160, 16, 32 };
	attackRect = { rect.x, rect.y, 32, 32 };
	swordRect = { rect.x + 24, rect.y + 8, 10, 8 };
	frameTimer.start();
	swordDamage = 64;
	state = STANDING_RIGHT;
	immuneState = 0;
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
	if (immuneState > 0)
	{
		(immuneState == 1) ? immuneState = 2 : immuneState = 1;
		if (immunityTimer.getTime() >= 1)
		{
			immuneState = 0;
		}
	}
}

void Player::moveLeft(float deltaTime)
{
	rect.x -= (int)(60.f * deltaTime) * speed;
	attackRect.x = rect.x - 18;
	swordRect.x = attackRect.x;
	if (state != MOVING_LEFT)
	{
		state = MOVING_LEFT;
		frameTimer.start();
		currentFrame = 3;
	}
	else if (frameTimer.getTime() > 0.2f)
	{
		frameTimer.start();
		(currentFrame == 2) ? currentFrame = 3 : currentFrame = 2;
	}

}

void Player::moveRight(float deltaTime)
{
	rect.x += (int)(60.f * deltaTime) * speed;
	attackRect.x = rect.x;
	swordRect.x = rect.x + 24;
	if (state != MOVING_RIGHT)
	{
		state = MOVING_RIGHT;
		frameTimer.start();
		currentFrame = 1;
	}
	else if (frameTimer.getTime() > 0.2f)
	{
		frameTimer.start();
		(currentFrame == 0) ? currentFrame = 1 : currentFrame = 0;
	}
}

int Player::attackSword()
{
	if (state == STANDING_RIGHT || state == MOVING_RIGHT)
	{
		state = ATTACKING_RIGHT;
		frameTimer.start();
		currentFrame = 4;
		return 1;
	}
	else if (state == STANDING_LEFT || state == MOVING_LEFT)
	{
		state = ATTACKING_LEFT;
		frameTimer.start();
		currentFrame = 5;
		return 2;
	}
	return 0;
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
	if (state == MOVING_RIGHT)
	{
		currentFrame = 0;
	}
	else if (state == MOVING_LEFT)
	{
		currentFrame = 2;
	}
	else if (state == AFTER_ATTACK_RIGHT)
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

SDL_Rect* Player::getSwordRect()
{
	return &swordRect;
}

int Player::getCurrentFrame()
{
	return currentFrame;
}

State Player::getState()
{
	return state;
}

int Player::getSwordDamage()
{
	return swordDamage;
}

void Player::takeDamage(int damage)
{
	if (immuneState == 0)
	{
		health -= damage;
		immuneState = 1;
		immunityTimer.start();
	}
	
}

int Player::getHealth()
{
	return health;
}

int Player::getMaxHealth()
{
	return maxHealth;
}


int Player::getImmunityState()
{
	return immuneState;
}

void Player::heal()
{
	sideEffect();
	health = maxHealth;
}

void Player::sideEffect()
{
	switch (rand() % 4)
	{
	case 0:
		maxHealth = std::max(32, maxHealth - 32);
		break;
	case 1:
		speed = 1;
		break;
	case 2:
		swordDamage = std::max(16, swordDamage - 16);
		break;
	default:
		break;
	}
}