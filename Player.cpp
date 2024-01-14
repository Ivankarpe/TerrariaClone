#include "Player.h"

void Player::Move(Vector2f dir, Uint32 deltaTime, std::vector<std::vector<int>> Map)
{
	if (cord.x < 0) {
		cord.x = 0;
	}
	if (cord.y < 0) {
		cord.y = 0;
	}
	float dx = dir.x * static_cast<int>(deltaTime) / 1000. * speed * BLOCK_SIZE;
	float dy = dir.y * static_cast<int>(deltaTime) / 1000. * speed * BLOCK_SIZE;

	float div = 6;

	for (size_t i = 0; i < div; i++)
	{

		bool x = true;
		bool y = true;
		if (gamemode == 0) {

			if (Map[(cord.y - 16 + dy / div) / BLOCK_SIZE][(cord.x - 16) / BLOCK_SIZE] != 0) { y = false; }
			else if (Map[(cord.y - 16 + dy / div) / BLOCK_SIZE][(cord.x + 16) / BLOCK_SIZE] != 0) { y = false; }
			else if (Map[(cord.y + 16 + dy / div) / BLOCK_SIZE][(cord.x - 16) / BLOCK_SIZE] != 0) { y = false; }
			else if (Map[(cord.y + 16 + dy / div) / BLOCK_SIZE][(cord.x + 16) / BLOCK_SIZE] != 0) { y = false; }

			if (Map[(cord.y - 16) / BLOCK_SIZE][(cord.x - 16 + dx / div) / BLOCK_SIZE] != 0) { x = false; }
			else if (Map[(cord.y - 16) / BLOCK_SIZE][(cord.x + 16 + dx / div) / BLOCK_SIZE] != 0) { x = false; }
			else if (Map[(cord.y + 16) / BLOCK_SIZE][(cord.x - 16 + dx / div) / BLOCK_SIZE] != 0) { x = false; }
			else if (Map[(cord.y + 16) / BLOCK_SIZE][(cord.x + 16 + dx / div) / BLOCK_SIZE] != 0) { x = false; }
		}
		else
		{
			dx *= 1.5;
			dy *= 1.5;
		}
		if (cord.x + 48 + dx / div >= MAP_WIDTH * BLOCK_SIZE) { x = false; }
		if (cord.y + 48 + dy / div >= MAP_HEIGHT * BLOCK_SIZE) { y = false; }
		if (x) {

			cord.x += dx * (1 / div);

		}
		if (y) {
			cord.y += dy * (1 / div);
		}
		else {
			acc = 0;
		}
	}
	if (cord.x < 0) {
		cord.x = 0;
	}
	if (cord.x > MAP_WIDTH * BLOCK_SIZE) {
		cord.x = MAP_WIDTH * BLOCK_SIZE;
	}
	if (cord.y < 0) {
		cord.y = 0;
	}
	if (cord.y > MAP_HEIGHT * BLOCK_SIZE) {
		cord.y = MAP_HEIGHT * BLOCK_SIZE;
	}
}

void Player::Update(Uint32 deltaTime, std::vector<std::vector<int>> Map)
{
	if (gamemode == 0) {
		acc += 9*deltaTime/1000.;
		if (acc >= 10) {
			acc = 10;
		}
		float dy = acc;
		Move({ 0, dy }, deltaTime, Map);
	}
	else
	{

	}
}

void Player::Jump( std::vector<std::vector<int>> Map)
{
	if (gamemode == 0) {

		bool y = false;

		if (Map[(cord.y + 16 + 5) / BLOCK_SIZE][(cord.x - 16) / BLOCK_SIZE] != 0) { y = true; }
		if (Map[(cord.y + 16 + 5) / BLOCK_SIZE][(cord.x + 16) / BLOCK_SIZE] != 0) { y = true; }

		if (y) {
			acc = -4;

		}
	}
	else {

	}
	
}

void Player::SetGamemode(int gamemode)
{
	this->gamemode = gamemode;
}
