#include "game.h"

void Game::initVariables()
{
	this->Width = 1000;
	this->Height = 700;
	this->title = "Platform game";
	this->SpaceBarGi‡Premuta = false;
	this->EnterGi‡Premuto = false;
	cout << "livello: ";
	int lvl;
	cin >> lvl;
	this->maxLevels = 2;
	this->livello = lvl;
	//this->background.setSize(Vector2f(this->Width, this->Height));

	this->loadTextures();

	string msg = "";
	do
	{
		cout << "multiplayer? (s/n) ";
		cin >> msg;
	} while (msg != "s" && msg != "n");
	if (msg == "s")
	{
		this->isMultiplayer = true;
	}
	else
	{
		this->isMultiplayer = false;
	}
}

void Game::initWindow()
{
	if (this->isMultiplayer)
	{
		string ip;
		cout << "ip: ";
		cin >> ip;
		int port;
		cout << "port: ";
		cin >> port;
		this->multiplayer;// = multiplayer;
		this->multiplayer.Start(&this->isLatoSinistro, ip, port);
		//this->multiplayer.send();
		//this->updateMultiplayer();
	}
	this->videomode = VideoMode(Width, Height);
	this->window = new RenderWindow(this->videomode, this->title);

	this->window->setFramerateLimit(60);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->event.key.code == Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	Player player;
	Player player2;
	this->player = player;
	this->player2 = player2;
	this->playerCorrente = 1;
	this->initLivello();
	this->mask.setSize(Vector2f(this->Width, this->Height));
	this->mask.setFillColor(Color(0, 0, 0, 100));

	this->testLight.setRadius(50.f);
	this->testLight.setFillColor(Color(247, 255, 0, 100));
	this->testLight.setPosition(Vector2f(320.f, 320.f));

	//this->testShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag");
}

void Game::clearObjects()
{
	this->Terreni.clear();
	this->Muri.clear();
	this->Pedane.clear();
	this->Targets.clear();
	this->MovingPlatforms.clear();
	this->MuriSpeciali.clear();
}

Game::~Game()
{
	delete this->window;
	this->multiplayer.disconnect();
}

void Game::update()
{
	this->pollEvents();

	if (Keyboard::isKeyPressed(Keyboard::Enter) && !this->isMultiplayer)
	{
		if (!this->EnterGi‡Premuto)
		{
			this->EnterGi‡Premuto = true;
			if (this->playerCorrente == 1)
			{
				this->playerCorrente = 2;
			}
			else
			{
				this->playerCorrente = 1;
			}
		}
	}
	else
	{
		this->EnterGi‡Premuto = false;
	}

	this->updatePlayer();

	this->updatePlayer2();

	this->updateMovingPlatforms();

	this->updateEndGamePlatforms();

	if (this->isMultiplayer)
	{
		this->updateMultiplayer();
	}
}

void Game::render()
{
	this->window->clear();

	this->window->draw(this->background);

	//this->window->draw(this->testLight);

	this->renderPlayer();

	this->renderMuri();

	this->renderTerreni();

	this->renderPedane();

	this->renderMovingPlatforms();

	this->renderEndGamePlatforms();

	this->renderMuriSpeciali();

	this->window->draw(this->mask);

	this->window->display();
}

const bool Game::is_running() const
{
	return this->window->isOpen();
}