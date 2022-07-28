#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

using namespace std;
using namespace sf;

class EndGamePlatform
{
private:
	RectangleShape sprite;
	bool Attivata;
	float AltezzaIniziale;
public:
	bool isActive() { return this->Attivata; }
	void setAttivata();
	void setDisattivata();
	EndGamePlatform(float Width, float Height);
	void setPosition(float posX, float posY);
	RectangleShape getSprite() { return this->sprite; }
};