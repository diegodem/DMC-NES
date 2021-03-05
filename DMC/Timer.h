#pragma once


class Timer
{
public:
	void start();
	float getTime();
private:

	unsigned int previousTicks;
};