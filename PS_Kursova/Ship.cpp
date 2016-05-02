#include "stdafx.h"
#include "Ship.h"


Ship::Ship()
{
}

Ship::Ship(const int& x,const int& y,const int &hp)
{
	posX = x;
	posY = y;
	health = hp;
}

void Ship::Move(const int& px)
{
	posX += px;
}

int Ship::GetX() const
{
	return posX;
}

void Ship::SetX(const int& x)
{
	posX = x;
}

int Ship::GetY() const
{
	return posY;
}

int Ship::GetHealth() const
{
	return health;
}

void Ship::AddHealth(const int& hp)
{
	health += hp;
}


Ship::~Ship()
{
	delete this;
}
