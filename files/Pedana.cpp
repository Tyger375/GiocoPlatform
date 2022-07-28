#include <iostream>
#include "Game.h"
#include "Pedana.h"
#include "Ground.h"

using namespace std;
using namespace sf;

Pedana::Pedana(float Width, float Height, RenderWindow* window)
{
	this->AltezzaIniziale = Height;
	this->sprite.setSize(Vector2f(Width, Height));
	this->sprite.setFillColor(Color::Blue);
	this->Attivata = false;
	this->window = window;
}

void Pedana::setUpTarget(float WidthTarget, float HeightTarget, bool isGround, bool compare)
{
	if (isGround)
	{
		GroundTarget Target;
		Target.setUp(WidthTarget, HeightTarget);
		this->target = Target;
	}
	else
	{
		MuroTarget Target;
		Target.setUp(WidthTarget, HeightTarget);
		this->targetMuro = Target;
	}
	this->TargetCompare = compare;
	this->isGround = isGround;
}

void Pedana::setTargetPosition(float posX, float posY)
{
	if (this->isGround)
	{
		this->target.setPosition(posX, posY);
	}
	else
	{
		this->targetMuro.setPosition(posX, posY);
	}
}

void Pedana::renderTarget()
{
	//cout << "ciao" << endl;
	if (this->isGround)
	{
		if (!this->target.isNascosto())
		{
			//cout << this->target.getSprite().getPosition().x << endl;
			this->window->draw((this->target.getSprite()));
		}
	}
	else
	{
		if (!this->targetMuro.isNascosto())
		{
			//cout << this->target.getSprite().getPosition().x << endl;
			this->window->draw((this->targetMuro.getSprite()));
		}
	}
}

void Pedana::setActive()
{
	float Width = this->getSprite().getSize().x;
	float Height = this->AltezzaIniziale;
	float NuovaAltezza = (Height - (10.f));
	this->sprite.setSize(Vector2f(Width, NuovaAltezza));
	Vector2f pos = this->sprite.getPosition();
	float posX = pos.x;
	float posY = pos.y;
	this->sprite.setPosition(posX, (posY + NuovaAltezza));
	if (this->TargetCompare)
	{
		if (this->isGround)
		{
			this->target.Show();
		}
		else
		{
			this->targetMuro.Show();
		}
	}
	else
	{
		if (this->isGround)
		{
			this->target.Hide();
		}
		else
		{
			this->targetMuro.Hide();
		}
	}
	this->Attivata = true;
}

void Pedana::setNotActive()
{
	float Width = this->getSprite().getSize().x;
	this->setSize(Width, this->AltezzaIniziale);

	if (this->Attivata)
	{
		float NuovaAltezza = (this->AltezzaIniziale - (10.f));
		Vector2f pos = this->sprite.getPosition();
		float posX = pos.x;
		float posY = pos.y;
		this->sprite.setPosition(posX, (posY - NuovaAltezza));
	}
	if (this->TargetCompare)
	{
		if (this->isGround)
		{
			this->target.Hide();
		}
		else
		{
			this->targetMuro.Hide();
		}
	}
	else
	{
		if (this->isGround)
		{
			this->target.Show();
		}
		else
		{
			this->targetMuro.Show();
		}
	}
	this->Attivata = false;
}

void Pedana::setSize(float Width, float Height)
{
	this->sprite.setSize(Vector2f(Width, Height));
}

void Pedana::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}

void Pedana::ShowTarget()
{
	this->target.Show();
}

void Pedana::HideTarget()
{
	this->target.Hide();
}

void Game::updatePedana()
{
	for (int i = 0; i < this->Pedane.size(); i++)
	{
		Pedana pedana = this->Pedane[i];
	}
}

void Game::renderPedane()
{
	for (int i = 0; i < this->Pedane.size(); i++)
	{
		Pedana pedana = this->Pedane[i];
		pedana.renderTarget();
		this->window->draw(pedana.getSprite());
	}
}