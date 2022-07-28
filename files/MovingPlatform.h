#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class MovingPlatform
{
private:
	RectangleShape sprite;
	float direction;
	float NumMovements;
	float ActualMovement;
	bool movingDirection;
	float speed;
	bool nascosto;
public:
	/*
	* 1 = left
	* 2 = right
	* 3 = up
	* 4 = down
	*/
	bool isNascosto() { return this->nascosto; }
	MovingPlatform(float Width, float Height, int direction, float NumMovements, float speed);
	RectangleShape getSprite() { return this->sprite; }
	void setPosition(float posX, float posY);
	void update();
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	int getDirection() { return this->direction; }
	float getSpeed() { return this->speed; }
	bool isMovingDirection() { return this->movingDirection; }
};