#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	void Update(int x_pos, int y_pos, int screenWidth, int screenHeight);
	void Render();

	SDL_Rect srcRect, destRect;

private:
	bool isColliding;
	int x_pos;
	int y_pos;

	SDL_Texture* objTexture;

};