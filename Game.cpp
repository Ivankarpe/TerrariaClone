#include "Game.h"

void Game::Innit()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();



	window = SDL_CreateWindow("Terraria", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CAMERA_WIDTH, CAMERA_HEIGHT, 0/*SDL_WINDOW_FULLSCREEN*/);

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
	heights[1] = heights[0];
	heights2[0] = rand() % 15 + 5;
	for (size_t x = 2; x < MAP_WIDTH; x++)//generate surface
	{
		int num = rand() % 3;
		if (num == 1) {
			heights[x] = heights[x - 1] + 1;
		}
		else if (num == 0)
		{
			heights[x] = heights[x - 1] - 1;
			if (heights[x] < 0) {
				heights[x] = 0;
			}
		}
		else {
			heights[x] = heights[x - 1];

		}


	}
	for (size_t x = 1; x < MAP_WIDTH - 1; x++)//generate surface
	{
		if (heights[x] > heights[x - 1] && heights[x] > heights[x + 1]) {
			heights[x]--;
		}
		if (heights[x] < heights[x - 1] && heights[x] < heights[x + 1]) {
			heights[x]++;
		}


	}
	cameraPos = { 0,heights[(CAMERA_WIDTH / 2) / BLOCK_SIZE] * BLOCK_SIZE - CAMERA_HEIGHT / 2 - 2 * BLOCK_SIZE };//set camera to the ground


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

	int VOID = 0;//
	int STONE = 1;
	int seed = time(NULL);
	int STONEProb = 55;
	srand(seed);

	for (int x = 0; x < MAP_WIDTH; x++) {//filling map with blocks
		for (int y = heights[x]; y < MAP_HEIGHT; y++) {
			if (y == heights[x]) {
				Map[y][x] = 3;
				int id_ground = rand() % 40;//add plants
				if (id_ground >= 0 && id_ground <= 3) Map[y - 1][x] = 12;
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
				if (id_ground >= 27 && id_ground <= 31 && x >= 3 && x <= MAP_WIDTH - 3) {
					int tree_height = rand() % 15 + 7;
					if (Map[y - 1][x - 1] != 20 && Map[y - 2][x - 1] != 20) {
						for (int i = y - 1; i >= y - tree_height; i--) {
							Map[i][x] = 20;
							if (i == y - tree_height) {
								for (int j = i - 1; j >= i - 5; j--) {
									for (int p = x - 2; p <= x + 2; p++) {
										if ((j == i - 1 && p == x - 2) || (j == i - 1 && p == x + 2) || (j == i - 5 && p == x - 2) || (j == i - 5 && p == x + 2) || (Map[j][p] == 20)) {
											continue;
										}
										Map[j][p] = 145;
									}
								}
							}
						}
					}

				}

				int lake_chance = rand() % 150;//add lakes
				if (lake_chance == 0 && x < MAP_HEIGHT - 5) {
					int tempie = y;
					for (int i = 0; i < 5; i++) {
						Map[tempie][x + i] = 205;

					}
				}
			}
			else if (y < heights[x] + heights2[x] + 5)
			{
				Map[y][x] = 2;
			}
			else//random spawm STONE and void
			{
				if (x == 0 || x == MAP_WIDTH) {
					Map[y][x] = 255;
				}
				else {
					Map[y][x] = 1;
					if (rand() % 100 > 58/*STONEProb*/) Map[y][x] = 0;
				}


			}


		}
	}

	for (int w = 1; w < MAP_WIDTH - 1; w++) {// grouping the STONE
		for (int h = heights[w]; h < MAP_HEIGHT - 1; h++) {
			int STONECounter = 0;

			for (int x = w - 1; x < w + 2; x++) {
				for (int y = h - 1; y < h + 2; y++) {
					if (!(x == w && y == h)) {
						STONECounter += Map[y][x];
					}
				}
			}

			if (Map[h][w] == VOID && STONECounter >= 6) Map[h][w] = STONE;
			if (Map[h][w] == STONE && STONECounter <= 3) Map[h][w] = VOID;
		}
	}


	for (int x = 1; x < MAP_WIDTH - 1; x++) {// ore generation
		for (int y = heights[x] + heights2[x] + 5; y < MAP_HEIGHT; y++) {
			int oreProb = rand() % 3000;

			//int orecount = 0;
			int defaultHeight = heights[x] + heights2[x];

			oreSpawn(rand() % 3000, x, y, heights, heights2, COAL_ORE, defaultHeight, coalOreChance);
			oreSpawn(rand() % 3000, x, y, heights, heights2, IRON_ORE, defaultHeight, ironOreChance);
			oreSpawn(rand() % 4000, x, y, heights, heights2, GOLD_ORE, goldOreHight, goldOreChance);
			oreSpawn(rand() % 6000, x, y, heights, heights2, DIAMOND_ORE, diamondOreHight, diamondOreChance);
			oreSpawn(rand() % 6000, x, y, heights, heights2, RUBY_ORE, rubyOreHight, rubyOreChance);
			oreSpawn(rand() % 6000, x, y, heights, heights2, SAPHIRE_ORE, saphireOreHight, saphireOreChance);

		}
	}
}

