#pragma once
class Enemy
{
private:
	int posX;
	int posY;
public:
	Enemy();
	Enemy(const int & x, const int & y);
	int GetX() const;
	int GetY() const;
	void Move();
	~Enemy();
};

