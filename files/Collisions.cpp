#include <iostream>
#include "game.h"
#include "player.h"
#include "Ground.h"
#include "Muro.h"
#include "Pedana.h"

using namespace std;
using namespace sf;

bool Game::isCollidingWithGround(bool isPlayer1)
{
	Player* Player = &((isPlayer1) ? this->player : this->player2);
	bool GroundToccato = false;
	for (int i = 0; i < this->Terreni.size(); i++)
	{
		Ground terreno = this->Terreni[i];
		if (!terreno.isNascosto())
		{
			if (terreno.getSprite().getGlobalBounds().intersects(Player->getSprite().getGlobalBounds()))
			{
				//cout << terreno.getSprite().getPosition().y - (terreno.getSprite().getSize().y * 2.f - 10.f) << " " << this->player.getSprite().getPosition().y << endl;
				if ((terreno.getSprite().getPosition().y - (terreno.getSprite().getSize().y * 2.f - 20.f) > Player->getSprite().getPosition().y))
				{
					GroundToccato = true;
					break;
				}
				else
				{
					GroundToccato = false;
				}
			}
		}
	}
	return GroundToccato;
}
bool Game::isCollidingWithWall(bool* vieneDaSinistra, bool* GroundToccato, bool isPlayer1)
{
	Player* Player = &((isPlayer1) ? this->player : this->player2);
	bool MuroToccato = false;
	for (int i = 0; i < this->Muri.size(); i++)
	{
		Muro muro = this->Muri[i];
		if (muro.getSprite().getGlobalBounds().intersects(Player->getSprite().getGlobalBounds()))
		{
			float CheckAlto1 = muro.getSprite().getPosition().y + 15.f;
			float CheckAlto2 = Player->getSprite().getPosition().y + Player->getSprite().getSize().y;
			//cout << muro.getSprite().getPosition().y << " " << CheckAlto1 << " " << CheckAlto2 << endl;
			if (CheckAlto1 > CheckAlto2)
			{
				MuroToccato = false;
				*GroundToccato = true;
			}
			else
			{
				float PosMuroY = muro.getSprite().getPosition().y;
				float PosMuroX = muro.getSprite().getPosition().x;
				float SizeMuroY = muro.getSprite().getSize().y;
				float SizeMuroX = muro.getSprite().getSize().x;
				float PosPlayerY = Player->getSprite().getPosition().y;
				float PosPlayerX = Player->getSprite().getPosition().x;
				bool check1 = (((PosMuroX - (SizeMuroX / 2.f)) /** 2.f - 20.f*/) > PosPlayerX);
				bool check2 = ((PosMuroX - (SizeMuroX * 2.f)) < PosPlayerX);
				//cout << check1 << " " << check2 << endl;
				if (check1 && check2)
				{
					*vieneDaSinistra = true;
				}
				MuroToccato = true;
			}
			break;
		}
	}
	return MuroToccato;
}
void Game::CollidingWithPressurePlate()
{
	Player* Player1 = &(this->player);
	Player* Player2 = &(this->player2);
	bool PressurePlateToccata = false;
	for (int i = 0; i < this->Pedane.size(); i++)
	{
		Pedana* Pedana = &(this->Pedane[i]);
		bool CollisionWithPlayer1 = Pedana->getSprite().getGlobalBounds().intersects(Player1->getSprite().getGlobalBounds());
		bool CollisionWithPlayer2 = Pedana->getSprite().getGlobalBounds().intersects(Player2->getSprite().getGlobalBounds());
		if (CollisionWithPlayer1 || CollisionWithPlayer2)
		{
			if (!Pedana->isActive())
			{
				Pedana->setActive();
			}
		}
		else
		{
			Pedana->setNotActive();
		}
	}
	return;
}
bool Game::isCollidingWithTarget(bool isPlayer1)
{
	Player* player = &((isPlayer1) ? this->player : this->player2);
	bool Collision = false;
	for (int i = 0; i < this->Pedane.size(); i++)
	{
		Pedana pedana = this->Pedane[i];
		GroundTarget target = pedana.getTarget();
		if (!target.isNascosto())
		{
			bool CollisionWithPlayer = target.getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds());
			//cout << Collision << endl;
			if (CollisionWithPlayer)
			{
				if ((target.getSprite().getPosition().y - (target.getSprite().getSize().y * 2.f - 20.f) > player->getSprite().getPosition().y))
				{
					Collision = true;
					break;
				}
				else
				{
					Collision = false;
				}
			}
		}
	}
	return Collision;
}

