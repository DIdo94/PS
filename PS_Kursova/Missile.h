#pragma once
class Missile
{
private:
	int posX;
	int posY;
public:
	Missile();
	Missile(const int & x, const int & y);
	int GetX() const;
	int GetY() const;
	void Move();
	~Missile();
};

