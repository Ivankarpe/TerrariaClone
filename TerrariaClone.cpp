#include <iostream>
#include <SDL.h>
#include "Game.h"
#undef main

int main()
{

	Game* game = new Game;
	game->Innit();
	Uint64 start;
	Uint64 end;
	float elapsed= 0;
	float elapsedMS = 0;
	while (game->IsRunning()) {
		start = SDL_GetPerformanceCounter();
		game->Inputs();
		
		game->Update(elapsed);
		game->Render();
		end = SDL_GetPerformanceCounter();

		elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
		elapsedMS = elapsed * 1000.f;
		//SDL_Log("%d", elapsed);
		//SDL_Log("%d", elapsedMS);
		// Cap to 60 FPS
		SDL_Delay(floor(16.666f - elapsedMS));
	}
	return 0;
}

