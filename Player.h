#pragma once
#include "Settings.h"
#include <vector>
#include "SDL.h"
class Player
{
public:
	Vector2 GetPos() { return { (int)(cord.x), (int)(cord.y) }; }

	void Move(Vector2f dir, Uint32 deltaTime, std::vector<std::vector<block>> Map);
	void Update(Uint32 deltaTime,std::vector<std::vector<block>> Map);
	void Jump(std::vector<std::vector<block>> Map);

	void SetGamemode(int gamemode);
	int GetGamemode() { return gamemode; }
	Vector2f cord = { 2 , 0};
private:
	int gamemode = 0;

	Vector2f cord = { 100, 50};

	float acc = 0;
	float speed = 10;
};

