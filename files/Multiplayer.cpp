#include <iostream>
#include <SFML\Network.hpp>
#include "Multiplayer.h"
#include "game.h"
#include <codecvt>
#include <locale>
#include <string>
#include <cassert>

vector<string> ciao;

using namespace std;
using namespace sf;

float* split(string str, char seperator);

void Multiplayer::Start(bool* isLatoSinistro, string ip, int port)
{
	this->lastSentData = "";
	*this->lastPlayerPositionSent = { 0.f };
	//TcpSocket socket;
	//this->Socket = socket;
	Socket::Status status = this->Socket.connect(ip, port);
	char buffer[1000];
	size_t received;
	if (this->Socket.receive(buffer, sizeof(buffer), received) == Socket::Done)
	{
		cout << "connected to the server" << endl;
		string msg = buffer;
		try
		{
			cout << "IL MESSAGGIO: " << msg << endl;
			int player = stoi(msg);
			switch (player)
			{
			case 1:
				*isLatoSinistro = true;
				break;
			case 2:
				*isLatoSinistro = false;
				break;
			default:
				cout << "troppi player" << endl;
				break;
			}
		}
		catch (const std::exception&)
		{
			cout << "failed starting the game" << endl;
		}
	}
	else
	{
		cout << "failed connecting to the server" << endl;
	}
	this->Socket.setBlocking(false);
	/*if (this->Socket->bind(9000) != Socket::Done)
	{
		cout << "error" << endl;
	}*/
	//this->sendPos();
	//string text2 = "!DISCONNECT";
	//this->Socket->send(text2.c_str(), text2.length() + 1);
}
void Multiplayer::send()
{
	//string text = "poggers";
	string text = "poggers";
	cout << "sending: " << text << endl;
	this->Socket.send(text.c_str(), text.length() + 1);
	cout << "done" << endl;

	cout << "receiving data" << endl;

	char buffer[2000];
	size_t received;
	//this->Socket->receive(data, 64, received);
	this->Socket.receive(buffer, sizeof(buffer), received);
	//cout << "Received " << received << " bytes" << endl;
	//cout << "data = " << data << endl;

	//Packet packet;

	//packet >> data;

	//cout << data[0] << data[1] << data[2] << data[3] << endl;
	cout << "received: " << buffer << endl;
}

void Multiplayer::disconnect()
{
	string msg = "!DISCONNECT";
	size_t sent;
	this->Socket.send(msg.c_str(), msg.length() + 1, sent);
}

void Multiplayer::sendPos(Player* player)
{
	Vector2f pos = player->getSprite().getPosition();
	float posX = pos.x;
	float posY = pos.y;
	string text = to_string(posX) + " " + to_string(posY);
	size_t sent;
	//cout << "text: " << text << " lastSentData: " << this->lastSentData << endl;
	this->Socket.send(text.c_str(), text.length() + 1, sent);
	/*TcpSocket socket;
	this->Socket = &socket;
	Socket::Status status = this->Socket->connect("192.168.1.181", 9000);
	this->Socket->setBlocking(true);
	if (status != Socket::Done)
	{
		// error...
		cout << "error while connecting to server" << endl;
	}*/
	//cout << "Socket: " << &this->Socket << endl;
	//cout << "----------------------" << endl;
	//cout << "sending: " << text << endl;
	//Packet packet;
	//packet << text;
	//cout << this->lastSentData << endl;
	//cout << this->lastSentData << endl;
	//cout << "done" << endl;
	//cout << "----------------------" << endl;
	//cout << "receiving data" << endl;
	//char buffer[2000];
	//size_t received;
	//this->Socket->receive(data, 64, received);
	//this->Socket.receive(buffer, sizeof(buffer), received);
	//cout << "Received " << received << " bytes" << endl;
	//cout << "data = " << data << endl;

	//Packet packet;

	//packet >> data;

	//cout << data[0] << data[1] << data[2] << data[3] << endl;
	//cout << "received: " << buffer << endl;
	//this->Socket->disc();
	/*string text2 = "!DISCONNECT";
	this->Socket->send(text2.c_str(), text2.length() + 1);*/
}

