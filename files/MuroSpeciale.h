#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

using namespace std;
using namespace sf;

class MuroSpeciale
{
private:
	RectangleShape sprite;
public:
	MuroSpeciale(float Width, float Height);
	RectangleShape getSprite() { return this->sprite; }
	inline void setTexture(Texture* texture) { this->sprite.setTexture(texture); }
	inline void setTextureRect(IntRect* ciao) { this->sprite.setTextureRect(*ciao); }
	void setPosition(float posX, float posY);
	void setColor(Color color) { this->sprite.setFillColor(color); }
};