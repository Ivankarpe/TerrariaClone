#include <iostream>
#include <SDL.h>
#include "Game.h"
#undef main

int main()
{

	Game* game = new Game;
	game->Innit();

	while (game->IsRunning()) {

		game->Inputs();
		game->Update();
		game->Render();
	}
	return 0;
}

