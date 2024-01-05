#pragma once
const int MAP_WIDTH = 2000;
const int MAP_HEIGHT = 300;


const int CAMERA_WIDTH = 1920;
const int CAMERA_HEIGHT = 1080;


const int BLOCK_SIZE = 32;
const int TEXTURE_SIZE = 16;
struct Buttons {
	bool w, a, s, d, space;
};


struct Vector2
{
	int x;
	int y;
};

enum ItemsID
{
	AIR, STONE, DIRT, GRASS, PLANK,GLASS, NONE, BRICKWALL, TNT, NONE2, NONE3, WEB, FLOWER,NONE4,NONE5,NONE6,STONEWALL
};