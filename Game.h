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

	void SetDeltaTime(Uint32 deltaTime);

	void oreSpawn(int oreChance, int x, int y, int heights[MAP_WIDTH], int heights2[MAP_WIDTH], ItemsID oreID, const int oreSpawnHight, const int oreSpawnChance);

	void caveSpawn(int x, int y, int caveChance, int caveMinAngle, int caveMaxAngle);

	void setGrass(int x, int y, int randomLeftDiagonalGrass, int randomRightDiagonalGrass, int randomsmoothGrass, int randomUnderLeftDiagonalGrass1);


	void DrawMap(InfoForRender info);

	void UpdateWater();


private:
	SDL_Window* window;

	SDL_Renderer* renderer;

	SDL_Texture* texture;

	SDL_Texture* grassTexture;

	SDL_Texture* hoe;

	SDL_Texture* tree_Top;

	bool running = false;
	
	std::vector<std::vector<block>> Map;

	Vector2 cameraPos = { CAMERA_HEIGHT,CAMERA_WIDTH };
	Player player;
	Vector2 playerPos = { CAMERA_WIDTH / 2 - 64, CAMERA_HEIGHT / 2 - 64 };

	Buttons butt = { 0, 0, 0, 0 };

	Inventory inventory;
	Uint32 deltaTime;

	Uint32 counter = 0;

};

