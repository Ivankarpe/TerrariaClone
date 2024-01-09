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
            inventory.push_back({ AIR,0 });
            break;
        case 2:
            inventory.push_back({ AIR,0 });
            break;
        case 3:
            inventory.push_back({ AIR,0 });
            break;
        case 4:
            inventory.push_back({ AIR,0 });
            break;
        case 5:
            inventory.push_back({ AIR,0 });
            break;
        case 6:
            inventory.push_back({ AIR,0 });
            break;
        case 7:
            inventory.push_back({ AIR,0 });
            break;
        case 8:
            inventory.push_back({ AIR,0 });
            break;
        case 9:
            inventory.push_back({ AIR,0 });
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
        if (inventory[i].ID == item.ID) {
            firstEmptyIndex = i;
            break;
        }
    }
    if (firstEmptyIndex == -1) {

        for (size_t i = 0; i < size; i++)
        {
            if (inventory[i].ID == AIR) {
                firstEmptyIndex = i;
                break;
            }
        }
    }

    if (firstEmptyIndex == -1) {
        return false;
    }

    inventory[firstEmptyIndex].count += item.count;
    inventory[firstEmptyIndex].ID = item.ID;

    return true;
}

int Inventory::Place()
{
    if (GetActiveSlotItem().ID == AIR) {
    return false;

    }
    inventory[activeSlot].count -= 1;
    if (inventory[activeSlot].count < 0) {
        DeleteActiveItem();
    }
    return static_cast<int>(inventory[activeSlot].ID);
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

void Inventory::Render(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_Rect rect;
    rect.x = 25;
    rect.y = 25;
    rect.w = 408;
    rect.h = 48;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 10);
    SDL_RenderFillRect(renderer, &rect);
    TTF_Font* rFont = TTF_OpenFont("arial.ttf", 24);

    for (size_t i = 0; i < size; i++)
    {
        Item item = inventory[i];
        if (i == activeSlot) {
            SDL_Rect rect;
            rect.x = i * BLOCK_SIZE + (i + 1) * 8 + 25 - 4;
            rect.y = 25 + 8 - 4;
            rect.w = 40;
            rect.h = 40;

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 10);
            SDL_RenderFillRect(renderer, &rect);
        }
        int textureIndex = item.ID;
        SDL_Rect sours = { textureIndex % 16 * TEXTURE_SIZE , textureIndex / 16 * TEXTURE_SIZE ,TEXTURE_SIZE,TEXTURE_SIZE };
        SDL_Rect dest = { i * BLOCK_SIZE + (i + 1) * 8 + 25, 25 + 8, BLOCK_SIZE, BLOCK_SIZE };
        SDL_RenderCopy(renderer, texture, &sours, &dest);

        SDL_Surface* textSurface = TTF_RenderText_Solid(rFont, std::to_string(item.count).c_str(), SDL_Color(20, 20, 20));

        SDL_Rect abcPosition = { i * BLOCK_SIZE + (i + 1) * 8 + 25, 48,textSurface->w,textSurface->h };

        SDL_Texture* mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_RenderCopy(renderer, mTexture, NULL, &abcPosition);
    }







}
