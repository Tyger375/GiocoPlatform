#pragma once

#include <iostream>
#include <SFML\Network.hpp>
#include "player.h"

using namespace std;
using namespace sf;

class Multiplayer
{
private:

public:
	float lastPlayerPositionSent[2];
	string lastSentData;
	TcpSocket Socket;
	void Start(bool* isLatoSinistro, string ip, int port);
	void send();
	//const void start() const;
	void sendPos(Player* player);
	void updatePos(Player*);
	void disconnect();
};