void Game::oreSpawn(int oreProb, int x, int y, int heights[MAP_WIDTH], int heights2[MAP_WIDTH], ItemsID oreID, const int oreSpawnHight, const int oreSpawnChance) {
	int oreType = static_cast<int>(oreID);
	int oreHight = oreSpawnHight;
	int oreChance = oreSpawnChance;
	if (oreProb >= 0 && oreProb <= 4 && x > 5 && x < (MAP_WIDTH - 5) && y < (MAP_HEIGHT - 5) && y >= oreHight) {
		for (int w = x - 2; w <= x + 2; w++) {
			for (int h = y - 2; h <= y + 2; h++) {
				if (rand() % 100 <= oreChance) Map[h][w] = oreType;
			}
		}


		for (int w = 1; w < MAP_WIDTH - 1; w++) {// grouping the ore
			for (int h = heights[w]; h < MAP_HEIGHT - 1; h++) {
				int coalCounter = 0;

				for (int p = w - 1; p < w + 2; p++) {
					for (int t = h - 1; t < h + 2; t++) {
						if (!(p == w && t == h) && (Map[t][p] == oreType)) {
							coalCounter++;
						}
					}
				}
				//SDL_Log("rockCounter = : (%d)", rockCounter);

				if (Map[h][w] == oreType && coalCounter <= 1) Map[h][w] = STONE;
				if (Map[h][w] == !oreType && coalCounter >= 5) Map[h][w] = oreType;
			}
		}
	}
}

void Game::Update()
{
	player.Update(Map);
}

void Game::on_left_click(SDL_Event event) {
	
	int mouseX, mouseY, distance;

	
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Log("left clicked in: (%d, %d)", mouseX, mouseY);
	mouseX += cameraPos.x - cameraPos.x / BLOCK_SIZE * BLOCK_SIZE;
	mouseY += cameraPos.y - cameraPos.y / BLOCK_SIZE * BLOCK_SIZE;

	distance = pow((mouseX - CAMERA_WIDTH / 2), 2) + pow((mouseY - CAMERA_HEIGHT / 2), 2);
	SDL_Log("dist: (%d)", distance);
	
	if (distance / BLOCK_SIZE <= 90000 / BLOCK_SIZE && Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] == 0) {
		int tem = inventory.Place();
		if (tem != 0) {
			Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] = tem;
		}
		
	}

}

void Game::on_right_click(SDL_Event event) {
	int mouseX, mouseY, distance;

	SDL_GetMouseState(&mouseX, &mouseY);
	mouseX += cameraPos.x - cameraPos.x / BLOCK_SIZE * BLOCK_SIZE;
	mouseY += cameraPos.y - cameraPos.y / BLOCK_SIZE * BLOCK_SIZE;
	SDL_Log("right clicked in: (%d, %d)", mouseX, mouseY);

	distance = pow(((player.GetPos().x - cameraPos.x - 16) - mouseX), 2) + pow(((player.GetPos().y - cameraPos.y - 16) - mouseY), 2);
	SDL_Log("dist: (%d)", distance);

	if (distance / BLOCK_SIZE <= 90000 / BLOCK_SIZE && Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] != 0) {
		inventory.PickUp({static_cast<ItemsID>(Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE]) , 1});
		Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] = 0;
	}
}

