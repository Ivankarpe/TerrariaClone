#include "Player.h"

void Player::Move(Vector2 dir, std::vector<std::vector<int>> Map)
{
	int dx = dir.x;
	int dy = dir.y;
	//SDL_Log("x: %d , y: %d", (cord.x + dx) / BLOCK_SIZE , (cord.y + dy) / BLOCK_SIZE);
	bool x = true;
	bool y = true;
	if (Map[(cord.y - 16 + dy) / BLOCK_SIZE][(cord.x - 16) / BLOCK_SIZE] != 0) { y = false; }
	if (Map[(cord.y - 16) / BLOCK_SIZE][(cord.x + dx - 16) / BLOCK_SIZE] != 0) { x = false; }

	if (Map[(cord.y - 16 + dy) / BLOCK_SIZE][(cord.x + 16) / BLOCK_SIZE] != 0) { y = false; }
	if (Map[(cord.y - 16) / BLOCK_SIZE][(cord.x + dx + 16) / BLOCK_SIZE] != 0) { x = false; }

	if (Map[(cord.y + 16 + dy) / BLOCK_SIZE][(cord.x - 16) / BLOCK_SIZE] != 0) { y = false; }
	if (Map[(cord.y + 16) / BLOCK_SIZE][(cord.x + dx - 16) / BLOCK_SIZE] != 0) { x = false; }

	if (Map[(cord.y + 16 + dy) / BLOCK_SIZE][(cord.x + 16) / BLOCK_SIZE] != 0) { y = false; }
	if (Map[(cord.y + 16) / BLOCK_SIZE][(cord.x + dx + 16) / BLOCK_SIZE] != 0) { x = false; }

	if (x) {
		cord.x += dx;
	}

	if (y) {
		cord.y += dy;
	}
	else
	{
		acc = 0;
	}
}

void Player::Update(std::vector<std::vector<int>> Map)
{
	acc += 0.1;
	int dy = acc;
	Move({0, dy}, Map);
}

void Player::Jump()
{
	if (acc == 0) {
		acc = -9;

	}

}
