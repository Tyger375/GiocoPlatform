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

class Muro
{
private:
	RectangleShape sprite;
public:
	Muro(float Width, float Height);
	RectangleShape getSprite() { return this->sprite; }
	void setPosition(float posX, float posY);
	void setColor(Color color) { this->sprite.setFillColor(color); }
	inline void setTexture(Texture* texture) { this->sprite.setTexture(texture); }
	inline void setTextureRect(IntRect* ciao) { this->sprite.setTextureRect(*ciao); }

};

class MuroTarget
{
private:
	RectangleShape sprite;
	bool hide;
public:
	inline void setUp(float Width, float Height) { this->sprite.setSize(Vector2f(Width, Height)); }
	void setPosition(float posX, float posY);
	inline RectangleShape getSprite() { return this->sprite; };
	inline void setColor(Color color) { this->sprite.setFillColor(color); };
	inline void Hide() { this->hide = true; };
	inline void Show() { this->hide = false; };
	inline bool isNascosto() { return this->hide; };
	inline void setTexture(Texture* texture) { this->sprite.setTexture(texture); }
};