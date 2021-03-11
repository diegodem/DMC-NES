// Code by Diego de Miguel (https://github.com/diegodem) - March 2021

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