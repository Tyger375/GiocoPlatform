#include <iostream>
#include "game.h"

using namespace std;
using namespace sf;

void Game::loadLimits()
{
	RenderWindow* window = this->window;
	vector<Ground>* Terreni = &this->Terreni;
	vector<Muro>* Muri = &this->Muri;
	Ground TerrenoSotto(window->getSize().x, 50.f);
	TerrenoSotto.setPosition(0, window->getSize().y - (TerrenoSotto.getSprite().getSize().y - 20.f));
	TerrenoSotto.setColor(Color::Cyan);
	TerrenoSotto.setTexture(&this->TerrenoLimit);
	Terreni->push_back(TerrenoSotto);

	Muro muroSinistra(64.f, window->getSize().y * 2);
	muroSinistra.setPosition(0, -(static_cast<float>(window->getSize().y)));
	muroSinistra.setColor(Color::Cyan);
	muroSinistra.setTexture(&this->Colonna);
	Muri->push_back(muroSinistra);

	Muro muroDestra(64.f, window->getSize().y * 2);
	muroDestra.setPosition(window->getSize().x - muroDestra.getSprite().getSize().x, -(static_cast<float>(window->getSize().y)));
	muroDestra.setColor(Color::Cyan);
	muroDestra.setTexture(&this->Colonna);
	
	//IntRect ciao(0, 0, 48, 48);
	//muroDestra.setTextureRect(&ciao);
	Muri->push_back(muroDestra);

	Muro muroTest(64.f, window->getSize().y * 2);
	muroTest.setPosition(window->getSize().x / 2.f, -(static_cast<float>(window->getSize().y)));
	muroTest.setColor(Color::Cyan);
	muroTest.setTexture(&this->Colonna);
	Muri->push_back(muroTest);
}

void Game::initLivello()
{
	switch (this->livello)
	{
	case 0:
		this->LevelTest();
		break;
	case 1:
		this->Livello1();
		break;
	case 2:
		this->Livello2();
		break;
	default:
		cout << "Error while loading level" << endl;
		break;
	}
}