void Game::DrawMap(InfoForRender info) {
	
	int textureIndex;
	for (size_t i = info.Start; i < info.End; i++)//filling screen with blocks
	{
		for (size_t j = 0; j < CAMERA_HEIGHT / BLOCK_SIZE + 2; j++)
		{
			textureIndex = Map[info.firstPos.y + j][info.firstPos.x + i];

			SDL_Rect sours = { textureIndex % 16 * TEXTURE_SIZE ,textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };

			//SDL_Rect dest = { i * BLOCK_SIZE ,j * BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_Rect dest = { i * BLOCK_SIZE - info.dosPos.x,j * BLOCK_SIZE - info.dosPos.y,BLOCK_SIZE,BLOCK_SIZE };

			SDL_RenderCopy(renderer, texture, &sours, &dest);

		}
	}

}

void Game::Render()
{
	SDL_RenderClear(renderer);
	cameraPos.x = player.GetPos().x - CAMERA_WIDTH / 2;
	cameraPos.y = player.GetPos().y - CAMERA_HEIGHT / 2;

	if (cameraPos.x <=0)
	{
		cameraPos.x = 0;
	}
	if (cameraPos.y < 0)
	{
		cameraPos.y= 0;
	}
	if (cameraPos.x >= MAP_WIDTH*BLOCK_SIZE-CAMERA_WIDTH)
	{
		cameraPos.x = MAP_WIDTH * BLOCK_SIZE - CAMERA_WIDTH;
	}
	if (cameraPos.y >= MAP_HEIGHT * BLOCK_SIZE - CAMERA_HEIGHT)
	{
		cameraPos.y = MAP_HEIGHT * BLOCK_SIZE - CAMERA_HEIGHT;
	}
	Vector2 firstPos = { cameraPos.x / BLOCK_SIZE, cameraPos.y / BLOCK_SIZE};
	Vector2 dosPos = { cameraPos.x - firstPos.x*BLOCK_SIZE, cameraPos.y - firstPos.y*BLOCK_SIZE };
	InfoForRender info = { firstPos,dosPos,0,CAMERA_WIDTH / 2 + 1 };
	DrawMap(info);
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseX += dosPos.x;
	mouseY += dosPos.y;

	mouseX /= BLOCK_SIZE;
	mouseY /= BLOCK_SIZE;

	int textureIndex = 5;
	SDL_Rect sours = { textureIndex % 16 * TEXTURE_SIZE , textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
	SDL_Rect dest = { mouseX * BLOCK_SIZE - dosPos.x, mouseY * BLOCK_SIZE - dosPos.y, BLOCK_SIZE, BLOCK_SIZE };


	SDL_RenderCopy(renderer, texture, &sours, &dest);
	
	inventory.Render(renderer, texture);
	//dest = {player.GetPos().x -cameraPos.x-64, player.GetPos().y - cameraPos.y-64, 128, 128};
	//SDL_RenderCopy(renderer, hoe, NULL, &dest);
	SDL_Rect rect;
	rect.x = player.GetPos().x - cameraPos.x - 16;
	rect.y = player.GetPos().y - cameraPos.y - 16;
	rect.w = 32;
	rect.h = 32;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 10);
	SDL_RenderFillRect(renderer, &rect);

	TTF_Font* rFont = TTF_OpenFont("arial.ttf", 24);
	
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
		if(item.count != 0)SDL_RenderCopy(renderer, texture, &sours, &dest);

		SDL_Surface* textSurface = TTF_RenderText_Solid(rFont, std::to_string(item.count).c_str(), SDL_Color(20, 20, 20));

		SDL_Rect abcPosition = { i * BLOCK_SIZE + (i + 1) * 8 + 25, 48,textSurface->w,textSurface->h };

		SDL_Texture* mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_RenderCopy(renderer, mTexture, NULL, &abcPosition);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(mTexture);
	}
	TTF_CloseFont(rFont);



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
			case SDLK_SPACE:
				std::cout << "You Clicked \'space\'" << std::endl;
				butt.space = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				std::cout << "You upped \'space\'" << std::endl;
				butt.space = false;
				break;
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
	Vector2 dir = { 0,0 };
	if (butt.a && player.GetPos().x != 0) {
		dir.x -= 1;
	}
	if (butt.d && player.GetPos().x < MAP_WIDTH*BLOCK_SIZE) {
		dir.x += 1;
	}
	if (butt.space ) {
		player.Jump(Map);
	}
	player.Move(dir, Map);
	
}

void Game::Quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	running = false;
}
