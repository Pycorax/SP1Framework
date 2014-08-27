#include "bullet.h"
#include "Framework\console.h"
#include <iostream>

using std::cout;

Bullet::Bullet(Pacman player, int bulletDamage)
{
	damage = bulletDamage;
	speed = 1;
	direct = player.direct;
	coord = player.coord;
	oldCoord = coord;
	collided = false;
	firstMove = true;
}

void Bullet::draw()
{
	colour(FOREGROUND_RED | FOREGROUND_INTENSITY);

	switch(direct)
	{
		case E_UP_DIRECTION:
			gotoXYTile(coord);
			cout << "/\\ ";
			gotoXYTileDown(coord, 1);
			cout << "/\\ ";
			gotoXYTileDown(coord, 2);
			cout << "|| ";
			break;

		case E_DOWN_DIRECTION:	
				gotoXYTile(coord);
				cout << "|| ";
				gotoXYTileDown(coord, 1);
				cout << "\\/ ";
				gotoXYTileDown(coord, 2);
				cout << "\\/ ";
			break;

		case E_LEFT_DIRECTION:
				gotoXYTile(coord);
				cout << "   ";
				gotoXYTileDown(coord, 1);
				cout << "<<=";
				gotoXYTileDown(coord, 2);
				cout << "   ";
			break;

		case E_RIGHT_DIRECTION:	
				gotoXYTile(coord);
				cout << "   ";
				gotoXYTileDown(coord, 1);
				cout << "=>>";
				gotoXYTileDown(coord, 2);
				cout << "   ";
			break;
	}
}

void Bullet::undraw(Map currentMap)
{
	printTile(currentMap.processedMap[oldCoord.Y][oldCoord.X], oldCoord);
}

bool Bullet::move(Map currentMap)
{
	oldCoord = coord;
	short changeX = 0;
	short changeY = 0;

	switch(direct)
	{
		case E_UP_DIRECTION:
			changeX += 0;
			changeY += -speed;
			break;
		case E_DOWN_DIRECTION:
			changeX += 0;
			changeY += speed;
			break;
		case E_LEFT_DIRECTION:
			changeX += -speed;
			changeY += 0;
			break;
		case E_RIGHT_DIRECTION:
			changeX += speed;
			changeY += 0;
			break;
	}

	if(coord.X + changeX >= 0 && coord.X + changeX < currentMap.processedMap[coord.Y].size() && coord.Y + changeY >= 0 && coord.Y + changeY < currentMap.processedMap.size() && currentMap.processedMap[coord.Y + changeY][coord.X + changeX] != '#')
	{
		coord.X += changeX;
		coord.Y += changeY;
		
		return true;
	}
	else
	{
		return false;
	}
}
