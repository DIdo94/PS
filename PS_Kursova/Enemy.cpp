#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	posX = 0;
	posY = 0;
}

Enemy::Enemy(const int& x, const int& y)
{
	posX = x;
	posY = y;
}

int Enemy::GetX() const
{
	return posX;
}

int Enemy::GetY() const
{
	return posY;
}



void Enemy::Move()
{
	posY += 120;
}


Enemy::~Enemy()
{
	delete &posX;
	delete &posY;
}
