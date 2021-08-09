#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int screenWidth, int ScreenHeight, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;

	int screenWidth = 600;
	int screenHeight = 600;


	int x_pos = 0;
	int y_pos = 0;

private:
	bool isRunning = false;
	bool menuOpen = true;
	bool enterPressed = false;
	int cnt = 0;
	int optionSelected = 0;
	SDL_Window* window;
};