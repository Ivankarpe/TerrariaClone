#pragma once
#include "Settings.h"
#include <vector>
#include "SDL.h"
class Player
{
public:
	Vector2 GetPos() { return cord; }

	void Move(Vector2 dir, std::vector<std::vector<int>> Map);
	void Update(std::vector<std::vector<int>> Map);
	void Jump(std::vector<std::vector<int>> Map);
private:
	Vector2 cord = { CAMERA_WIDTH , CAMERA_HEIGHT};
	float acc = 0;

};

