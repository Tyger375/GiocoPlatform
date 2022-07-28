#include <iostream>
#include "player.h"

using namespace std;
using namespace sf;

Player::Player()
{
	this->sprite.setSize(Vector2f(100.f, 100.f));
	this->sprite.setFillColor(Color::Red);
	this->speed = 5.f;
	this->Jumping = false;

	//Phisyc
	this->Gravity = 0.f;
	this->MaxGravity = 25.f;

	//Jump
	this->Jump = 10.f;
	this->MaxJump = 2.f;
	this->StaSalendo = false;
	this->timeJumping = 0;
}

void Player::fall()
{
	if (Gravity < MaxGravity)
	{
		Gravity += 0.45f;
	}
	this->move(0.f, Gravity);
}

void Player::jump()
{
	if (this->timeJumping < 30)
	{
		if (this->Jump > this->MaxJump)
		{
			this->Jump -= 0.3f;
		}
		this->move(0.f, -Jump);
		this->timeJumping++;
	}
	else
	{
		this->StaSalendo = false;
		this->Jumping = false;
		this->Jump = 10.f;
		this->timeJumping = 0;
		this->Gravity = 0.75f;
	}
}

void Player::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}