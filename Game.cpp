#include "Game.h"

void Game::Innit()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();



	if (FULLSCREEN == 1) {
		window = SDL_CreateWindow("Terraria", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CAMERA_WIDTH, CAMERA_HEIGHT, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		window = SDL_CreateWindow("Terraria", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CAMERA_WIDTH, CAMERA_HEIGHT, 0);
	}


	renderer = SDL_CreateRenderer(window, 0, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	running = true;
	SDL_Surface* temp = IMG_Load("d7aem.png");
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("klipartz.com.png");
	hoe = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	for (size_t i = 0; i < MAP_HEIGHT; i++)
	{
		Map.push_back(std::vector<block>(MAP_WIDTH));
	}
	for (int x = 0; x < MAP_WIDTH; x++) {//filling map with blocks
		for (int y = 0; y < MAP_HEIGHT; y++) {
			Map[y][x] = { NONE, 0 };
		}
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

	for (int x = 1; x < MAP_WIDTH - 1; x++) {
		if (int lakeChance = rand() % 2 == 0) {
			int w = x;
			int h = heights[w];
			int maxSize = 40;
			int size = 0;
			while (h + 1 <= heights[x + size + 1]) {
				size++;
				if (size > maxSize) {
					break;
				}
			}
			if (size > 10 && size <= maxSize) {
				for (int i = 0; i <= size; i++) {
					//while (h < heights[w + 1]) {
						//w++;
					for (int h2 = h; h2 < heights[x + i]; h2++) {

						Map[h2][x + i].area = WATERCAPACITY;
					}
				}
			SDL_Log("size, x: (%d, %d)", size, x);
			player.cord = { 100, (float)(x ) };
			}
		}
	}


	//int VOID = 0;
	//int STONE = 1;
	int seed = time(NULL);
	int STONEProb = 65;
	srand(seed);
	for (int x = 0; x < MAP_WIDTH; x++) {//filling map with blocks
		for (int y = heights[x]; y < MAP_HEIGHT; y++) {
			if (y == heights[x]) {
				Map[y][x] = { GRASS, 1 };
				if (Map[y - 1][x].area == 0) {
					int id_ground = rand() % 40;//add plants
					if (id_ground >= 0 && id_ground <= 3) Map[y - 1][x] = { static_cast<ItemsID>(12), 0 };
					if (id_ground >= 4 && id_ground <= 7) Map[y - 1][x] = { static_cast<ItemsID>(13), 0 };
					if (id_ground >= 10 && id_ground <= 11) Map[y - 1][x] = { static_cast<ItemsID>(88), 0 };
					if (id_ground >= 12 && id_ground <= 13) Map[y - 1][x] = { static_cast<ItemsID>(89), 0 };
					if (id_ground >= 14 && id_ground <= 15) Map[y - 1][x] = { static_cast<ItemsID>(90), 0 };
					if (id_ground >= 16 && id_ground <= 17) Map[y - 1][x] = { static_cast<ItemsID>(91), 0 };
					if (id_ground >= 18 && id_ground <= 19) Map[y - 1][x] = { static_cast<ItemsID>(92), 0 };
					if (id_ground >= 20 && id_ground <= 21) Map[y - 1][x] = { static_cast<ItemsID>(93), 0 };
					if (id_ground >= 22 && id_ground <= 23) Map[y - 1][x] = { static_cast<ItemsID>(94), 0 };
					if (id_ground >= 24 && id_ground <= 25) Map[y - 1][x] = { static_cast<ItemsID>(95), 0 };
					if (id_ground == 26) Map[y - 1][x] = { static_cast<ItemsID>(15), 0 };
					if (id_ground >= 27 && id_ground <= 31 && x >= 3 && x <= MAP_WIDTH - 3) {
						int tree_height = rand() % 15 + 7;
						if (Map[y - 1][x - 1].ID != WOOD && Map[y - 2][x - 1].ID != WOOD) {
							for (int i = y - 1; i >= y - tree_height; i--) {
								Map[i][x] = { WOOD, 0 };
								if (i == y - tree_height) {
									for (int j = i - 1; j >= i - 5; j--) {
										for (int p = x - 2; p <= x + 2; p++) {
											if ((j == i - 1 && p == x - 2) || (j == i - 1 && p == x + 2) || (j == i - 5 && p == x - 2) || (j == i - 5 && p == x + 2) || (Map[j][p].ID == WOOD)) {
												continue;
											}
											Map[j][p] = { LEAF, 0 };
										}
									}
								}
							}
						}

					}
				}
			}
			else if (y < heights[x] + heights2[x] + 5)
			{
				Map[y][x] = { DIRT,1 };
			}
			else//random spawm STONE and void
			{
				if (x == 0 || x == MAP_WIDTH) {
					Map[y][x] = { NONE, 0 };
				}
				else {
					Map[y][x] = { STONE, 1 };
					if (rand() % 100 > STONEProb) Map[y][x] = { NONE, 0 };
				}


			}


		}
	}


	for (int x = 0; x < MAP_WIDTH; x++) {//filling map with blocks
		for (int y = 0; y < heights[x]+1; y++) {
			if (!Map[y][x].colideable) {
				Map[y][x].lightSource = true;
  		}
    }
  }
	for (int x = 0; x < MAP_WIDTH - 0; ++x) {
		for (int y = 0 + heights[x] + heights2[x]; y < MAP_HEIGHT - 0; ++y) {
			caveSpawn(x, y, heights, heights2, 2500, 5, 80);
			caveSpawn(x, y, heights, heights2, 2500, 105, 175);

		}
	}

	for (int w = 1; w < MAP_WIDTH - 1; w++) {// grouping the STONE
		for (int h = heights[w]; h < MAP_HEIGHT - 1; h++) {
			int STONECounter = 0;

			for (int x = w - 1; x < w + 2; x++) {
				for (int y = h - 1; y < h + 2; y++) {
					if (!(x == w && y == h)) {
						if(Map[y][x].ID == STONE)
						STONECounter ++;
					}
				}
			}

			if (Map[h][w].ID == NONE && STONECounter >= 6) Map[h][w] = { STONE, 1 };
			if (Map[h][w].ID == STONE && STONECounter <= 3) Map[h][w] = { NONE, 0 };
		}
	}

	

	for (int x = 1; x < MAP_WIDTH - 1; x++) {// ore generation
		for (int y = heights[x] + heights2[x] + 5; y < MAP_HEIGHT; y++) {
			//int oreProb = rand() % 3000;

			//int orecount = 0;
			int defaultHeight = heights[x] + heights2[x];

			/*oreSpawn(rand() % 3000, x, y, heights, heights2, COAL_ORE, defaultHeight, coalOreChance);
			oreSpawn(rand() % 3000, x, y, heights, heights2, IRON_ORE, defaultHeight, ironOreChance);
			oreSpawn(rand() % 4000, x, y, heights, heights2, GOLD_ORE, goldOreHight, goldOreChance);
			oreSpawn(rand() % 6000, x, y, heights, heights2, DIAMOND_ORE, diamondOreHight, diamondOreChance);
			oreSpawn(rand() % 6000, x, y, heights, heights2, RUBY_ORE, rubyOreHight, rubyOreChance);
			oreSpawn(rand() % 6000, x, y, heights, heights2, SAPHIRE_ORE, saphireOreHight, saphireOreChance);*/
		}
	}

	UpdateLight();
}

void Game::oreSpawn(int oreProb, int x, int y, int heights[MAP_WIDTH], int heights2[MAP_WIDTH], ItemsID oreID, const int oreSpawnHight, const int oreSpawnChance) {
	int oreHight = oreSpawnHight;
	int oreChance = oreSpawnChance;
	if (oreProb >= 0 && oreProb <= 4 && x > 5 && x < (MAP_WIDTH - 5) && y < (MAP_HEIGHT - 5) && y >= oreHight) {
		for (int w = x - 2; w <= x + 2; w++) {
			for (int h = y - 2; h <= y + 2; h++) {
				if (rand() % 100 <= oreChance) Map[h][w] = { oreID, 1 };
			}
		}


		for (int w = 1; w < MAP_WIDTH - 1; w++) {// grouping the ore
			for (int h = heights[w]; h < MAP_HEIGHT - 1; h++) {
				int coalCounter = 0;

				for (int p = w - 1; p < w + 2; p++) {
					for (int t = h - 1; t < h + 2; t++) {
						if (!(p == w && t == h) && (Map[t][p].ID == oreID)) {
							coalCounter++;
						}
					}
				}
				//SDL_Log("rockCounter = : (%d)", rockCounter);

				if (Map[h][w].ID == oreID && coalCounter <= 2) Map[h][w] = { STONE, 1 };
				if (Map[h][w].ID != oreID && coalCounter >= 5) Map[h][w] = { oreID, 1 };
			}
		}
	}
}

void Game::caveSpawn(int x, int y, int heights[MAP_WIDTH], int heights2[MAP_WIDTH], int caveChance, int caveMinAngle, int caveMaxAngle) {
	if (rand() % caveChance == 0) {
		int randomAngle = rand() % caveMaxAngle;
		int caveSize = rand() % 70 + 30;
		if (randomAngle >= caveMinAngle) {

			int randomX = x + static_cast<int>(caveSize * std::cos(randomAngle * 3.14159 / 180));
			int randomY = y + static_cast<int>(caveSize * std::sin(randomAngle * 3.14159 / 180));

			double distance = std::sqrt(std::pow(x - randomX, 2) + std::pow(y - randomY, 2));
			int deltaX = randomX - x;
			int deltaY = randomY - y;
			int steps = std::max(std::abs(deltaX), std::abs(deltaY));


			for (int step = 0; step <= steps; step++) {
				int pathWidth = rand() % 2 + 1;
				int currentX = x + step * deltaX / steps;
				int currentY = y + step * deltaY / steps;

				for (int i = -pathWidth / 2; i <= pathWidth / 2; ++i) {
					for (int j = -pathWidth / 2; j <= pathWidth / 2; ++j) {
						int sideX = currentX + i;
						int sideY = currentY + j;

						if (sideX >= 0 && sideX < MAP_WIDTH && sideY >= 0 && sideY < MAP_HEIGHT) {
							Map[sideY][sideX] = { NONE, 0 };
						}
					}
				}
			}
		}
	}
}

void Game::Update()
{
	player.Update(deltaTime, Map);


	counter+= deltaTime;
	while (counter > 50) {
	UpdateWater();
	counter -= 50;
	}


}

void Game::on_left_click(SDL_Event event) {

	int mouseX, mouseY, distance;
	
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Log("left clicked in: (%d, %d)", mouseX, mouseY);
	mouseX += cameraPos.x - cameraPos.x / BLOCK_SIZE * BLOCK_SIZE;
	mouseY += cameraPos.y - cameraPos.y / BLOCK_SIZE * BLOCK_SIZE;

	distance = pow((mouseX - CAMERA_WIDTH / 2), 2) + pow((mouseY - CAMERA_HEIGHT / 2), 2);
	SDL_Log("dist: (%d)", distance);

	SDL_Log("lightness: (%d)", 255 / MAX_LIGHT * (MAX_LIGHT - Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE].lightness)); 
	if (distance / BLOCK_SIZE <= 90000 / BLOCK_SIZE && Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE].ID == NONE) {
		block tem = inventory.Place();
		if (tem.ID != NONE) {
			Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] = tem;
			if (tem.ID == TORCH) {
				Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE].lightSource = true;
			}
		}
		
	}
	std::thread thread(&Game::UpdateLight, this);
	thread.detach();

}