bool Game::isCollidingWithTargetMuro(bool* VieneDaSinistra, bool* GroundToccato, bool isPlayer1)
{
	Player* Player = &((isPlayer1) ? this->player : this->player2);
	bool MuroToccato = false;
	for (int i = 0; i < this->Pedane.size(); i++)
	{
		Pedana pedana = this->Pedane[i];
		if (!pedana.isGround)
		{
			MuroTarget target = pedana.getTargetMuro();
			if (!target.isNascosto())
			{
				if (target.getSprite().getGlobalBounds().intersects(Player->getSprite().getGlobalBounds()))
				{
					float CheckAlto1 = target.getSprite().getPosition().y + 15.f;
					float CheckAlto2 = Player->getSprite().getPosition().y + Player->getSprite().getSize().y;
					//cout << muro.getSprite().getPosition().y << " " << CheckAlto1 << " " << CheckAlto2 << endl;
					if (CheckAlto1 > CheckAlto2)
					{
						MuroToccato = false;
						*GroundToccato = true;
					}
					else
					{
						float PosMuroY = target.getSprite().getPosition().y;
						float PosMuroX = target.getSprite().getPosition().x;
						float SizeMuroY = target.getSprite().getSize().y;
						float SizeMuroX = target.getSprite().getSize().x;
						float PosPlayerY = Player->getSprite().getPosition().y;
						float PosPlayerX = Player->getSprite().getPosition().x;
						bool check1 = (((PosMuroX - (SizeMuroX / 2.f)) /** 2.f - 20.f*/) > PosPlayerX);
						bool check2 = ((PosMuroX - (SizeMuroX * 2.f)) < PosPlayerX);
						//cout << check1 << " " << check2 << endl;
						if (check1 && check2)
						{
							*VieneDaSinistra = true;
						}
						MuroToccato = true;
					}
					break;
				}
			}
		}
	}
	return MuroToccato;
}

bool Game::isCollidingMovingPlatform(bool isPlayer1)
{
	Player* player = &((isPlayer1) ? this->player : this->player2);
	bool Collision = false;
	for (int i = 0; i < this->MovingPlatforms.size(); i++)
	{
		MovingPlatform platform = this->MovingPlatforms[i];
		if (!platform.isNascosto())
		{
			bool CollisionWithPlayer = platform.getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds());
			if (CollisionWithPlayer)
			{
				if ((platform.getSprite().getPosition().y - (platform.getSprite().getSize().y * 2.f - 20.f) > player->getSprite().getPosition().y))
				{
					Collision = true;
					break;
				}
				else
				{
					Collision = false;
				}
			}
		}
	}
	return Collision;
}

vector<float> Game::directionMovingPlatformCollision(bool isPlayer1)
{
	Player* player = &((isPlayer1) ? this->player : this->player2);
	bool Collision = false;
	float direction;
	float speed;
	float movingDirection;
	for (int i = 0; i < this->MovingPlatforms.size(); i++)
	{
		MovingPlatform platform = this->MovingPlatforms[i];
		if (!platform.isNascosto())
		{
			bool CollisionWithPlayer = platform.getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds());
			if (CollisionWithPlayer)
			{
				if ((platform.getSprite().getPosition().y - (platform.getSprite().getSize().y * 2.f - 20.f) > player->getSprite().getPosition().y))
				{
					Collision = true;
					direction = float(platform.getDirection());
					speed = platform.getSpeed();
					movingDirection = (platform.isMovingDirection()) ? 1 : 0;
					break;
				}
				else
				{
					Collision = false;
				}
			}
		}
	}
	vector<float> ciao;
	ciao.push_back(direction);
	ciao.push_back(speed);
	ciao.push_back(movingDirection);
	return ciao;
}

void Game::collidingWithEndPlatform()
{
	Player* Player1 = &this->player;
	Player* Player2 = &this->player2;

	bool PressurePlateToccata = false;
	for (int i = 0; i < 2; i++)
	{
		EndGamePlatform* Pedana = &(this->endgameplatforms[i]);
		bool CollisionWithPlayer1 = Pedana->getSprite().getGlobalBounds().intersects(Player1->getSprite().getGlobalBounds());
		bool CollisionWithPlayer2 = Pedana->getSprite().getGlobalBounds().intersects(Player2->getSprite().getGlobalBounds());
		if (CollisionWithPlayer1 || CollisionWithPlayer2)
		{
			if (!Pedana->isActive())
			{
				Pedana->setAttivata();
			}
		}
		else
		{
			Pedana->setDisattivata();
		}
	}
	return;
}

bool Game::isCollidingWithMuroSpeciale(bool* VieneDaSinistra, bool* GroundToccato, bool isPlayer1)
{
	Player* Player = &((isPlayer1) ? this->player : this->player2);
	bool MuroToccato = false;
	for (int i = 0; i < this->MuriSpeciali.size(); i++)
	{
		MuroSpeciale muro = this->MuriSpeciali[i];
		if (muro.getSprite().getGlobalBounds().intersects(Player->getSprite().getGlobalBounds()))
		{
			float CheckAlto1 = muro.getSprite().getPosition().y + 15.f;
			float CheckAlto2 = Player->getSprite().getPosition().y + Player->getSprite().getSize().y;
			//cout << muro.getSprite().getPosition().y << " " << CheckAlto1 << " " << CheckAlto2 << endl;
			if (CheckAlto1 > CheckAlto2)
			{
				/*MuroToccato = false;
				*GroundToccato = true;*/
			}
			else
			{
				float PosMuroY = muro.getSprite().getPosition().y;
				float PosMuroX = muro.getSprite().getPosition().x;
				float SizeMuroY = muro.getSprite().getSize().y;
				float SizeMuroX = muro.getSprite().getSize().x;
				float PosPlayerY = Player->getSprite().getPosition().y;
				float PosPlayerX = Player->getSprite().getPosition().x;
				bool check1 = (((PosMuroX - (SizeMuroX / 2.f)) /** 2.f - 20.f*/) > PosPlayerX);
				bool check2 = ((PosMuroX - (SizeMuroX * 2.f)) < PosPlayerX);
				//cout << check1 << " " << check2 << endl;
				if (check1 && check2)
				{
					*VieneDaSinistra = true;
				}
				MuroToccato = true;
			}
			break;
		}
	}
	return MuroToccato;
}