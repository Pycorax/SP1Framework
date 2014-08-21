#include "bullet.h"

Bullet::Bullet(Pacman player)
{
	damage = 1;
	speed = 1;
	direct = player.direct;
	coord = player.coord;
	oldCoord = coord;
	collided = false;
}

void Bullet::draw()
{
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

void Bullet::move(Map currentMap)
{
	oldCoord = coord;
	switch(direct)
	{
		case UP:
			coord.X += 0;
			coord.Y += -speed;
			break;
		case DOWN:
			coord.X += 0;
			coord.Y += speed;
			break;
		case LEFT:
			coord.X += -speed;
			coord.Y += 0;
			break;
		case RIGHT:
			coord.X += speed;
			coord.Y += 0;
			break;
	}
}
