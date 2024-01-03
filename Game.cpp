#include "Game.h"

void Game::Innit()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Terraria", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CAMERA_WIDTH, CAMERA_HEIGHT, 0);

	renderer = SDL_CreateRenderer(window, 0, 0);
	running = true;
	SDL_Surface* temp = IMG_Load("d7aem.png");
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("klipartz.com.png");
	hoe = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	for (size_t i = 0; i < MAP_HEIGHT; i++)
	{
		Map.push_back(std::vector<int>(MAP_WIDTH));
	}

	srand(time(NULL));

	int heights[MAP_WIDTH];
	int heights2[MAP_WIDTH];
	heights[0] = rand() % 30 + 80;
	heights2[0] = rand() % 15 + 5;
	for (size_t x = 1; x < MAP_WIDTH; x++)//generate surface
	{
		int num = rand() % 3;
		if (num ==1) {
			heights[x] = heights[x - 1] + 1;

		}
		else if (num == 2) {
			heights[x] = heights[x - 1];
		
		}
		else
		{
			heights[x] = heights[x - 1] - 1;
			if (heights[x] < 0) {
				heights[x] = 0;
			}
		}

	}
	cameraPos = { 0,heights[(CAMERA_WIDTH / 2) / BLOCK_SIZE] * BLOCK_SIZE - CAMERA_HEIGHT / 2 - 2*BLOCK_SIZE };//set camera to the ground
	for (size_t x = 1; x < MAP_WIDTH; x++)//height of dirt layer
	{
		int num = rand() % 3;
		if (num == 1) {
			heights2[x] = heights2[x - 1] + 1;

		}
		else if (num == 2) {
			heights2[x] = heights2[x - 1];

		}
		else
		{
			heights2[x] = heights2[x - 1] - 1;
			if (heights2[x] < 0) {
				heights2[x] = 0;
			}
		}

	}
	for (int x = 0; x < MAP_WIDTH; x++) {//filling map with blocks
		int id_ground = rand() % 40;
		for (int y = heights[x]; y < MAP_HEIGHT; y++) {
			if (y == heights[x]) {
				Map[y][x] = 3;
				if (id_ground >= 0 && id_ground <= 3) Map[y - 1][x] = 12;//add plants
				if (id_ground >= 4 && id_ground <= 7) Map[y - 1][x] = 13;
				if (id_ground >= 10 && id_ground <= 11) Map[y - 1][x] = 88;
				if (id_ground >= 12 && id_ground <= 13) Map[y - 1][x] = 89;
				if (id_ground >= 14 && id_ground <= 15) Map[y - 1][x] = 90;
				if (id_ground >= 16 && id_ground <= 17) Map[y - 1][x] = 91;
				if (id_ground >= 18 && id_ground <= 19) Map[y - 1][x] = 92;
				if (id_ground >= 20 && id_ground <= 21) Map[y - 1][x] = 93;
				if (id_ground >= 22 && id_ground <= 23) Map[y - 1][x] = 94;
				if (id_ground >= 24 && id_ground <= 25) Map[y - 1][x] = 95;
				if (id_ground == 26) Map[y - 1][x] = 15;
				if (id_ground >= 27 && id_ground <= 31) {
					int tree_height = rand() % 15 + 7;
					if (Map[y - 1][x - 1] != 20 && Map[y - 2][x - 1] != 20) {
						for (int i = y - 1; i >= y - tree_height; i--) {
							Map[i][x] = 20;
							if (i == y - tree_height) {
									for (int j = i; j >= i - 4; j--) {
								for (int p = x - 2; p <= x + 2; p++) {
									if ((j == i && p == x - 2) || (j == i && p == x + 2) || (j == i - 4 && p == x - 2) || (j == i - 4 && p == x + 2) || (Map[j][p] == 20)) {
										continue;
									}
											Map[j][p] = 145;
										}
									}
								}
							}
						}

					}
				}
			
				else if (y < heights[x] + heights2[x] + 5)
				{
					Map[y][x] = 2;
				}
				else
				{
					Map[y][x] = 1;

				}
			int lake_chance = rand() % 150;

			}
		}
	}


