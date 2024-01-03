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
	heights[0] = rand() % 30 + 50;
	heights2[0] = rand() % 15 + 5;
	for (size_t x = 1; x < MAP_WIDTH; x++)
	{
		if (rand() % 3==1) {
			heights[x] = heights[x - 1] + 1;

		}
		else if (rand() % 3 == 1) {
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
	for (size_t x = 1; x < MAP_WIDTH; x++)
	{
		if (rand() % 3 == 1) {
			heights2[x] = heights2[x - 1] + 1;

		}
		else if (rand() % 3 == 1) {
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
	for (int x = 0; x < MAP_WIDTH; x++) {
		for (int y = heights[x]; y < MAP_HEIGHT; y++) {
			if (y == heights[x]) {
				Map[y][x] = 3;

			}
			else if (y < heights[x] + heights2[x]+5)
			{
				Map[y][x] = 2;
			}
			else
			{
				Map[y][x] = 1;
			}
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
		Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] = inventory.GetActiveSlotItem().ID;
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
	for (size_t i = 0; i < CAMERA_WIDTH/BLOCK_SIZE; i++)
	{
		for (size_t j = 0; j < CAMERA_HEIGHT / BLOCK_SIZE; j++)
		{
			textureIndex = Map[firstPos.y + j][firstPos.x + i];
			SDL_Rect sours = { textureIndex* TEXTURE_SIZE ,textureIndex/16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
			SDL_Rect dest = { i * BLOCK_SIZE,j * BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, texture, &sours, &dest);

		}
	}
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	mouseX /= BLOCK_SIZE;
	mouseY /= BLOCK_SIZE;

	textureIndex = 5;
	SDL_Rect sours = { textureIndex % 16 * TEXTURE_SIZE , textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
	SDL_Rect dest = { mouseX * BLOCK_SIZE, mouseY * BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
	SDL_RenderCopy(renderer, texture, &sours, &dest);
	
	SDL_Rect rect;
	rect.x = 25;
	rect.y = 25;
	rect.w = 408;
	rect.h = 48;

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 10);
	SDL_RenderFillRect(renderer, &rect);
	
	for (size_t i = 0; i < inventory.GetSize(); i++)
	{
		Item item = inventory.GetSlotItem(i);
		if (i == inventory.GetActiveSlotIndex()) {
			SDL_Rect rect;
			rect.x = i * BLOCK_SIZE + (i + 1) * 8 + 25-4;
			rect.y = 25 + 8-4;
			rect.w = 40;
			rect.h = 40;

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 10);
			SDL_RenderFillRect(renderer, &rect);
		}
		textureIndex = item.ID;
		SDL_Rect sours = { textureIndex % 16 * TEXTURE_SIZE , textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
		SDL_Rect dest = { i * BLOCK_SIZE + (i+1)*8+25, 25 + 8, BLOCK_SIZE, BLOCK_SIZE};
		SDL_RenderCopy(renderer, texture, &sours, &dest);
	}
	dest = {playerPos.x, playerPos.y, 128, 128};
	SDL_RenderCopy(renderer, hoe, NULL, &dest);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0) // scroll up
			{
				inventory.ChangeActiveSlot(inventory.GetActiveSlotIndex() + 1);
			}
			else if (event.wheel.y < 0) // scroll down
			{
				inventory.ChangeActiveSlot(inventory.GetActiveSlotIndex() - 1);
			}
			SDL_Log("%d", inventory.GetActiveSlotIndex());
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
