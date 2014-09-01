#include "bullet.h"
#include "Framework\console.h"
#include <iostream>

using std::cout;

Bullet::Bullet(Pacman player, int bulletDamage, int bulletSpeed)
{
	damage = bulletDamage;
	speed = bulletSpeed;
	direct = player.direct;
	coord = player.coord;
	oldCoord = coord;
	change.X = 0;
	change.Y = 0;
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
	printTile(currentMap.processedMap[oldCoord.Y][oldCoord.X], oldCoord, currentMap.colors);
}

bool Bullet::move(Map currentMap)
{
	oldCoord = coord;

	switch(direct)
	{
		case E_UP_DIRECTION:
			change.X = 0;
			change.Y = -1;
			break;
		case E_DOWN_DIRECTION:
			change.X = 0;
			change.Y = 1;
			break;
		case E_LEFT_DIRECTION:
			change.X = -1;
			change.Y = 0;
			break;
		case E_RIGHT_DIRECTION:
			change.X = 1;
			change.Y = 0;
			break;
	}

	bool canMove = true;
	bool moved = false;

	for(int position = 1; position <= speed && canMove; ++position)
	{
		if(coord.X + (change.X) >= 0 && coord.X + (change.X) < currentMap.processedMap[coord.Y].size() && coord.Y + (change.Y) >= 0 && coord.Y + (change.Y) < currentMap.processedMap.size() && currentMap.processedMap[coord.Y + (change.Y)][coord.X + (change.X)] != '#')
		{
			coord.X += change.X;
			coord.Y += change.Y;
			moved = true;
		}
		else
		{
			canMove = false;
		}
	}

	if (canMove)
	{
		return true;
	}
	else
	{
		return false;
	}
}
