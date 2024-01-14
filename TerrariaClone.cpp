#include <iostream>
#include <SDL.h>
#include "Game.h"
#undef main

int main()
{

	Game* game = new Game;
	game->Innit();
	
	Uint32 a = SDL_GetTicks();
	Uint32 b = 0;
	Uint32 delta;
	while (game->IsRunning()) {
		a = SDL_GetTicks();
		delta = a - b;

		if (delta > 1000 / 165.f)
		{
			//std::cout << "fps: " << 1000 / delta << std::endl;
			b = a;
			game->SetDeltaTime(delta);
			game->Inputs();
			game->Update();
			game->Render();
		}

	}
	return 0;
}

