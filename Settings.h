#pragma once
const int MAP_WIDTH = 2000;
const int MAP_HEIGHT = 300;

const int CAMERA_WIDTH = 1360;
const int CAMERA_HEIGHT = 768;

const int BLOCK_SIZE = 32;
const int TEXTURE_SIZE = 16;
struct Buttons {
	bool w, a, s, d;
};


struct Vector2
{
	int x;
	int y;
};