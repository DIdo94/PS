#pragma once
class Ship
{
private:
	int posX;
	int posY;
	int health;
public:
	Ship();
	Ship(const int & x, const int & y, const int & hp);
	void Move(const int & px);
	int GetX() const;
	void SetX(const int & x);
	int GetY() const;
	int GetHealth() const;
	void AddHealth(const int & hp);
	~Ship();
};

