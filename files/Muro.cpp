#include <iostream>
#include "game.h"
#include "Muro.h"

using namespace std;
using namespace sf;

Muro::Muro(float Width, float Height)
{
	this->sprite.setSize(Vector2f(Width, Height));
	this->sprite.setFillColor(Color::Green);
}

void Muro::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}

void Game::renderMuri()
{
	for (int i = 0; i < this->Muri.size(); i++)
	{
		Muro muro = this->Muri[i];
		this->window->draw(muro.getSprite());
	}
}