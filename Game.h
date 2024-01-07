#pragma once

#include "Settings.h"
#include "Player.h"
#include "PerlinNoise.hpp"
#include "Inventory.h"
struct InfoForRender {
	Vector2 firstPos;
	Vector2 dosPos;
	int Start;
	int End;

};
class Game
{
public:
	
	Game(){}
	~Game(){}
	
	void Innit();

	void Update();

	void Render();

	void Inputs();

	void Quit();

	bool IsRunning() { return running; }

	void on_left_click(SDL_Event event);

	void on_right_click(SDL_Event event);

	void DrawMap(InfoForRender info);
private:
	SDL_Window* window;

	SDL_Renderer* renderer;

	SDL_Texture* texture;

	SDL_Texture* hoe;

	bool running = false;
	
	std::vector<std::vector<int>> Map;

	Vector2 cameraPos = { CAMERA_HEIGHT,CAMERA_WIDTH };
	Player player;
	Vector2 playerPos = { CAMERA_WIDTH / 2 - 64, CAMERA_HEIGHT / 2 - 64 };

	Buttons butt = { 0, 0, 0, 0 };

	Inventory inventory;

};