void Multiplayer::updatePos(Player* player)
{
	char buffer[2000];
	size_t received;

	float ciao[2] = { this->lastPlayerPositionSent[0], this->lastPlayerPositionSent[1] };

	if (this->Socket.receive(buffer, sizeof(buffer), received) == Socket::Done)
	{
		string msg = buffer;
		/*cout << "---------------" << endl;
		cout << "msg: " << msg << endl;
		cout << "---------------" << endl;*/
		if (msg != "no data")
		{
			//cout << pog[0] << " " << pog[1] << endl;
			try
			{
				string word = "";
				int io = 0;
				float words[2] = { this->lastPlayerPositionSent[0], this->lastPlayerPositionSent[1] };
				string str = msg;
				try
				{
					for (int i = 0; i < str.length(); i++)
					{
						char pog = str[i];
						//cout << pog << endl;
						if (pog == ' ' || i == str.length() - 1)
						{
							if (pog == ' ') {
								words[io] = stof(word);
								word = "";
							}
							else
							{
								word += pog;
								words[io] = stof(word);
								word = "";
							}
							io++;
						}
						else
						{
							word += pog;
						}
					}
				}
				catch (const std::exception&)
				{
					//cout << "errore nella funzione split" << endl;
					words[0] = this->lastPlayerPositionSent[0];
					words[1] = this->lastPlayerPositionSent[1];
				}
				cout << "valori split: " << words[0] << " " << words[1] << endl;
				float posX = words[0];
				float posY = words[1];
				//cout << "pos: " << posX << " " << posY << endl;
				ciao[0] = posX;
				ciao[1] = posY;
				//cout << "ciao: " << ciao[0] << " " << ciao[1] << endl;
			}
			catch (const exception& i)
			{
				cout << "error while converting data:\n" << i.what() << endl;
			}
		}
	}
	cout << this->lastPlayerPositionSent[0] << endl << this->lastPlayerPositionSent[1] << endl;
	if (ciao[0] < 10)
	{
		ciao[0] = this->lastPlayerPositionSent[0];
	}
	if (ciao[1] < 10)
	{
		ciao[1] = this->lastPlayerPositionSent[1];
	}
	player->setPosition(ciao[0], ciao[1]);
	this->lastPlayerPositionSent[0] = ciao[0];
	this->lastPlayerPositionSent[1] = ciao[1];
	/*try
	{
		cout << "-------------" << endl;
		cout << ciao[0] << endl << ciao[1] << endl;
		cout << "-------------" << endl;
	}
	catch (const std::exception&)
	{
		cout << "error" << endl;
	}*/
	//return ciao;
	/*int mess;
	sf::Packet Packet;
	this->Socket.receive(Packet);
	Packet >> mess;
	cout << mess << endl;*/
	/*else
	{
		cout << "failed receiving data" << endl;
	}*/
}

void Game::updateMultiplayer()
{
	Vector2f pos = this->player.getSprite().getPosition();
	float posX = pos.x;
	float posY = pos.y;
	string text = to_string(posX) + " " + to_string(posY);
	if (text != this->multiplayer.lastSentData)
	{
		this->multiplayer.lastSentData = text;
		this->multiplayer.sendPos(&this->player);
	}
	this->multiplayer.updatePos(&this->player2);
	/*cout << Pos[0] << " " << Pos[1] << endl;
	//cout << this->multiplayer.lastPlayerPositionSent[0] << endl << this->multiplayer.lastPlayerPositionSent[1] << endl;
	try
	{
		this->player2.setPosition(Pos[0], Pos[1]);
	}
	catch (const exception&)
	{
		this->player2.setPosition(this->multiplayer.lastPlayerPositionSent[0], this->multiplayer.lastPlayerPositionSent[1]);
	}*/
}

float* split(string str, char seperator)
{
	string word = "";
	int io = 0;
	float words[2] = { 0.0, 0.0 };
	try
	{
		for (int i = 0; i < str.length(); i++)
		{
			char pog = str[i];
			//cout << pog << endl;
			if (pog == ' ' || i == str.length() - 1)
			{
				if (pog == ' ') {
					words[io] = stof(word);
					word = "";
				}
				else
				{
					word += pog;
					words[io] = stof(word);
					word = "";
				}
				io++;
			}
			else
			{
				word += pog;
			}
		}
	}
	catch (const std::exception&)
	{
		cout << "errore nella funzione split" << endl;
		words[0] = 0.0;
		words[1] = 0.0;
	}
	cout << "valori nella funzione split: " << words[0] << " " << words[1] << endl;
	return words;
}