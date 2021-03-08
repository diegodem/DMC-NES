#include "Kirzos.h"

Kirzos::Kirzos()
{
	initializeRect(250, 160);
	startFrameTimer();
	setFrames(0, 1);
	speed = 1;
	health = 100;
}
