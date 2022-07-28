#include <iostream>
#include <vector>
#include "MovingPlatform.h"
#include "game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

MovingPlatform::MovingPlatform(float Width, float Height, int direction, float NumMovements, float speed)
{
	this->sprite.setSize(Vector2f(Width, Height));
	this->sprite.setFillColor(Color::Green);
	this->direction = direction;
	this->NumMovements = NumMovements;
	this->movingDirection = true;
	this->ActualMovement = 0.f;
	this->speed = speed;
	this->nascosto = false;
}

void MovingPlatform::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}

void MovingPlatform::update()
{
	int direction = this->direction;
	switch (direction)
	{
	case 1:
		this->MoveLeft();
		break;
	case 2:
		this->MoveRight();
		break;
	case 3:
		this->MoveUp();
		break;
	case 4:
		this->MoveDown();
		break;
	default:
		break;
	}
}

void MovingPlatform::MoveRight()
{
	Vector2f pos = this->sprite.getPosition();
	float posX = pos.x;
	float posY = pos.y;
	if (this->movingDirection)
	{
		if (this->NumMovements > this->ActualMovement)
		{
			this->ActualMovement = this->ActualMovement + 1;
			this->sprite.setPosition((posX - this->speed), posY);
		}
		else
		{
			this->movingDirection = false;
			this->ActualMovement = 0;
		}
	}
	else
	{
		if (this->NumMovements > this->ActualMovement)
		{
			this->ActualMovement++;
			this->sprite.setPosition((posX + this->speed), posY);
		}
		else
		{
			this->movingDirection = true;
			this->ActualMovement = 0;
		}
	}
}

void MovingPlatform::MoveUp()
{
	Vector2f pos = this->sprite.getPosition();
	float posX = pos.x;
	float posY = pos.y;
	if (this->movingDirection)
	{
		if (this->NumMovements > this->ActualMovement)
		{
			this->ActualMovement = this->ActualMovement + 1;
			this->sprite.setPosition(posX, (posY - this->speed));
		}
		else
		{
			this->movingDirection = false;
			this->ActualMovement = 0;
		}
	}
	else
	{
		if (this->NumMovements > this->ActualMovement)
		{
			this->ActualMovement++;
			this->sprite.setPosition(posX, (posY + this->speed));
		}
		else
		{
			this->movingDirection = true;
			this->ActualMovement = 0;
		}
	}
}

void MovingPlatform::MoveDown()
{
	Vector2f pos = this->sprite.getPosition();
	float posX = pos.x;
	float posY = pos.y;
	if (this->movingDirection)
	{
		if (this->NumMovements > this->ActualMovement)
		{
			this->ActualMovement = this->ActualMovement + 1;
			this->sprite.setPosition(posX, (posY + this->speed));
		}
		else
		{
			this->movingDirection = false;
			this->ActualMovement = 0;
		}
	}
	else
	{
		if (this->NumMovements > this->ActualMovement)
		{
			this->ActualMovement++;
			this->sprite.setPosition(posX, (posY - this->speed));
		}
		else
		{
			this->movingDirection = true;
			this->ActualMovement = 0;
		}
	}
}

void MovingPlatform::MoveLeft()
{
	Vector2f pos = this->sprite.getPosition();
	float posX = pos.x;
	float posY = pos.y;
	if (this->movingDirection)
	{
		if (this->NumMovements > this->ActualMovement)
		{
			this->ActualMovement = this->ActualMovement + 1;
			this->sprite.setPosition((posX + this->speed), posY);
		}
		else
		{
			this->movingDirection = false;
			this->ActualMovement = 0;
		}
	}
	else
	{
		if (this->NumMovements > this->ActualMovement)
		{
			this->ActualMovement++;
			this->sprite.setPosition((posX - this->speed), posY);
		}
		else
		{
			this->movingDirection = true;
			this->ActualMovement = 0;
		}
	}
}

void Game::updateMovingPlatforms()
{
	for (int i = 0; i < this->MovingPlatforms.size(); i++)
	{
		MovingPlatform* Platform = &this->MovingPlatforms[i];
		Platform->update();
	}
}

void Game::renderMovingPlatforms()
{
	for (int i = 0; i < this->MovingPlatforms.size(); i++)
	{
		MovingPlatform Platform = this->MovingPlatforms[i];
		this->window->draw(Platform.getSprite());
	}
}