#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include "EndGamePlatform.h"
#include "game.h"

using namespace std;
using namespace sf;

EndGamePlatform::EndGamePlatform(float Width, float Height)
{
	this->AltezzaIniziale = Height;
	this->sprite.setSize(Vector2f(Width, Height));
	this->sprite.setFillColor(Color::Yellow);
}

void EndGamePlatform::setAttivata()
{
	float Width = this->getSprite().getSize().x;
	float Height = this->AltezzaIniziale;
	float NuovaAltezza = (Height - (10.f));
	this->sprite.setSize(Vector2f(Width, NuovaAltezza));
	Vector2f pos = this->sprite.getPosition();
	float posX = pos.x;
	float posY = pos.y;
	this->sprite.setPosition(posX, (posY + NuovaAltezza));
	this->Attivata = true;
}

void EndGamePlatform::setDisattivata()
{
	float Width = this->getSprite().getSize().x;
	this->sprite.setSize(Vector2f(Width, this->AltezzaIniziale));

	if (this->Attivata)
	{
		float NuovaAltezza = (this->AltezzaIniziale - (10.f));
		Vector2f pos = this->sprite.getPosition();
		float posX = pos.x;
		float posY = pos.y;
		this->sprite.setPosition(posX, (posY - NuovaAltezza));
	}
	this->Attivata = false;
}

void EndGamePlatform::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}

void Game::renderEndGamePlatforms()
{
	this->window->draw(this->endgameplatforms[0].getSprite());
	this->window->draw(this->endgameplatforms[1].getSprite());
}

void Game::updateEndGamePlatforms()
{
	EndGamePlatform* platform1 = &this->endgameplatforms[0];
	EndGamePlatform* platform2 = &this->endgameplatforms[1];

	if (platform1->isActive() && platform2->isActive())
	{
		cout << "livello finito" << endl;
		this->window->clear();
		this->clearObjects();
		if (this->livello < this->maxLevels)
		{
			this->livello++;
		}
		this->initLivello();
	}
}