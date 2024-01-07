#pragma once
#include "Settings.h"
class Player
{
public:
	Vector2 GetPos() { return cord; }

	void Move(Vector2 dir);

private:
	Vector2 cord = { CAMERA_WIDTH , CAMERA_HEIGHT};


};

