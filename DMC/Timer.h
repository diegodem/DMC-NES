#pragma once


class Timer
{
public:
	void start();
	void updateDT();
	float getTime();
private:

	unsigned int previousTicks;
};