#include "GameObject.h"
#include "TextureManager.h"



GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	x_pos = x;
	y_pos = y;
}

void GameObject::Update(int x_pos, int y_pos, int screenWidth, int screenHeight)
{
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = x_pos;
	destRect.y = y_pos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

	std::cout << destRect.x << ", " << destRect.y << std::endl;

	if (destRect.x < (screenWidth - screenWidth - 5))
	{
		destRect.x = screenWidth - screenWidth - 5;
	}

	if (destRect.x > (screenWidth - srcRect.w))
	{
		destRect.x = screenWidth + 10;
	}

	if (destRect.y < (screenHeight - screenHeight - 5))
	{
		destRect.y = screenHeight - screenHeight - 5;
	}

	if (destRect.y > (screenHeight - (srcRect.h * 2)))
	{
		destRect.y = screenHeight - (srcRect.h * 2);
	}
}


void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject()
{

}