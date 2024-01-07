#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <iostream>
#include "Settings.h"
#include "Player.h"
#include "PerlinNoise.hpp"
#include "Inventory.h"

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

	void oreSpawn(int oreChance, int x, int y, int heights[MAP_WIDTH], int heights2[MAP_WIDTH], ItemsID oreID, const int oreSpawnHight, const int oreSpawnChance);
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

