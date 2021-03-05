#include "Timer.h"
#include <SDL.h>



void Timer::start()
{
	previousTicks = SDL_GetTicks();
	return;
}

float Timer::getTime()
{
	return (float)(SDL_GetTicks() - previousTicks) / 1000.f;
}