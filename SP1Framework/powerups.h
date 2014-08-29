#ifndef POWERUPS_H
#define POWERUPS_H

#include "bullet.h"

struct Power
{
	int giveLife;
	int increaseDmg;
	int increasebulletSpeed;
	int scoreMultiplier;
	
	Power(Pacman player);
	void draw();
	void undraw(Map currentMap);
};

#endif