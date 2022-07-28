#include <iostream>
#include "Ground.h"
#include "game.h"

using namespace std;
using namespace sf;

Ground::Ground(float Width, float Height)
{
	this->sprite.setSize(Vector2f(Width, Height));
	this->sprite.setFillColor(Color::Green);
	this->hide = false;
}

void Ground::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}

void Game::renderTerreni()
{
	for (int i = 0; i < this->Terreni.size(); i++)
	{
		Ground terreno = this->Terreni[i];
		if (!terreno.isNascosto())
		{
			this->window->draw(terreno.getSprite());
		}
	}
	/*for (int i = 0; i < this->Targets.size(); i++)
	{
		Ground& terrenoTarget = *(this->Targets[i]);
		cout << "è nascosto: " << terrenoTarget.isNascosto() << endl;
		if (terrenoTarget.isNascosto())
		{
			cout << i << endl;
			RectangleShape* sprite = terrenoTarget.getSpritePointer();
			RectangleShape ciao = *sprite;
			this->window->draw(ciao);
		}
	}*/
}