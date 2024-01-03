#include "Inventory.h"

Inventory::Inventory() {
    for (size_t i = 0; i < size; i++)
    {
        switch (i)
        {
        case 0:
            inventory.push_back({ AIR,0 });
            break;
        case 1:
            inventory.push_back({ STONE,0 });
            break;
        case 2:
            inventory.push_back({ DIRT,0 });
            break;
        case 3:
            inventory.push_back({ GRASS,0 });
            break;
        case 4:
            inventory.push_back({ PLANK,0 });
            break;
        case 5:
            inventory.push_back({ GLASS,0 });
            break;
        case 6:
            inventory.push_back({ NONE,0 });
            break;
        case 7:
            inventory.push_back({ BRICKWALL,0 });
            break;
        case 8:
            inventory.push_back({ TNT,0 });
            break;
        case 9:
            inventory.push_back({ NONE2,0 });
            break;
        default:
            inventory.push_back({ AIR,0 });
            break;
        }
    }

}

bool Inventory::PickUp(Item item)
{
    int firstEmptyIndex = -1;
    for (size_t i = 0; i < size; i++)
    {
        if (inventory[i].ID == AIR || inventory[i].ID == item.ID) {
            firstEmptyIndex = i;
            break;
        }
    }

    if (firstEmptyIndex == -1) {
        return false;
    }

    inventory[firstEmptyIndex].count += item.count;
    inventory[firstEmptyIndex].ID = item.ID;

    return true;
}

void Inventory::ChangeActiveSlot(int slot)
{
    activeSlot = slot%size;
    if (activeSlot < 0) {
        activeSlot = size-1;
    }
}

void Inventory::DeleteActiveItem()
{
    inventory[activeSlot] = { AIR,0 };
}

int Inventory::GetActiveSlotIndex()
{
    return activeSlot;
}

Item Inventory::GetActiveSlotItem()
{
    return inventory[activeSlot];
}

Item Inventory::GetSlotItem(int slot)
{
    return inventory[slot];
}
