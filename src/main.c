#include "SDL2/SDL.h"

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define PARTICLESIZE 5

#define WIDTH 161
#define HEIGHT 161

#define EMPTY 1
#define SAND 2

#define FRAMERATE 60

int init();

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int grid[WIDTH][HEIGHT];
int privateGrid[WIDTH][HEIGHT];

const int frameRate = FRAMERATE;
const int frameDelay = 1000 / frameRate;

void initGrids()
{
	for (int i = 0; i < WIDTH - 1; i++)
	{
		for (int j = 0; j < HEIGHT - 1; j++)
		{
			privateGrid[i][j] = EMPTY;
			grid[i][j] = EMPTY;
		}
	}
	printf("Grids initialized\n");
}

void update()
{
	for (int i = 0; i < WIDTH - 2; i++)
	{
		for (int j = 0; j < HEIGHT - 1; j++)
		{
			if (privateGrid[i][j] == SAND)
			{
				// If below is empty
				if (privateGrid[i][j + 1] == EMPTY)
				{
					grid[i][j] = EMPTY;
					grid[i][j + 1] = SAND;
				}
				else if (privateGrid[i - 1][j + 1] == EMPTY && privateGrid[i + 1][j + 1] == EMPTY)
				{
					bool direction = rand() % 2;
					if (direction == 0) {
						// left
						grid[i][j] = EMPTY;
						grid[i - 1][j + 1] = SAND;
					}
					else if (direction == 1) {
						grid[i][j] = EMPTY;
						grid[i + 1][j + 1] = SAND;
					}
				}
				/*
					If only below and left is empty, move there.
				*/
				else if (privateGrid[i - 1][j + 1] == EMPTY)
				{
					grid[i][j] = EMPTY;
					grid[i - 1][j + 1] = SAND;
				}
				/*
					If only below and right is empty, move there.
				*/
				else if (privateGrid[i + 1][j + 1] == EMPTY)
				{
					grid[i][j] = EMPTY;
					grid[i + 1][j + 1] = SAND;
				}
			}
		}
	}
}

void draw()
{ 
	for (int i = 0; i < WIDTH - 1; i++)
	{
		for (int j = 0; j < HEIGHT - 1; j++)
		{
			if (grid[i][j] == SAND) {
				SDL_Rect rect;
				rect.w = PARTICLESIZE;
				rect.h = PARTICLESIZE;

				rect.x = i  * PARTICLESIZE;
				rect.y = j  * PARTICLESIZE;

				SDL_SetRenderDrawColor(ren, 194, 178, 128, 255);
				SDL_RenderFillRect(ren, &rect);
			}

			privateGrid[i][j] = grid[i][j];
		}
	}
}

void placeParticle(int type, int x, int y)
{
	if (grid[x][y] == EMPTY) {
		grid[x][y] = type;
	}
}
int main(int argc, char** argv)
{
	if(init() != 0)
	{
		printf("Failed to initialize program\n");
		return -1;
	} else printf("Program initialized\n");
	 
	// Main loop
	SDL_Event event;
	bool quit = false;
	bool lbheld = false;
	bool rbheld = false;

	Uint32 frameStart;
	int frameTime;
	
	int fps = 0;
	
	while(!quit)
	{
		frameStart = SDL_GetTicks();

		while(SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							quit = true;
							break;
					}
					break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					lbheld = true;
				}
				break;

				case SDL_MOUSEBUTTONUP:
				lbheld = false;
				rbheld = false;
			}
		}
		int x, y;
		SDL_GetMouseState(&x, &y);

		if (lbheld)
		{
			placeParticle(SAND, x / PARTICLESIZE, y / PARTICLESIZE);
		}


		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);

		update();
		draw();

		SDL_RenderPresent(ren);

		frameTime = SDL_GetTicks() - frameStart;    

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	// Cleanup
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);

	SDL_Quit();

	return 0;

}

int init()
{
	initGrids();

	//Create all SDL resources, terminating the program if any fail to create
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Failed to initialize SDL\nSDL Error: %s\n", SDL_GetError());
		return 1;
	}

	win = SDL_CreateWindow(
		"SDL2 Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (!win)
	{
		printf("Failed to create SDL Window\nSDL Error: %s\n", SDL_GetError());
		return 1;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if(!ren)
	{
		printf("Failed to create SDL Renderer\nSDL Error: %s\n", SDL_GetError());
		return 1;
	}

	return 0;
}
