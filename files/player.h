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

class Player
{
private:
	RectangleShape sprite;
	float MaxGravity;
	bool StaSalendo;
	float Jump;
	float MaxJump;
	int timeJumping;
public:
	float speed;
	bool Jumping;
	float Gravity;
	Player();
	RectangleShape getSprite() { return this->sprite; }
	void move(float x, float y)
	{
		this->sprite.move(x, y);
	}
	bool isJumping() { return this->Jumping; }
	void fall();
	void jump();
	void setPosition(float posX, float posY);
};