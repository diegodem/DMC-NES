#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "Player.h"
#include "Timer.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 896;

const int RESOLUTION_WIDTH = 256;
const int RESOLUTION_HEIGHT = 224;

bool init();

void close();

bool loadMedia();

SDL_Texture *loadTexture(std::string path);

SDL_Window *gWindow = NULL;

SDL_Renderer *gRenderer = NULL;

SDL_Texture* gTexturePlayer[6] = { 0 };

Player p1 = Player();

Timer deltaTime;

bool init()
{
	//Initialization flag
	bool success = true;


	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
	
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_RenderSetLogicalSize(gRenderer, RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexturePlayer[0] = loadTexture("Sprites/Dante_gun_r.png");
	if (gTexturePlayer[0] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[1] = loadTexture("Sprites/Dante_gun_r2.png");
	if (gTexturePlayer[1] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[2] = loadTexture("Sprites/Dante_gun_l.png");
	if (gTexturePlayer[2] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[3] = loadTexture("Sprites/Dante_gun_l2.png");
	if (gTexturePlayer[3] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[4] = loadTexture("Sprites/Dante_sword_attack_r.png");
	if (gTexturePlayer[4] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[5] = loadTexture("Sprites/Dante_sword_attack_l.png");
	if (gTexturePlayer[5] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}

SDL_Texture* loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{

		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

				}
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				p1.update();
				if (currentKeyStates[SDL_SCANCODE_Z])
				{
					p1.attackSword();
				}
				else if (currentKeyStates[SDL_SCANCODE_X])
				{
					p1.fire();
				}
				else if (currentKeyStates[SDL_SCANCODE_LEFT])
				{
					p1.moveLeft(deltaTime.getTime());
				}
				else if (currentKeyStates[SDL_SCANCODE_RIGHT])
				{
					p1.moveRight(deltaTime.getTime());
				}
				else
				{
					p1.noButtonPressed();
				}
				if (deltaTime.getTime() >= 1.f / 100.f)
				{
					deltaTime.start();
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, p1.getAttackRect());
				if (p1.getCurrentFrame() > 3)
				{
					SDL_RenderCopy(gRenderer, gTexturePlayer[p1.getCurrentFrame()], NULL, p1.getAttackRect());
				}
				else
				{
					SDL_RenderCopy(gRenderer, gTexturePlayer[p1.getCurrentFrame()], NULL, p1.getRect());
				}
				



				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}