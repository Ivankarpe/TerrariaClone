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
	running = true;
	SDL_Surface* temp = IMG_Load("d7aem.png");
	texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("Tiles_0.png");
	grassTexture = SDL_CreateTextureFromSurface(renderer, temp);
	textures.insert({DIRT, grassTexture});
	SDL_FreeSurface(temp);

	temp = IMG_Load("Tiles_1.png");
	grassTexture = SDL_CreateTextureFromSurface(renderer, temp);
	textures.insert({ STONE, grassTexture });
	SDL_FreeSurface(temp);

	temp = IMG_Load("klipartz.com.png");
	hoe = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("Tree_Tops_0.png");
	tree_Top = SDL_CreateTextureFromSurface(renderer, temp);
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
		if (int lakeChance = rand() % 10 == 0) {
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
					for (int h2 = h; h2 < heights[x + i]; h2++) {
						//Map[h2][x + i] = { WATER, 0 };
					}
				}
				SDL_Log("size, x: (%d, %d)", size, x);
			}
		}
	}


	//int VOID = 0;
	//int STONE = 1;
	int seed = time(NULL);
	int STONEProb = 65;
	srand(seed);
	int randomLeftDiagonalGrass = 0;
	int randomRightDiagonalGrass = 0;
	int randomsmoothGrass = 0;
	int randomUnderLeftDiagonalGrass1 = 0;


	for (int x = 0; x < MAP_WIDTH - 0; ++x) {
		for (int y = 0 + heights[x] + heights2[x] / 2; y < MAP_HEIGHT - 0; ++y) {
			if (y > heights[x] + heights2[x]) {
				Map[y][x] = { STONE, 1 };
				if (rand() % 100 > STONEProb) Map[y][x] = { NONE, 0 };
			}
			caveSpawn(x, y, 2500, 5, 80);
			caveSpawn(x, y, 2500, 105, 175);
		}
	}
	for (int x = 0; x < MAP_WIDTH - 1; x++) {//filling map with blocks
		for (int y = heights[x]; y < heights[x] + heights2[x] + 7; y++) {
			if (y <= heights[x] + heights2[x] + 5 && Map[y][x].ID != NONE5) {
				Map[y][x] = { DIRT, 1, static_cast<Textures>(19), 1 };
				
			}
		}
	}


	for (int w = 1; w < MAP_WIDTH - 1; w++) {// grouping the STONE
		for (int h = heights[w]; h < MAP_HEIGHT - 1; h++) {
			int STONECounter = 0;

			for (int x = w - 1; x < w + 2; x++) {
				for (int y = h - 1; y < h + 2; y++) {
					if (!(x == w && y == h)) {
						if (Map[y][x].ID == STONE)
							STONECounter++;
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


	for (int x = 0; x < MAP_WIDTH; x++) {//filling map with blocks
		for (int y = 0; y < MAP_HEIGHT; y++) {
			debug(x, y);
		}
	}
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

void Game::caveSpawn(int x, int y, int caveChance, int caveMinAngle, int caveMaxAngle) {
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
							Map[sideY][sideX] = { NONE5, 0};
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

	/*counter+= deltaTime;
	while (counter > 100) {
	UpdateWater();
	counter -= 100;
	}*/

}

void Game::setGrass(int x, int y, int heights[MAP_WIDTH], int heights2[MAP_WIDTH], int randomLeftDiagonalGrass, int randomRightDiagonalGrass, int randomsmoothGrass, int randomUnderLeftDiagonalGrass1) {
	if (Map[y][x].ID == DIRT) {
		bool down = false;
		bool right = false;
		bool up = false;
		bool left = false;
		if (x > 1) {
			left = Map[y][x - 1].ID == Map[y][x].ID;
		}
		if (x < MAP_WIDTH - 1) {
			right = Map[y][x + 1].ID == Map[y][x].ID;
		}
		if (true) {
			up = Map[y - 1][x].ID == Map[y][x].ID;
		}
		if (true) {

			down = Map[y + 1][x].ID == Map[y][x].ID;
		}

		if ((!left) && (!up) && (down) && (right)) {//.....'''''
			randomLeftDiagonalGrass = leftDiagonalGrass1 + rand() % 3 * 2;
			Map[y][x] = { DIRT, 1, static_cast<Textures>(randomLeftDiagonalGrass), 1 };
		}
		else if (Map[y][x - 1].top == 1 && Map[y - 1][x].top == 1 && Map[y - 1][x - 1].colideable == 0) {//.....:'''''
			Map[y][x] = { DIRT, 1, static_cast<Textures>(99) };
		}
		else if ((left) && (!up) && (down) && (!right)) {//'''''.....
			randomRightDiagonalGrass = rightDiagonalGrass1 + rand() % 3 * 2;

			Map[y][x] = { DIRT, 1, static_cast<Textures>(49), 1 };
		}
		else if (Map[y][x + 1].top == 1 && Map[y - 1][x].top == 1 && Map[y - 1][x + 1].colideable == 0) {//'''':.....
			Map[y][x] = { DIRT, 1, static_cast<Textures>(98) };
		}


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		else if ((!left) && (up) && (!down) && (right)) {//'''''.....
			randomUnderLeftDiagonalGrass1 = underLeftDiagonalGrass1 + rand() % 3 * 2;
			Map[y][x] = { DIRT, 1, static_cast<Textures>(randomUnderLeftDiagonalGrass1), 1 };
			SDL_Log("FUUUUUUUUUUUUUUUUUUUUUUCK");
		}
		else if (Map[y][x - 1].top == 1 && Map[y - 1][x].top == 1 && Map[y - 1][x - 1].colideable == 0) {//.....:'''''
			Map[y][x] = { DIRT, 1, static_cast<Textures>(99) };
		}
		else if ((left) && (up) && (!down) && (!right)/*Map[y + 1][x].ID != DIRT  && Map[y][x + 1].ID != DIRT*/) {//'''''.....
			randomRightDiagonalGrass = rightDiagonalGrass1 + rand() % 3 * 2;
			Map[y][x] = { DIRT, 1, static_cast<Textures>(underRightDiagonalGrass1), 1 };
		}
		else if (Map[y][x + 1].top == 1 && Map[y - 1][x].top == 1 && Map[y - 1][x + 1].colideable == 0) {//'''':.....
			Map[y][x] = { DIRT, 1, static_cast<Textures>(98) };
		}
		//else if (Map[y - 1][x].ID == DIRT && y > heights[x] + heights2[x] + 4){
		//	//randomLeftDiagonalGrass = leftDiagonalGrass1 + rand() % 3 * 2;
		//	Map[y][x] = { DIRT, 1, static_cast<Textures>(202) };
		//}
		else if (!up) {//........
			randomsmoothGrass = smoothGrass1 + rand() % 3;
			Map[y][x] = { DIRT, 1, static_cast<Textures>(randomsmoothGrass), 1 };
		}
	}
}
void Game::debug(int x, int y) {
	if (x >= 0 && x < MAP_WIDTH) {
		if (Map[y][x].ID != NONE && Map[y][x].ID != NONE5) {

			bool down = false;
			bool right = false;
			bool up = false;
			bool left = false;

			bool upleft = false;
			bool upright = false;
			bool downleft = false;
			bool downright = false;
			if (x >= 1) {
				left = Map[y][x - 1].ID != NONE && Map[y][x - 1].ID != NONE5;
				downleft = Map[y + 1][x - 1].ID == NONE && Map[y + 1][x - 1].ID == NONE5;
				upleft = Map[y - 1][x - 1].ID == NONE && Map[y - 1][x - 1].ID == NONE5;
			}
			if (x < MAP_WIDTH - 1) {
				right = Map[y][x + 1].ID != NONE && Map[y][x + 1].ID != NONE5;
			}
			if (y >=1) {
				up = Map[y - 1][x].ID != NONE && Map[y - 1][x].ID != NONE5;
				downright = Map[y + 1][x + 1].ID != NONE && Map[y + 1][x + 1].ID != NONE5;
				upright = Map[y - 1][x + 1].ID != NONE && Map[y - 1][x + 1].ID != NONE5;
			}
			if (y < MAP_HEIGHT - 1) {

				down = Map[y + 1][x].ID != NONE && Map[y + 1][x].ID != NONE5;
			}

			if ((!left) && (!up) && (down) && (right)) {//.....'''''
				int randomLeftDiagonalGrass = leftDiagonalGrass1 + rand() % 3 * 2;
				Map[y][x].TEXTURE = static_cast<Textures>(randomLeftDiagonalGrass);
			}
			else if ((left) && (up) && (down) && (right) && !upleft) {//.....:'''''
				Map[y][x].TEXTURE = static_cast<Textures>(97);
			}
			else if ((left) && (!up) && (down) && (!right)) {//'''''.....
				int randomRightDiagonalGrass = rightDiagonalGrass1 + rand() % 3 * 2;

				Map[y][x].TEXTURE = static_cast<Textures>(49);
			}
			else if ((left) && (up) && (down) && (right) && !upright) {//'''':.....
				Map[y][x].TEXTURE = static_cast<Textures>(96);
			}


			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			else if ((!left) && (up) && (!down) && (right)) {//'''''.....
				int randomUnderLeftDiagonalGrass1 = underLeftDiagonalGrass1 + rand() % 3 * 2;
				Map[y][x].TEXTURE = static_cast<Textures>(randomUnderLeftDiagonalGrass1);
				SDL_Log("FUUUUUUUUUUUUUUUUUUUUUUCK");
			}
			else if ((left) && (up) && (down) && (right) && !downright) {//.....:'''''
				Map[y][x].TEXTURE = static_cast<Textures>(80);
			}
			else if ((left) && (up) && (!down) && (!right)/*Map[y + 1][x].ID != DIRT  && Map[y][x + 1].ID != DIRT*/) {//'''''.....
				int randomRightDiagonalGrass = rightDiagonalGrass1 + rand() % 3 * 2;
				Map[y][x].TEXTURE = static_cast<Textures>(underRightDiagonalGrass1);
			}
			else if ((left) && (up) && (down) && (right) && !downleft) {//'''':.....
				Map[y][x].TEXTURE = static_cast<Textures>(81);
			}
			//else if (Map[y - 1][x].ID == DIRT && y > heights[x] + heights2[x] + 4){
			//	//randomLeftDiagonalGrass = leftDiagonalGrass1 + rand() % 3 * 2;
			//	Map[y][x].TEXTURE =static_cast<Textures>(202) ;
			//}

			/////////////////////////////////////////////////

			else if (!up && !down && !left && right) {
				int randomsmoothGrass = 9 + 16 * (rand() % 3);
				Map[y][x].TEXTURE = static_cast<Textures>(randomsmoothGrass);

			}
			else if (!up && !down && left && !right) {
				int randomsmoothGrass = 12 + 16 * (rand() % 3);
				Map[y][x].TEXTURE = static_cast<Textures>(randomsmoothGrass);

			}
			else if (!up && down && !left && !right) {
				int randomsmoothGrass = 6 + rand() % 3;
				Map[y][x].TEXTURE = static_cast<Textures>(randomsmoothGrass);

			}
			else if (up && !down && !left && !right) {
				int randomsmoothGrass = 54 + rand() % 3;
				Map[y][x].TEXTURE = static_cast<Textures>(randomsmoothGrass);

			}
			///////////////////
			else if (!up && !down && !left && !right) {
				int randomsmoothGrass = 57 + rand() % 3;
				Map[y][x].TEXTURE = static_cast<Textures>(randomsmoothGrass);

			}
			//////////////////////////


			else if (!up && down && left && right) {//........
				int randomsmoothGrass = smoothGrass1 + rand() % 3;
				Map[y][x].TEXTURE = static_cast<Textures>(randomsmoothGrass);
			}
			else if (up && !down && left && right) {//........
				int randomsmoothGrass = 33 + rand() % 3;
				Map[y][x].TEXTURE = static_cast<Textures>(randomsmoothGrass);
			}
			else if (up && down && !left && right) {//........
				int randomsmoothGrass = 16 * (rand() % 3);
				Map[y][x].TEXTURE = static_cast<Textures>(randomsmoothGrass);
			}
			else if (up && down && left && !right) {//........
				int randomsmoothGrass = 4 + 16 * (rand() % 3);
				Map[y][x].TEXTURE = static_cast<Textures>(randomsmoothGrass);
			}
		}
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
	
	SDL_Log("colid: (%d)", Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE].colideable);

	if (distance / BLOCK_SIZE <= 90000 / BLOCK_SIZE && Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE].ID == NONE) {
		block tem = inventory.Place();
		if (tem.ID != NONE) {
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

	if (distance / BLOCK_SIZE <= 90000 / BLOCK_SIZE && Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE].ID != NONE) {
		inventory.PickUp({Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE], 1});
		Map[cameraPos.y / BLOCK_SIZE + mouseY / BLOCK_SIZE][cameraPos.x / BLOCK_SIZE + mouseX / BLOCK_SIZE] = { NONE,0 };
	}
}

void Game::SetDeltaTime(Uint32 deltaTime)
{
	this->deltaTime = deltaTime;
}

void Game::DrawMap(InfoForRender info) {

	int textureIndex;
	int realTextureIndex;
	for (size_t i = info.Start; i < info.End; i++)//filling screen with blocks
	{
		for (size_t j = 0; j < CAMERA_HEIGHT / BLOCK_SIZE + 2; j++)
		{
			if (Map[info.firstPos.y + j][info.firstPos.x + i].ID != NONE && Map[info.firstPos.y + j][info.firstPos.x + i].ID != NONE5) {
				if (Map[info.firstPos.y + j][info.firstPos.x + i].ID == DIRT) {

					textureIndex = static_cast<int>(Map[info.firstPos.y + j][info.firstPos.x + i].ID);
					realTextureIndex = static_cast<int>(Map[info.firstPos.y + j][info.firstPos.x + i].TEXTURE);
					SDL_Rect sours = { realTextureIndex % 16 * 16 + realTextureIndex % 16 * 2,realTextureIndex / 16 * 16 + realTextureIndex / 16 * 2,TEXTURE_SIZE,TEXTURE_SIZE };


					//SDL_Rect dest = { i * BLOCK_SIZE ,j * BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
					SDL_Rect dest = { i * BLOCK_SIZE - info.dosPos.x,j * BLOCK_SIZE - info.dosPos.y,BLOCK_SIZE,BLOCK_SIZE };

					SDL_RenderCopy(renderer, textures[DIRT], &sours, &dest);
				}
				if (Map[info.firstPos.y + j][info.firstPos.x + i].ID == STONE) {


					textureIndex = static_cast<int>(Map[info.firstPos.y + j][info.firstPos.x + i].ID);
					realTextureIndex = static_cast<int>(Map[info.firstPos.y + j][info.firstPos.x + i].TEXTURE);
					SDL_Rect sours = { realTextureIndex % 16 * 16 + realTextureIndex % 16 * 2,realTextureIndex / 16 * 16 + realTextureIndex / 16 * 2,TEXTURE_SIZE,TEXTURE_SIZE };


					//SDL_Rect dest = { i * BLOCK_SIZE ,j * BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE };
					SDL_Rect dest = { i * BLOCK_SIZE - info.dosPos.x,j * BLOCK_SIZE - info.dosPos.y,BLOCK_SIZE,BLOCK_SIZE };

					SDL_RenderCopy(renderer, textures[STONE], &sours, &dest);

				}
			}
		}

	}
}
//void Game::UpdateWater() {
//	bool mooved = false;
//	for (size_t x = 0; x < MAP_WIDTH; x++) {
//		for (size_t y = MAP_HEIGHT - 1; y > 0; y--) {
//			if (Map[y][x] == 205) {//water
//				mooved = false;
//				if (Map[y + 1][x] == AIR || Map[y + 1][x] == 209) {//water under
//					Map[y][x] = AIR;
//					Map[y + 1][x] = 205;
//					mooved = true;
//				}
//				if (0) {
//					if (rand() % 2 == 0) {
//						if ((Map[y + 1][x - 1] == AIR || Map[y + 1][x - 1] == 209) && Map[y][x - 1] == AIR) {//water under-left
//							Map[y][x] = AIR;
//							Map[y + 1][x - 1] = 205;
//							mooved = true;
//						}
//						else if ((Map[y + 1][x + 1] == AIR || Map[y + 1][x + 1] == 209) && Map[y][x + 1] == AIR) {//water under-right
//							Map[y][x] = AIR;
//							Map[y + 1][x + 1] = 205;
//							mooved = true;
//						}
//					}
//					else {
//						if ((Map[y + 1][x + 1] == AIR || Map[y + 1][x + 1] == 209) && Map[y][x+1] == AIR) {//water under-right
//							Map[y][x] = AIR;
//							Map[y + 1][x + 1] = 205;
//							mooved = true;
//						}
//						else if ((Map[y + 1][x - 1] == AIR || Map[y + 1][x - 1] == 209) && Map[y][x-1] == AIR) {//water under-left
//							Map[y][x] = AIR;
//							Map[y + 1][x - 1] = 205;
//							mooved = true;
//						}
//					}
//				}
//				if (!mooved) {
//					if (rand() % 2 == 0) {
//						if (Map[y][x + 1] == AIR) {//water right
//							Map[y][x] = AIR;
//							Map[y][x + 1] = 205;
//							mooved = true;
//							x++;
//						}
//						else if (Map[y][x - 1] == AIR) {//water left
//							Map[y][x] = AIR;
//							Map[y][x - 1] = 205;
//							mooved = true;
//						}
//					}
//					else {
//						if (Map[y][x - 1] == AIR) {//water left
//							Map[y][x] = AIR;
//							Map[y][x - 1] = 205;
//							mooved = true;
//						}
//						else if (Map[y][x + 1] == AIR) {//water right
//							Map[y][x] = AIR;
//							Map[y][x + 1] = 205;
//							mooved = true;
//							x++;
//						}
//					}
//
//				}
//
//				//if (Map[y][x] == 209) {
//				//	if (Map[y + 1][x] == AIR) {//flowing under on air
//				//		Map[y][x] = AIR;
//				//		Map[y + 1][x] = 209;
//				//	}
//				//	else if (Map[y + 1][x] == 209) {//flowing under on flowing
//				//		Map[y][x] = AIR;
//				//		Map[y + 1][x] = 205;
//				//	}
//				//	else if (Map[y + 1][x - 1] == 209 && Map[y + 1][x] == 205) {//flowing under-left
//				//		Map[y][x] = AIR;
//				//		Map[y + 1][x - 1] = 205;
//				//	}
//				//	else if (Map[y + 1][x + 1] == 209 && Map[y + 1][x] == 205) {//flowing under-right
//				//		Map[y+1][x] = AIR;
//				//		Map[y + 1][x + 1] = 205;
//				//	}
//				//	else if (Map[y][x - 1] == AIR && Map[y+1][x + 1] != AIR) {//flowing left
//				//		Map[y][x] = 209;
//				//		Map[y][x - 1] = 209;
//				//	}
//				//	else if (Map[y][x + 1] == AIR && Map[y+1][x - 1] != AIR) {//flowing right
//				//		Map[y][x] = 209;
//				//		Map[y][x + 1] = 209;
//				//	}
//				//}
//				/*if (Map[y][x] == AIR && Map[y][x - 1] == 205 && Map[y + 1][x] != 209) {
//					Map[y][x] = 209;
//
//				}*/
//			}
//		}
//
//	}
//}

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

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 10);
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
