#pragma once
#include <vector>
#include "Settings.h"
struct Item
{
	ItemsID ID;
	int count;
};
class Inventory
{
public:
	Inventory();

	bool PickUp(Item item);
	int Place();

	void ChangeActiveSlot(int slot);

	void DeleteActiveItem();

	int GetActiveSlotIndex();

	Item GetActiveSlotItem();

	Item GetSlotItem(int slot);

	int GetSize() { return size; }

	void Render(SDL_Renderer* renderer, SDL_Texture* texture);
private:

	int activeSlot;

	int size = 10;

	std::vector<Item> inventory;
};

