#include "Kirzos.h"
#include <cmath>

Kirzos::Kirzos()
{

	health = 100;
	startFrameTimer();
	if (rand() % 2 == 0)
	{
		initializeRect(256, 160);
		setFrames(0, 1);
		speed = 1;
	}
	else
	{
		initializeRect(-16, 160);
		setFrames(5, 6);
		speed = -1;
	}
}
