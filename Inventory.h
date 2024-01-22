#pragma once
#include <vector>
#include "Settings.h"
struct Item
{
	block ID;
	int count;
};
class Inventory
{
public:
	Inventory();

	bool PickUp(Item item);
	
	block Place();

	void ChangeActiveSlot(int slot);

	void DeleteActiveItem();

	int GetActiveSlotIndex();

	block GetActiveSlotItem();

	block GetSlotItem(int slot);

	int GetSize() { return size; }

	void Render(SDL_Renderer* renderer, SDL_Texture* texture);
private:

	int activeSlot;

	int size = 10;

	std::vector<Item> inventory;
};

