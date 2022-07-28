#include <iostream>
#include "Ground.h"
#include "game.h"

using namespace std;
using namespace sf;

void GroundTarget::setPosition(float posX, float posY)
{
	this->sprite.setPosition(posX, posY);
}