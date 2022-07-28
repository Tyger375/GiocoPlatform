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

class Pedana
{
private:
	RectangleShape sprite;
	GroundTarget target;
	MuroTarget targetMuro;
	float AltezzaIniziale;
	bool Attivata;
	RenderWindow* window;
	bool TargetCompare;
public:
	bool isGround;
	void test();
	Pedana(float Width, float Height, RenderWindow* window);
	RectangleShape getSprite() { return this->sprite; }
	void setPosition(float posX, float posY);
	void setSize(float Width, float Height);
	void premuta();
	void setActive();
	void setNotActive();
	bool isActive() { return this->Attivata; }

	//Target
	void setUpTarget(float WidthTarget, float HeightTarget, bool isGround, bool comparire);
	void renderTarget();
	GroundTarget getTarget() { return this->target; }
	MuroTarget getTargetMuro() { return this->targetMuro; }
	void ShowTarget();
	void HideTarget();
	void setTargetPosition(float posX, float posY);
};