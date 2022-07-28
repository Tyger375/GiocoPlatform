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

class Ground
{
private:
	RectangleShape sprite;
	bool hide;
public:
	Ground(float Width, float Height);
	RectangleShape getSprite() { return this->sprite; };
	//RectangleShape* getSpritePointer() { return &this->sprite; }
	inline void setTexture(Texture* texture) { this->sprite.setTexture(texture); }
	inline void setTextureRect(IntRect* ciao) { this->sprite.setTextureRect(*ciao); }
	void setPosition(float posX, float posY);
	void setColor(Color color) { this->sprite.setFillColor(color); };
	void Hide() { this->hide = true; };
	void Show() { this->hide = false; };
	bool isNascosto() { return this->hide; };
};

class GroundTarget
{
private:
	RectangleShape sprite;
	bool hide;
public:
	void setUp(float Width, float Height) { this->sprite.setSize(Vector2f(Width, Height)); }
	RectangleShape getSprite() { return this->sprite; };
	//RectangleShape* getSpritePointer() { return &this->sprite; }
	void setPosition(float posX, float posY);
	void setColor(Color color) { this->sprite.setFillColor(color); };
	void Hide() { this->hide = true; };
	void Show() { this->hide = false; };
	bool isNascosto() { return this->hide; };
};