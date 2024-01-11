#include "Player.h"

void Player::Move(float deltaTime, std::vector<std::vector<int>> Map)
{
	// x
	
	bool x = true;
	if (!(cord.x + dx > 0 || cord.x + dx < MAP_WIDTH * BLOCK_SIZE)) { x = false; }
	if (Map[(cord.y - 16) / BLOCK_SIZE][(cord.x + dx - 16) / BLOCK_SIZE] != 0) { x = false; }
	if (Map[(cord.y - 16) / BLOCK_SIZE][(cord.x + dx + 16) / BLOCK_SIZE] != 0) { x = false; }
	if (Map[(cord.y + 16) / BLOCK_SIZE][(cord.x + dx - 16) / BLOCK_SIZE] != 0) { x = false; }
	if (Map[(cord.y + 16) / BLOCK_SIZE][(cord.x + dx + 16) / BLOCK_SIZE] != 0) { x = false; }
	
	if (x) { cord.x += (dx == 1) ? (deltaTime * 20) : (dx == 2 ? (-1 * deltaTime * 20) : 0); }
	

	int dy = acc;
	bool y = true;
	
	if (!(cord.y + dy > 0 || cord.y + dy < MAP_HEIGHT * BLOCK_SIZE)) { y = false; }
	if (Map[(cord.y - 16 + dy) / BLOCK_SIZE][(cord.x - 16) / BLOCK_SIZE] != 0) { y = false; }
	if (Map[(cord.y - 16 + dy) / BLOCK_SIZE][(cord.x + 16) / BLOCK_SIZE] != 0) { y = false; }
	if (Map[(cord.y + 16 + dy) / BLOCK_SIZE][(cord.x - 16) / BLOCK_SIZE] != 0) { y = false; }
	if (Map[(cord.y + 16 + dy) / BLOCK_SIZE][(cord.x + 16) / BLOCK_SIZE] != 0) { y = false; }
	if (y) { cord.y += dy * deltaTime * 100; }
	else { acc -= 1; }
	

	if (acc < 0) { acc = 0; }


	
}

void Player::Update(float deltaTime, std::vector<std::vector<int>> Map)
{
	acc += 9 * deltaTime;

	Move(deltaTime, Map);
}

void Player::Jump( std::vector<std::vector<int>> Map)
{
	bool y = false;
	
	if (Map[(cord.y + 16 + 5) / BLOCK_SIZE][(cord.x - 16) / BLOCK_SIZE] != 0) { y = true; }
	if (Map[(cord.y + 16 + 5) / BLOCK_SIZE][(cord.x + 16) / BLOCK_SIZE] != 0) { y = true; }

	if (y) {
		acc = -9;

	}

}

void Player::SetKeys(Buttons buttons)
{
	dx = 0;
	if (buttons.a == true)
	{
		dx -= 1;
	}
	if (buttons.d == true)
	{
		dx += 1;
	}
	
}