void Game::Update()
{
}

void Game::on_left_click(SDL_Event event) {
	int mouseX, mouseY, distance;
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Log("left clicked in: (%d, %d)", mouseX, mouseY);
	
	distance = pow((mouseX - CAMERA_WIDTH / 2), 2) + pow((mouseY - CAMERA_HEIGHT / 2), 2);
	SDL_Log("dist: (%d)", distance);

	if (distance / BLOCK_SIZE <= 90000 / BLOCK_SIZE) {
		Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] = 0;
	}

}

void Game::on_right_click(SDL_Event event) {
	int mouseX, mouseY, distance;
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Log("right clicked in: (%d, %d)", mouseX, mouseY);

	distance = pow((CAMERA_WIDTH / 2 - mouseX), 2) + pow((CAMERA_HEIGHT / 2 - mouseY), 2);
	SDL_Log("dist: (%d)", distance);

	if (distance / BLOCK_SIZE <= 90000 / BLOCK_SIZE) {
		Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] = 1;
	}
}


void Game::Render()
{
	SDL_RenderClear(renderer);

	Vector2 firstPos = { cameraPos.x / BLOCK_SIZE,cameraPos.y / BLOCK_SIZE };

	int textureIndex = 1;
	for (size_t i = 0; i < CAMERA_WIDTH/BLOCK_SIZE; i++)//filling screen with blocks
	{
		for (size_t j = 0; j < CAMERA_HEIGHT / BLOCK_SIZE; j++)
		{
			textureIndex = Map[firstPos.y + j][firstPos.x + i];
			SDL_Rect sours = { textureIndex%16* TEXTURE_SIZE ,textureIndex/16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
			SDL_Rect dest = { i * BLOCK_SIZE,j * BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, texture, &sours, &dest);

		}
	}
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	mouseX /= BLOCK_SIZE;
	mouseY /= BLOCK_SIZE;

	textureIndex = 5;
	SDL_Rect sours = { textureIndex * TEXTURE_SIZE , textureIndex / 100 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
	SDL_Rect dest = { mouseX * BLOCK_SIZE, mouseY * BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
	SDL_RenderCopy(renderer, texture, &sours, &dest);//render coursor

	dest = {playerPos.x, playerPos.y, 128, 128};//set character position
	SDL_RenderCopy(renderer, hoe, NULL, &dest);
	SDL_RenderPresent(renderer);
}

void Game::Inputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			Quit();
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				on_left_click(event);
				break;
			case SDL_BUTTON_RIGHT:
				on_right_click(event);
				break;
			default:
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				Quit();
				break;
			case SDLK_w:
				std::cout << "You Clicked \'W\'" << std::endl;
				butt.w = true;
				break;
			case SDLK_s:
				std::cout << "You Clicked \'S\'" << std::endl;
				butt.s = true;
				break;
			case SDLK_a:
				std::cout << "You Clicked \'A\'" << std::endl;
				butt.a = true;
				break;
			case SDLK_d:
				std::cout << "You Clicked \'D\'" << std::endl;
				butt.d = true;
				break;			
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_w:
				std::cout << "You upped \'W\'" << std::endl;
				butt.w = false;
				break;
			case SDLK_s:
				std::cout << "You upped \'S\'" << std::endl;
				butt.s = false;
				break;
			case SDLK_a:
				std::cout << "You upped \'A\'" << std::endl;
				butt.a = false;
				break;
			case SDLK_d:
				std::cout << "You upped \'D\'" << std::endl;
				butt.d = false;
				break;
			}
			break;
		default:
			break;
		}

	}

	if (butt.w && cameraPos.y != 0){
		cameraPos.y -= 1;
	}
	if (butt.s && cameraPos.y < (MAP_HEIGHT - 52) * BLOCK_SIZE) {
		cameraPos.y += 1;
	}
	if (butt.a && cameraPos.x != 0) {
		cameraPos.x -= 1;
	}
	if (butt.d && cameraPos.x < (MAP_WIDTH - 65) * BLOCK_SIZE) {
		cameraPos.x += 1;
	}

	
}

void Game::Quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	running = false;
}
