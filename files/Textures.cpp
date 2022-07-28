#include <iostream>

#include "game.h"

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

using namespace std;
using namespace sf;

void Game::loadTextures()
{
	cout << "loading texture" << endl;
	this->Background.setRepeated(true);
	this->Colonna.setRepeated(true);
	this->TextureMuroSpeciale.setRepeated(true);
	if (!this->Background.loadFromFile("Textures/Bricks.png", IntRect(0, 0, 128, 128))) {
		cout << "[GAME::TEXTURES::ERROR] FAILED LOADING TEXTURE (Textures/Bricks.png)" << endl;
	}
	else
	{
		this->background.setTexture(this->Background);
		this->background.setColor(Color(75, 75, 75, 255));
		this->background.setTextureRect({ 0, 0, this->Width, this->Height });
	}
	if (!this->Colonna.loadFromFile("Textures/BloccoColonna.png"))
	{
		cout << "[GAME::TEXTURES::ERROR] FAILED LOADING TEXTURE (Textures/BloccoColonna.png)" << endl;
	}
	if (!this->TerrenoLimit.loadFromFile("Textures/Terreno.png", IntRect(0, 0, 512, 32)))
	{
		cout << "[GAME::TEXTURES::ERROR] FAILED LOADING TEXTURE (Textures/Terreno.png)" << endl;
	}
	if (!this->Platform.loadFromFile("Textures/Platform.png", IntRect(0, 0, 256, 64)))
	{
		cout << "[GAME::TEXTURES::ERROR] FAILED LOADING TEXTURE (Textures/Platform.png)" << endl;
	}
	if (!this->TextureMuro.loadFromFile("Textures/Muro.png", IntRect(0, 0, 256, 64)))
	{
		cout << "[GAME::TEXTURES::ERROR] FAILED LOADING TEXTURE (Textures/Muro.png)" << endl;
	}
	if (!this->TextureMuroSpeciale.loadFromFile("Textures/MuroSpeciale.png", IntRect(0, 0, 64, 64)))
	{
		cout << "[GAME::TEXTURES::ERROR] FAILED LOADING TEXTURE (Textures/MuroSpeciale.png)" << endl;
	}
}