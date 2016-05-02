#include "stdafx.h"
#include "Missile.h"


Missile::Missile()
{
	posX = 0;
	posY = 0;
}

Missile::Missile(const int& x,const int& y)
{
	posX = x;
	posY = y;
}

int Missile::GetX() const
{
	return posX;
}

int Missile::GetY() const
{
	return posY;
}

void Missile::Move()
{
	if ((posY-10)>=0)
	{
		posY -= 30;
	}
	else
	{
		posY = -1;
	}	
}


Missile::~Missile()
{
	delete &posX;
	delete &posY;
}
