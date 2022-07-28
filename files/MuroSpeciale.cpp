#include <iostream>

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

#include "MuroSpeciale.h"
#include "game.h"

using namespace std;
using namespace sf;

MuroSpeciale::MuroSpeciale(float Width, float Height)
{
	this->sprite.setSize(Vector2f(Width, Height));
	this->sprite.setFillColor(Color(155, 0, 0, 255));
}

void MuroSpeciale::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}

/*void Game::loadMuriSpeciali()
{
	MuroSpeciale murotest(50.f, 200.f);
	murotest.setPosition(400.f, 350.f);
	this->MuriSpeciali.push_back(murotest);
}*/

void Game::renderMuriSpeciali()
{
	for (int i = 0; i < this->MuriSpeciali.size(); i++)
	{
		MuroSpeciale muro = this->MuriSpeciali[i];
		this->window->draw(muro.getSprite());
	}
}