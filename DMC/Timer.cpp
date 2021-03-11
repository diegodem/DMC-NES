#include "Timer.h"
#include <SDL.h>



void Timer::start()
{
	previousTicks = SDL_GetTicks();
	return;
}

void Timer::updateDT()
{
	while (previousTicks + 17 <= SDL_GetTicks())
	{
		previousTicks += 17;
	}
}

float Timer::getTime()
{
	return (float)(SDL_GetTicks() - previousTicks) / 1000.f;
}