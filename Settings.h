#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_thread.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

const int MAP_WIDTH = 2000;
const int MAP_HEIGHT = 300;
const int FULLSCREEN = 0;
const int WATERCAPACITY = 500;
const int MAX_LIGHT = 10;

const int CAMERA_WIDTH = 1920;
const int CAMERA_HEIGHT = 1080;


const int coalOreChance = 45;
const int ironOreChance = 40;
const int goldOreChance = 35;
const int diamondOreChance = 30;
const int rubyOreChance = 28;
const int saphireOreChance = 28;


const int goldOreHight = 175;
const int diamondOreHight = 200;
const int rubyOreHight = 225;
const int saphireOreHight = 250;



const int BLOCK_SIZE = 32;

const int TEXTURE_SIZE = 16;



struct Buttons {
	bool w, a, s, d, c, space, left, right;
};
struct Vector2
{
	int x;
	int y;
};
struct Vector2f
{
	float x;
	float y;
};

enum ItemsID
{
	AIR, STONE, DIRT, GRASS, PLANK,GLASS, NONE, BRICKWALL, TNT, NONE2, NONE3, WEB, FLOWER,NONE4,NONE5,NONE6,STONEWALL,WOOD = 20,GOLD_ORE = 32,IRON_ORE,COAL_ORE,DIAMOND_ORE=50,RUBY_ORE,TORCH = 80, LEAF = 145,SAPHIRE_ORE=160, WATER = 205
};

enum Textures
{
	 loh, smoothGrass1, smoothGrass2, smoothGrass3, leftDiagonalGrass1 = 48, rightDiagonalGrass1, underLeftDiagonalGrass1 = 64, underRightDiagonalGrass1
};

struct block {
	ItemsID ID;
	bool colideable;
	float area = 0;
	int lightness = MAX_LIGHT-2;
	bool lightSource = false;
  Textures TEXTURE;
	bool top = 0;
};
