#include <iostream>
#include "Muro.h"
#include "game.h"

using namespace std;
using namespace sf;

void MuroTarget::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}