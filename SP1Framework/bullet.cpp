#include "bullet.h"

Bullet::Bullet(Pacman player)
{
	damage = 1;
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
		case UP:
			gotoXYTile(coord);
			cout << "/\\ ";
			gotoXYTileDown(coord, 1);
			cout << "/\\ ";
			gotoXYTileDown(coord, 2);
			cout << "|| ";
			break;

		case DOWN:	
				gotoXYTile(coord);
				cout << "|| ";
				gotoXYTileDown(coord, 1);
				cout << "\\/ ";
				gotoXYTileDown(coord, 2);
				cout << "\\/ ";
			break;

		case LEFT:
				gotoXYTile(coord);
				cout << "   ";
				gotoXYTileDown(coord, 1);
				cout << "<<=";
				gotoXYTileDown(coord, 2);
				cout << "   ";
			break;

		case RIGHT:	
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
		case UP:
			changeX += 0;
			changeY += -speed;
			break;
		case DOWN:
			changeX += 0;
			changeY += speed;
			break;
		case LEFT:
			changeX += -speed;
			changeY += 0;
			break;
		case RIGHT:
			changeX += speed;
			changeY += 0;
			break;
	}

	if(coord.X +changeX >= 0 && coord.X + changeX < currentMap.processedMap[coord.Y].size() && coord.Y + changeY >= 0 && coord.Y + changeY < currentMap.processedMap.size() && currentMap.processedMap[coord.Y + changeY][coord.X + changeX] != '#')
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
