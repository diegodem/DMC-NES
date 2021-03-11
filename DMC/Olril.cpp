// Code by Diego de Miguel (https://github.com/diegodem) - March 2021

#include "Olril.h"
#include <cmath>

Olril::Olril()
{
	health = 128;
	startFrameTimer();
	if (rand() % 2 == 0)
	{
		initializeRect(256, 160);
		setFrames(2, 3);
		speed = 1;
	}
	else
	{
		initializeRect(-16, 160);
		setFrames(7, 8);
		speed = -1;
	}
	
}
