// Code by Diego de Miguel (https://github.com/diegodem) - March 2021

#include "Unnath.h"
#include <cmath>

Unnath::Unnath()
{
	startFrameTimer();
	score = 15;
	if (rand() % 2 == 0)
	{
		initializeRect(256, 160);
		setFrames(4, 4);
		speed = 2;
	}
	else
	{
		initializeRect(-16, 160);
		setFrames(9, 9);
		speed = -2;
	}
}
