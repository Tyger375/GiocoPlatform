#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "player.h"
#include "Ground.h"
#include "Muro.h"
#include "Pedana.h"
#include "MovingPlatform.h"
#include "EndGamePlatform.h"
#include "Multiplayer.h"
#include "MuroSpeciale.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;
using namespace sf;

class Game
{
private:
	int Width;
	int Height;
	int maxLevels;
	int livello;
	string title;
	VideoMode videomode;
	RenderWindow* window;
	Event event;

	bool isMultiplayer;
	Multiplayer multiplayer;
	bool isLatoSinistro;

	bool SpaceBarGi‡Premuta;
	bool EnterGi‡Premuto;

	void initVariables();
	void initWindow();

	vector<Ground> Terreni;
	vector<Ground*> Targets;
	vector<Muro> Muri;
	vector<Pedana> Pedane;
	vector<MovingPlatform> MovingPlatforms;
	vector<MuroSpeciale> MuriSpeciali;
	EndGamePlatform endgameplatforms[2] = { {0,0}, {0,0}};

	//Textures
	Texture Background;
	Texture Colonna;
	Texture TerrenoLimit;
	Texture Platform;
	Texture TextureMuro;
	Texture TextureMuroSpeciale;
	void loadTextures();

	//Levels
	void clearObjects();
	void LevelTest();
	void Livello1();
	void Livello2();
public:
	Player player;
	Player player2;
	int playerCorrente;

	Game();
	virtual ~Game();

	Sprite background;
	RectangleShape mask;

	Shader testShader;
	CircleShape testLight;

	const bool is_running() const;

	void loadLimits();
	void initLivello();
	void Movements(bool x1, bool MuroToccatoTarget, bool MuroSpecialeToccato, bool x2);

	//Multiplayer
	void updateMultiplayer();

	//Player1
	void updatePlayer();
	void renderPlayer();

	//Player2
	void updatePlayer2();
	void renderPlayer2();

	//Collisions
	bool isCollidingWithGround(bool isPlayer1);
	bool isCollidingWithWall(bool* VieneDaSinistra, bool* GroundToccato, bool isPlayer1);
	void CollidingWithPressurePlate();
	void collidingWithEndPlatform();
	bool isCollidingWithTarget(bool isPlayer1);
	bool isCollidingWithTargetMuro(bool* VieneDaSinistra, bool* GroundToccato, bool isPlayer1);
	bool isCollidingWithMuroSpeciale(bool* VieneDaSinistra, bool* GroundToccato, bool isPlayer1);
	bool isCollidingMovingPlatform(bool isPlayer1);
	vector<float> directionMovingPlatformCollision(bool isPlayer1);

	//Terreni
	//void loadTerreni();
	void renderTerreni();

	//Muri
	//void loadMuri();
	void renderMuri();

	//Pedane
	//void loadPedane();
	void renderPedane();
	void updatePedana();

	//Moving Platforms
	//void loadMovingPlatforms();
	void renderMovingPlatforms();
	void updateMovingPlatforms();

	//End Game Platforms
	//void loadEndGamePlatforms();
	void renderEndGamePlatforms();
	void updateEndGamePlatforms();

	//Muri Speciali
	//void loadMuriSpeciali();
	void renderMuriSpeciali();

	//Interni
	void pollEvents();

	void update();
	void render();
};