void Game::on_right_click(SDL_Event event) {
	int mouseX, mouseY, distance;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseX += cameraPos.x - cameraPos.x / BLOCK_SIZE * BLOCK_SIZE;
	mouseY += cameraPos.y - cameraPos.y / BLOCK_SIZE * BLOCK_SIZE;
	SDL_Log("right clicked in: (%d, %d)", mouseX, mouseY);

	distance = pow(((player.GetPos().x - cameraPos.x - 16) - mouseX), 2) + pow(((player.GetPos().y - cameraPos.y - 16) - mouseY), 2);
	SDL_Log("dist: (%d)", distance);

	if (distance / BLOCK_SIZE <= 90000 / BLOCK_SIZE && Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE].ID != NONE) {
		inventory.PickUp({Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE], 1});
		Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] = { NONE,0 };
	}
	std::thread thread(&Game::UpdateLight, this);
	thread.detach();
}

void Game::SetDeltaTime(Uint32 deltaTime)
{
	this->deltaTime = deltaTime;
}

void Game::DrawMap(InfoForRender info) {

	int textureIndex;
	for (size_t i = info.Start; i < info.End; i++)//filling screen with blocks
	{
		for (size_t j = 0; j < CAMERA_HEIGHT / BLOCK_SIZE + 2; j++)
		{
			int texturIndex;
			SDL_Rect dest = { i * BLOCK_SIZE - info.dosPos.x,j * BLOCK_SIZE - info.dosPos.y,BLOCK_SIZE,BLOCK_SIZE };


			textureIndex = static_cast<int>(Map[info.firstPos.y + j][info.firstPos.x + i].ID);
			SDL_Rect sours = { textureIndex % 16 * TEXTURE_SIZE ,textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
			//SDL_Rect dest = { i * BLOCK_SIZE ,j * BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
			SDL_RenderCopy(renderer, texture, &sours, &dest);

			if (Map[info.firstPos.y + j][info.firstPos.x + i].area != 0) {
				textureIndex = 205;
				if (Map[info.firstPos.y + j - 1][info.firstPos.x + i].area != 0) {

				}
				else {

					dest.h = Map[info.firstPos.y + j][info.firstPos.x + i].area / (float)(WATERCAPACITY) * (float)(BLOCK_SIZE);
					if (dest.h < 1) {
						dest.h = 1;
					}
					if (dest.h > BLOCK_SIZE) {
						dest.h = BLOCK_SIZE;
					}
					int dh = BLOCK_SIZE - dest.h;
					dest.y += dh;
				}
				sours = { textureIndex % 16 * TEXTURE_SIZE ,textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };

				SDL_RenderCopy(renderer, texture, &sours, &dest);

			}
			textureIndex = 221;
			sours = { textureIndex % 16 * TEXTURE_SIZE ,textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
			SDL_Rect rect;
			rect.x = i * BLOCK_SIZE - info.dosPos.x;
			rect.y = j * BLOCK_SIZE - info.dosPos.y;
			rect.w = 32;
			rect.h = 32;

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 / MAX_LIGHT * (MAX_LIGHT  - Map[info.firstPos.y + j][info.firstPos.x + i].lightness));
			SDL_RenderFillRect(renderer, &rect);

		}
	}
	
}

void Game::UpdateWater() {
	bool mooved = false;
	for (size_t x = 0; x < MAP_WIDTH; x++) {
		for (size_t y = MAP_HEIGHT - 2; y > 0; y--) {

			if (Map[y][x].area!= 0) {//water
				mooved = false;
				float curentArea = Map[y][x].area;
				if (!Map[y + 1][x].colideable || (Map[y + 1][x].area != 0 && Map[y + 1][x].area != WATERCAPACITY) ) {//water under
					float targetArea = Map[y + 1][x].area;
					float availeableArea = WATERCAPACITY - targetArea;
					if (curentArea - availeableArea >= 0) {
						Map[y][x].area = curentArea - availeableArea;
						Map[y + 1][x].area =  WATERCAPACITY;
					}
					else {
						Map[y][x].area = 0;
						Map[y + 1][x].area = targetArea+curentArea;
					}
					
					mooved = true;
				}
				
				curentArea = Map[y][x].area;
				if (curentArea != 0) {
					if (rand() % 2 == 0) {
						if (!Map[y][x + 1].colideable || (Map[y][x + 1].area != 0 && Map[y][x + 1].area != curentArea)) {//water right
							float transArea;
							if (!Map[y][x + 2].colideable || (Map[y][x + 2].area != 0 && Map[y][x + 2].area != curentArea)) {
								transArea = (Map[y][x + 1].area +Map[y][x + 2].area + curentArea) / 3;
								Map[y][x].area = transArea;
								Map[y][x + 1].area = transArea;
								Map[y][x + 2].area = transArea;
							}
							else
							{
								transArea = (Map[y][x + 1].area + curentArea) / 2;
								Map[y][x].area = transArea;
								Map[y][x + 1].area = transArea;

							}
							mooved = true;
							curentArea = transArea;
						}

						else if (!Map[y][x - 1].colideable || (Map[y][x - 1].area != 0 && Map[y][x - 1].area != curentArea)) {//water left
							float transArea;
							if (!Map[y][x - 2].colideable || (Map[y][x - 2].area != 0 && Map[y][x - 2].area != curentArea)) {
								transArea = (Map[y][x - 1].area + Map[y][x- 2].area + curentArea) / 3;
								Map[y][x].area =  transArea;
								Map[y][x - 1].area = transArea;
								Map[y][x - 2].area = transArea;
							}
							else
							{
								transArea = (Map[y][x - 1].area + curentArea) / 2;
								Map[y][x].area = transArea;
								Map[y][x - 1].area = transArea;

							}
							mooved = true;
							curentArea = transArea;
						}
					}
					else {
						if (!Map[y][x - 1].colideable || (Map[y][x - 1].area != 0 && Map[y][x - 1].area != curentArea)) {//water left
							float transArea;
							if (!Map[y][x - 2].colideable || (Map[y][x - 2].area != 0 && Map[y][x - 2].area != curentArea)) {
								transArea = (Map[y][x - 1].area + Map[y][x - 2].area + curentArea) / 3;
								Map[y][x].area = transArea;
								Map[y][x - 1].area = transArea;
								Map[y][x - 2].area = transArea;
							}
							else
							{
								transArea = (Map[y][x - 1].area + curentArea) / 2;
								Map[y][x].area = transArea;
								Map[y][x - 1].area = transArea;

							}
							mooved = true;
							curentArea = transArea;
						}

						else if (!Map[y][x + 1].colideable || (Map[y][x + 1].area != 0 && Map[y][x + 1].area != curentArea)) {//water right
							float transArea;
							if (!Map[y][x + 2].colideable || (Map[y][x + 2].area != 0 && Map[y][x + 2].area != curentArea)) {
								transArea = (Map[y][x + 1].area + Map[y][x + 2].area + curentArea) / 3;
								Map[y][x].area = transArea;
								Map[y][x + 1].area = transArea;
								Map[y][x + 2].area = transArea;
							}
							else
							{
								transArea = (Map[y][x + 1].area + curentArea) / 2;
								Map[y][x].area = transArea;
								Map[y][x + 1].area = transArea;

							}
							mooved = true;
							curentArea = transArea;
							
						}
					}

				}

				if (Map[y][x].area < 1) {
					Map[y][x].area = 0;
				}
				
			}
		}

	}
}


void Game::UpdateLight()
{
	for (size_t x = 0; x < MAP_WIDTH; x++) {
		for (size_t y = 0; y < MAP_HEIGHT; y++) {

			int min_dist = MAX_LIGHT;
			for (int i = -MAX_LIGHT - 1; i < MAX_LIGHT+1; i++) {
				for (int j = -MAX_LIGHT-1; j < MAX_LIGHT+1; j++) {
					if (x + i < 0 || x + i >= MAP_WIDTH || y + j < 0 || y + j >= MAP_HEIGHT) {
						continue;
					}

					if (Map[y + j][x + i].lightSource) {
						int dist = abs(i) + abs(j)-1;
						if (dist < min_dist) {
							min_dist = dist;
						}
					}
				}
			}
			Map[y][x].lightness = MAX_LIGHT - min_dist;
			if (Map[y][x].lightness < 0) {
				Map[y][x].lightness = 0;
			}
			if (Map[y][x].lightness > MAX_LIGHT) {
				Map[y][x].lightness = MAX_LIGHT;
			}
		
		}
	}
}




void Game::Render()
{
	SDL_RenderClear(renderer);
	int textureIndex = 0;
	SDL_Rect sours = { textureIndex % 16 * TEXTURE_SIZE , textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };

	SDL_RenderCopy(renderer, texture, &sours, NULL);
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
	if (cameraPos.x >= MAP_WIDTH*BLOCK_SIZE-CAMERA_WIDTH-BLOCK_SIZE)
	{
		cameraPos.x = MAP_WIDTH * BLOCK_SIZE - CAMERA_WIDTH - BLOCK_SIZE;
	}
	if (cameraPos.y >= MAP_HEIGHT * BLOCK_SIZE - CAMERA_HEIGHT - BLOCK_SIZE)
	{
		cameraPos.y = MAP_HEIGHT * BLOCK_SIZE - CAMERA_HEIGHT - BLOCK_SIZE;
	}
	Vector2 firstPos = { cameraPos.x / BLOCK_SIZE, cameraPos.y / BLOCK_SIZE};
	Vector2 dosPos = { cameraPos.x - firstPos.x*BLOCK_SIZE, cameraPos.y - firstPos.y*BLOCK_SIZE };
	InfoForRender info = { firstPos,dosPos,0,CAMERA_WIDTH / BLOCK_SIZE + 1 };
	DrawMap(info);
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseX += dosPos.x;
	mouseY += dosPos.y;

	mouseX /= BLOCK_SIZE;
	mouseY /= BLOCK_SIZE;

	textureIndex = 5;
	sours = { textureIndex % 16 * TEXTURE_SIZE , textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
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

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);



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
			case SDLK_F1:
				player.SetGamemode(0);
				break;
			case SDLK_F2:
				player.SetGamemode(1);
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
	
	Vector2f dir = { 0,0 };
	if (butt.a && player.GetPos().x != 0) {
		dir.x -= 1;
	}
	if (butt.d && player.GetPos().x < MAP_WIDTH*BLOCK_SIZE) {
		dir.x += 1;
	}
	if (butt.space ) {
		player.Jump(Map);
	}
	player.Move(dir, deltaTime, Map);
	if (player.GetGamemode() == 1) {
		dir = { 0,0 };
		if (butt.w && player.GetPos().x != 0) {
			dir.y -= 1;
		}
		if (butt.s && player.GetPos().x < MAP_WIDTH * BLOCK_SIZE) {
			dir.y += 1;
		}
		player.Move(dir, deltaTime, Map);
	}
}

void Game::Quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	running = false;
}
