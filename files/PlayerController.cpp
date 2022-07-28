#include <iostream>
#include "game.h"
#include "Ground.h"
#include "Muro.h"

using namespace std;
using namespace sf;

void Game::updatePlayer2()
{
	//cout << this->player.getSprite().getPosition().x << " " << this->player.getSprite().getPosition().y << endl;
	bool GroundToccato = this->isCollidingWithGround(false);
	bool GroundPedanaToccato = this->isCollidingWithTarget(false);
	bool vieneDaSinistra = false;
	bool MuroToccato = this->isCollidingWithWall(&vieneDaSinistra, &GroundToccato, false);
	bool MuroToccatoTarget = this->isCollidingWithTargetMuro(&vieneDaSinistra, &GroundToccato, false);
	bool MuroSpecialeToccato = this->isCollidingWithMuroSpeciale(&vieneDaSinistra, &GroundToccato, false);
	bool MovingPlatformToccata = this->isCollidingMovingPlatform(false);

	Vector2i mousePos = Mouse::getPosition(*this->window);
	bool ok = (mousePos.x >= 0) && (mousePos.y >= 0);
	bool ok2 = (mousePos.x <= this->Width) && (mousePos.y <= this->Height);
	bool ok3 = ok && ok2;

	if (MovingPlatformToccata)
	{
		vector<float> directionMovingPlatform = this->directionMovingPlatformCollision(false);
		switch ((int)directionMovingPlatform[0])
		{
		case 1:
			this->player.move((directionMovingPlatform[2] == 1) ? -directionMovingPlatform[1] : directionMovingPlatform[1], 0);
			break;
		case 2:
			this->player.move((directionMovingPlatform[2] == 1) ? directionMovingPlatform[1] : -directionMovingPlatform[1], 0);
			break;
		case 3:
			this->player2.move(0, directionMovingPlatform[1]);
			break;
		default:
			break;
		}
	}

	//this->CollidingWithPressurePlate(false);

	if (this->playerCorrente == 2)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space) && ok3)
		{
			if (!this->SpaceBarGiàPremuta && !this->player2.isJumping() && (GroundToccato || GroundPedanaToccato || MovingPlatformToccata || MuroSpecialeToccato))
			{
				this->SpaceBarGiàPremuta = true;
				this->player2.Jumping = true;
			}
		}
		else
		{
			if (!this->player2.isJumping())
			{
				this->SpaceBarGiàPremuta = false;
			}
		}
	}
	if (this->player2.isJumping())
	{
		this->player2.jump();
	}
	else if (GroundToccato || GroundPedanaToccato || MovingPlatformToccata)
	{
		this->player2.Gravity = 0.f;
	}
	else
	{
		this->player2.fall();
	}
	if (this->playerCorrente == 2)
	{
		Movements(MuroToccato, MuroToccatoTarget, MuroSpecialeToccato, vieneDaSinistra);
	}
}
void Game::updatePlayer()
{
	//cout << this->player.getSprite().getPosition().x << " " << this->player.getSprite().getPosition().y << endl;
	bool GroundToccato = this->isCollidingWithGround(true);
	bool GroundPedanaToccato = this->isCollidingWithTarget(true);
	bool vieneDaSinistra = false;
	bool MuroToccato = this->isCollidingWithWall(&vieneDaSinistra, &GroundToccato, true);
	bool MuroToccatoTarget = this->isCollidingWithTargetMuro(&vieneDaSinistra, &GroundToccato, true);
	bool MuroSpecialeToccato = this->isCollidingWithMuroSpeciale(&vieneDaSinistra, &GroundToccato, true);
	bool MovingPlatformToccata = this->isCollidingMovingPlatform(true);

	Vector2i mousePos = Mouse::getPosition(*this->window);
	bool ok = (mousePos.x >= 0) && (mousePos.y >= 0);
	bool ok2 = (mousePos.x <= this->Width) && (mousePos.y <= this->Height);
	bool ok3 = ok && ok2;

	if (MovingPlatformToccata)
	{
		vector<float> directionMovingPlatform = this->directionMovingPlatformCollision(true);
		switch ((int)directionMovingPlatform[0])
		{
		case 1:
			this->player.move((directionMovingPlatform[2] == 1) ? directionMovingPlatform[1] : -directionMovingPlatform[1], 0);
			break;
		case 2:
			this->player.move((directionMovingPlatform[2] == 1) ? -directionMovingPlatform[1] : directionMovingPlatform[1], 0);
			break;
		case 3:
			this->player.move(0, (directionMovingPlatform[2] == 1) ? -directionMovingPlatform[1] : directionMovingPlatform[1]);
			break;
		case 4:
			this->player.move(0, (directionMovingPlatform[2] == 1) ? directionMovingPlatform[1] : -directionMovingPlatform[1]);
			break;
		default:
			break;
		}
	}

	this->CollidingWithPressurePlate();
	this->collidingWithEndPlatform();

	if (this->playerCorrente == 1)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space) && ok3)
		{
			if (!this->SpaceBarGiàPremuta && !this->player.isJumping() && (GroundToccato || GroundPedanaToccato || MovingPlatformToccata || MuroSpecialeToccato))
			{
				this->SpaceBarGiàPremuta = true;
				this->player.Jumping = true;
			}
		}
		else
		{
			if (!this->player.isJumping())
			{
				this->SpaceBarGiàPremuta = false;
			}
		}
	}
	if (this->player.isJumping())
	{
		this->player.jump();
	}
	else if (GroundToccato || GroundPedanaToccato || MovingPlatformToccata)// || MuroToccato || MuroToccatoTarget)
	{
		this->player.Gravity = 0.f;
	}
	else
	{
		this->player.fall();
	}
	if (this->playerCorrente == 1)
	{
		this->Movements(MuroToccato, MuroToccatoTarget, MuroSpecialeToccato, vieneDaSinistra);
	}
}

void Game::Movements(bool MuroToccato, bool MuroToccatoTarget, bool MuroSpecialeToccato, bool vieneDaSinistra)
{
	Vector2i mousePos = Mouse::getPosition(*this->window);
	bool ok = (mousePos.x >= 0) && (mousePos.y >= 0);
	bool ok2 = (mousePos.x <= this->Width) && (mousePos.y <= this->Height);
	bool ok3 = ok && ok2;
	if (!ok3) return;
	if ((MuroToccato || MuroToccatoTarget || MuroSpecialeToccato))
	{
		if (vieneDaSinistra)
		{
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				if (this->playerCorrente == 1)
				{
					this->player.move(-this->player.speed, 0);
				}
				else
				{
					this->player2.move(-this->player2.speed, 0);
				}
			}
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				if (this->playerCorrente == 1)
				{
					this->player.move(this->player.speed, 0);
				}
				else
				{
					this->player2.move(this->player2.speed, 0);
				}
			}
		}
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			if (this->playerCorrente == 1)
			{
				this->player.move(this->player.speed, 0);
			}
			else
			{
				this->player2.move(this->player2.speed, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			if (this->playerCorrente == 1)
			{
				this->player.move(-this->player.speed, 0);
			}
			else
			{
				this->player2.move(-this->player2.speed, 0);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			if (this->playerCorrente == 1)
			{
				this->player.speed = 10.f;
			}
			else
			{
				this->player2.speed = 10.f;
			}
		}
		else
		{
			if (this->playerCorrente == 1)
			{
				this->player.speed = 5.f;
			}
			else
			{
				this->player2.speed = 5.f;
			}
		}
	}
}

void Game::renderPlayer()
{
	this->window->draw(this->player.getSprite());
	this->window->draw(this->player2.getSprite());
}