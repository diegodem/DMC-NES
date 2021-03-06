#include "Kirzos.h"

Kirzos::Kirzos()
{
	initializeRect(250, 160);
	startFrameTimer();
}

void Kirzos::update(float deltaTime)
{

	moveRect((int)(100.f * deltaTime));
	if (getFrameTimer() > 0.2)
	{
		(getCurrentFrame() == 0) ? setCurrentFrame(1) : setCurrentFrame(0);
		startFrameTimer();
	}

}