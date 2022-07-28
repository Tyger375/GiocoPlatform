#include <iostream>
#include "game.h"

using namespace std;

int main()
{
	Game game;
	while (game.is_running())
	{
		game.update();
		
		game.render();
	}
	return 0;
}