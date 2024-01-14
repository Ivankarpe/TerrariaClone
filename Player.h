#pragma once
#include "Settings.h"
#include <vector>
#include "SDL.h"
class Player
{
public:
	Vector2 GetPos() { return { (int)(cord.x), (int)(cord.y) }; }

	void Move(Vector2f dir, Uint32 deltaTime, std::vector<std::vector<int>> Map);
	void Update(Uint32 deltaTime,std::vector<std::vector<int>> Map);
	void Jump(std::vector<std::vector<int>> Map);

	void SetGamemode(int gamemode);
	int GetGamemode() { return gamemode; }
private:
	int gamemode = 0;
	Vector2f cord = { 100 , 48};
	float acc = 0;
	float speed = 10;
};

