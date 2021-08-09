#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "map.h"

#include "ECS.h"
#include "Components.h"

#include <map>

GameObject* player;
GameObject* largeEnemy;

Map* map;

SDL_Renderer* Game::renderer = nullptr;

const Uint8* SDL_GetKeyboardState(int* numkeys);
const Uint8* state = SDL_GetKeyboardState(NULL);

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int screenWidth, int screenHeight, bool fullscreen)
{
	int flags = 0;


	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	player = new GameObject("assets/player_character.png", 0, 0);
	largeEnemy = new GameObject("assets/LargeGuard.png", 128, 128);
	map = new Map();

	newPlayer.addComponent<PositionComponent>();
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	if (menuOpen)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			optionSelected -= 1;
			enterPressed = false;
			break;
		case SDLK_s:
			optionSelected += 1;
			enterPressed = false;
			break;
		case SDLK_RETURN:
			enterPressed = true;
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	SDL_PumpEvents();
	SDL_KeyboardEvent* key;

	std::cout << optionSelected << std::endl;

	if (menuOpen)
	{
		if ((optionSelected == 0) && (enterPressed))
		{
			menuOpen = false;
		}

		else if ((optionSelected == 1) && (enterPressed))
		{
			SDL_QUIT;
		}

		else if (optionSelected > 1)
		{
			optionSelected = 1;
		}

		else if (optionSelected < 0)
		{
			optionSelected = 0;
		}
	}

	else if ((menuOpen == false) && (enterPressed))
	{
		if ((state[SDL_SCANCODE_D]) || (state[SDL_SCANCODE_RIGHT]))
		{
			if (state[SDL_SCANCODE_LSHIFT])
			{
				player->Update(x_pos++, y_pos, screenWidth, screenHeight);
			}
			player->Update(x_pos++, y_pos, screenWidth, screenHeight);
		}

		if ((state[SDL_SCANCODE_A]) || (state[SDL_SCANCODE_LEFT]))
		{
			if (state[SDL_SCANCODE_LSHIFT])
			{
				player->Update(x_pos--, y_pos, screenWidth, screenHeight);
			}
			player->Update(x_pos--, y_pos, screenWidth, screenHeight);
		}

		if ((state[SDL_SCANCODE_W]) || (state[SDL_SCANCODE_UP]))
		{
			if (state[SDL_SCANCODE_LSHIFT])
			{
				player->Update(x_pos, y_pos--, screenWidth, screenHeight);
			}
			player->Update(x_pos, y_pos--, screenWidth, screenHeight);
		}

		if ((state[SDL_SCANCODE_S]) || (state[SDL_SCANCODE_DOWN]))
		{
			if (state[SDL_SCANCODE_LSHIFT])
			{
				player->Update(x_pos, y_pos++, screenWidth, screenHeight);
			}
			player->Update(x_pos, y_pos++, screenWidth, screenHeight);
		}


		if (x_pos < (screenWidth - screenWidth - 5))
		{
			x_pos = screenWidth - screenWidth - 5;
		}

		if (x_pos > (screenWidth - (player->srcRect.w * 2)))
		{
			x_pos = screenWidth - (player->srcRect.w * 2);
		}

		if (y_pos < (screenHeight - screenHeight - 5))
		{
			y_pos = screenHeight - screenHeight - 5;
		}

		if (y_pos > (screenHeight - (player->srcRect.h * 2)))
		{
			y_pos = screenHeight - (player->srcRect.h * 2);
		}
	}
	manager.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	if ((menuOpen == false) && (enterPressed))
	{
		map->DrawMap();
		player->Render();
		largeEnemy->Render();
	}
	SDL_RenderPresent(renderer);
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}