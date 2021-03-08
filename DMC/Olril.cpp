#include "Olril.h"

Olril::Olril()
{
	initializeRect(250, 160);
	startFrameTimer();
	setFrames(2, 3);
	health = 200;
	speed = 1;
}
