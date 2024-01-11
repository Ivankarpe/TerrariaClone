#pragma once
#include "Settings.h"
#include <vector>
#include "SDL.h"
class Player
{
public:
	Vector2 GetPos() { return cord; }

	void Move(float deltaTime, std::vector<std::vector<int>> Map);

	void Update(float deltaTime, std::vector<std::vector<int>> Map);

	void Jump(std::vector<std::vector<int>> Map);

	void SetKeys(Buttons buttons);
private:
	int gamemode = 0;
	Vector2 cord = { 120, CAMERA_HEIGHT*1};
	float acc = 0;
	float dx = 0;

};

