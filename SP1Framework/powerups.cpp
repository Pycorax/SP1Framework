#include "powerups.h"
#include "Framework\console.h"
#include <iostream>
#include "maps.h"

using std::cout;

Power::Power(Pacman player)
{
	giveLife = 1;
	increaseDmg = 1;
	increasebulletSpeed = 3;
}

void Power::draw()
{
	colour(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}