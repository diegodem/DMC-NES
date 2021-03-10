#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <cmath>
#include <vector>
#include "Player.h"
#include "Timer.h"
#include "Projectile.h"
#include "Enemy.h"
#include "State.h"
#include "Kirzos.h"
#include "Olril.h"
#include "Unnath.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 896;

const int RESOLUTION_WIDTH = 256;
const int RESOLUTION_HEIGHT = 224;

bool init();

void close();

bool loadMedia();

static bool checkCollision(SDL_Rect *rectA, SDL_Rect *rectB);

void gameOver(bool *quit);

SDL_Texture *loadTexture(std::string path);

SDL_Window *gWindow = NULL;

SDL_Renderer *gRenderer = NULL;

TTF_Font *gFontBig = NULL;

TTF_Font* gFontMed = NULL;

SDL_Texture* gTexturePlayer[6] = { 0 };

SDL_Texture* gTextureProj[2] = { 0 };

SDL_Texture* gTextureEnemies[10] = { 0 };

SDL_Texture* gTextureBackground[4] = { 0 };

Player p1;

std::vector<Projectile> projectiles;

std::vector<Enemy> enemies;

Timer deltaTime;

Timer spawnTimer;

int nextEnemy;

int i, j;

SDL_Rect healthRect;
SDL_Rect maxHealthRect;

SDL_Rect backgroundRect;
SDL_Rect moonRect;

Mix_Chunk* gGunSound;
Mix_Chunk* gSwordSound;
Mix_Chunk* gHealSound;
Mix_Chunk* gHurtSound;
Mix_Chunk* gCantShootSound;
Mix_Chunk* gHitSound;

bool init()
{
	srand(time(NULL));
	//Initialization flag
	bool success = true;

	p1 = Player();

	maxHealthRect = { 16, 16, p1.getMaxHealth(), 8 };
	healthRect = { 16, 16, p1.getHealth(), 8 };

	backgroundRect = { 0, 0, 8, 8 };

	moonRect = { 232, 200, 16, 16 };

	int randomEnemy = rand() % 10;

	nextEnemy = rand() % 2 + 1;

	if (randomEnemy < 5)
	{
		enemies.push_back(Kirzos());
	}
	else if (randomEnemy < 8)
	{
		enemies.push_back(Olril());
	}
	else
	{
		enemies.push_back(Unnath());
	}


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

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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
	gTexturePlayer[0] = loadTexture("Sprites/alig_gun_r.png");
	if (gTexturePlayer[0] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[1] = loadTexture("Sprites/alig_gun_r2.png");
	if (gTexturePlayer[1] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[2] = loadTexture("Sprites/alig_gun_l.png");
	if (gTexturePlayer[2] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[3] = loadTexture("Sprites/alig_gun_l2.png");
	if (gTexturePlayer[3] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[4] = loadTexture("Sprites/alig_sword_attack_r.png");
	if (gTexturePlayer[4] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTexturePlayer[5] = loadTexture("Sprites/alig_sword_attack_l.png");
	if (gTexturePlayer[5] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureProj[0] = loadTexture("Sprites/proj_l.png");
	if (gTextureProj[0] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureProj[1] = loadTexture("Sprites/proj_r.png");
	if (gTextureProj[1] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[0] = loadTexture("Sprites/kirzos_l.png");
	if (gTextureEnemies[0] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[1] = loadTexture("Sprites/kirzos_l2.png");
	if (gTextureEnemies[1] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[2] = loadTexture("Sprites/olril_l.png");
	if (gTextureEnemies[2] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[3] = loadTexture("Sprites/olril_l2.png");
	if (gTextureEnemies[3] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[4] = loadTexture("Sprites/unnath_l.png");
	if (gTextureEnemies[4] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[5] = loadTexture("Sprites/kirzos_r.png");
	if (gTextureEnemies[5] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[6] = loadTexture("Sprites/kirzos_r2.png");
	if (gTextureEnemies[6] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[7] = loadTexture("Sprites/olril_r.png");
	if (gTextureEnemies[7] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[8] = loadTexture("Sprites/olril_r2.png");
	if (gTextureEnemies[8] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureEnemies[9] = loadTexture("Sprites/unnath_r.png");
	if (gTextureEnemies[9] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureBackground[0] = loadTexture("Sprites/floor.png");
	if (gTextureBackground[0] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureBackground[1] = loadTexture("Sprites/floor_2.png");
	if (gTextureBackground[1] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureBackground[2] = loadTexture("Sprites/brick.png");
	if (gTextureBackground[2] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gTextureBackground[3] = loadTexture("Sprites/moon_2.png");
	if (gTextureBackground[3] == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	gFontBig = TTF_OpenFont("Fonts/Caveat-Bold.ttf", 40);
	gFontMed = TTF_OpenFont("Fonts/Pixeled.ttf", 5);

	gGunSound = Mix_LoadWAV("Sounds/gun.wav");
	if (gGunSound == NULL)
	{
		printf("Failed to load gun sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gSwordSound = Mix_LoadWAV("Sounds/sword.wav");
	if (gSwordSound == NULL)
	{
		printf("Failed to load gun sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gHealSound = Mix_LoadWAV("Sounds/heal.wav");
	if (gHealSound == NULL)
	{
		printf("Failed to load gun sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gHurtSound = Mix_LoadWAV("Sounds/hurt.wav");
	if (gHurtSound == NULL)
	{
		printf("Failed to load gun sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gHitSound = Mix_LoadWAV("Sounds/hit.wav");
	if (gHitSound == NULL)
	{
		printf("Failed to load gun sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gCantShootSound = Mix_LoadWAV("Sounds/cantShoot.wav");
	if (gCantShootSound == NULL)
	{
		printf("Failed to load gun sound effect! SDL_mixer Error: %s\n", Mix_GetError());
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
	TTF_CloseFont(gFontBig);
	TTF_CloseFont(gFontMed);
	Mix_FreeChunk(gGunSound);
	Mix_FreeChunk(gSwordSound);
	gWindow = NULL;
	gRenderer = NULL;
	gFontBig = NULL;
	gFontMed = NULL;
	gGunSound = NULL;
	gSwordSound = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

static bool checkCollision(SDL_Rect *rectA, SDL_Rect *rectB)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = rectA->x;
	rightA = rectA->x + rectA->w;
	topA = rectA->y;
	bottomA = rectA->y + rectA->h;

	//Calculate the sides of rect B
	leftB = rectB->x;
	rightB = rectB->x + rectB->w;
	topB = rectB->y;
	bottomB = rectB->y + rectB->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
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
				if (spawnTimer.getTime() >= nextEnemy)
				{
					int randomEnemy = rand() % 10;

					nextEnemy = rand() % 2 + 1;
					spawnTimer.start();

					if (randomEnemy < 5)
					{
						enemies.push_back(Kirzos());
					}
					else if (randomEnemy < 8)
					{
						enemies.push_back(Olril());
					}
					else
					{
						enemies.push_back(Unnath());
					}
				}
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type == SDL_KEYDOWN)
					{
						if (e.key.keysym.sym == SDLK_q)
						{
							p1.heal();
							Mix_PlayChannel(-1, gHealSound, 0);
							maxHealthRect.w = p1.getMaxHealth();
							healthRect.w = p1.getHealth();
						}
					}

				}
				const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
				p1.update();
				if (currentKeyStates[SDL_SCANCODE_Z])
				{
					int attackResult = p1.attackSword();
					
					if (attackResult)
					{
						Mix_PlayChannel(-1, gSwordSound, 0);

						for (i = 0; i < enemies.size(); i++)
						{
							if (checkCollision(p1.getSwordRect(), enemies[i].getRect()))
							{
								enemies[i].takeDamage(p1.getSwordDamage());
								enemies[i].pushBack(16, attackResult);
								Mix_PlayChannel(-1, gHitSound, 0);
								if (enemies[i].getHealth() <= 0)
								{
									enemies.erase(enemies.begin() + i);
									i--;
								}
							}
						}
					}
					
				}
				else if (currentKeyStates[SDL_SCANCODE_X])
				{
					if (p1.getState() == STANDING_RIGHT || p1.getState() == MOVING_RIGHT)
					{
						if (p1.getCanShoot())
						{
							projectiles.push_back(Projectile(p1.getRect()->x, 1));
							Mix_PlayChannel(-1, gGunSound, 0);
						}
						else
						{
							Mix_PlayChannel(-1, gCantShootSound, 0);
						}
						
					}
					else if (p1.getState() == STANDING_LEFT || p1.getState() == MOVING_LEFT)
					{
						if (p1.getCanShoot())
						{
							projectiles.push_back(Projectile(p1.getRect()->x, 0));
							Mix_PlayChannel(-1, gGunSound, 0);
						}
						else
						{
							Mix_PlayChannel(-1, gCantShootSound, 0);
						}
						
					}
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
				

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0x88, 0x88, 0x88, 0xFF);
				SDL_RenderClear(gRenderer);

				for (i = 0; i < 28; i++)
				{
					backgroundRect.y = i * 8;
					for (j = 0; j < 32; j++)
					{
						backgroundRect.x = j * 8;

						SDL_RenderCopy(gRenderer, gTextureBackground[2], NULL, &backgroundRect);

					}
				}

				for (i = 0; i < 4; i++)
				{
					backgroundRect.y = 192 + i * 8;
					for (j = 0; j < 32; j++)
					{
						backgroundRect.x = j * 8;

						SDL_RenderCopy(gRenderer, gTextureBackground[(i + j) % 2], NULL, &backgroundRect);
						//SDL_RenderCopy(gRenderer, gTextureBackground[0], NULL, &backgroundRect);

					}
				}

				SDL_SetRenderDrawColor(gRenderer, 0xeb, 0xeb, 0xeb, 0xFF);
				SDL_RenderFillRect(gRenderer, &moonRect);

				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderDrawRect(gRenderer, &moonRect);

				SDL_RenderCopy(gRenderer, gTextureBackground[3], NULL, &moonRect);



				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, &maxHealthRect);
				

				SDL_SetRenderDrawColor(gRenderer, 0x49, 0xaa, 0x10, 0xFF);
				SDL_RenderFillRect(gRenderer, &healthRect);

				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
				SDL_RenderDrawRect(gRenderer, &maxHealthRect);

				for (i = 0; i < projectiles.size(); i++)
				{
					projectiles[i].update(deltaTime.getTime());
					SDL_RenderCopy(gRenderer, gTextureProj[projectiles[i].getFrame()], NULL, projectiles[i].getRect());
					for (j = 0; j < enemies.size(); j++)
					{
						if (checkCollision(projectiles[i].getRect(), enemies[j].getRect()))
						{
							enemies[j].takeDamage(32);
							Mix_PlayChannel(-1, gHitSound, 0);
							(projectiles[i].getFrame() == 1) ? enemies[j].pushBack(8, 1) : enemies[j].pushBack(8, 0);
							break;
							
						}
						
					}
					//printf("%d", j);
					if (j < enemies.size())
					{
						projectiles.erase(projectiles.begin() + i);
						i--;
						if (enemies[j].getHealth() <= 0)
						{
							enemies.erase(enemies.begin() + j);
						}
					}
				}
				for (i = 0; i < enemies.size(); i++)
				{
					enemies[i].update(deltaTime.getTime());
					SDL_RenderCopy(gRenderer, gTextureEnemies[enemies[i].getCurrentFrame()], NULL, enemies[i].getRect());
					//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
					//SDL_RenderFillRect(gRenderer, enemies[i].getRect());
				}
				if (p1.getImmunityState() < 2)
				{
					if (p1.getCurrentFrame() > 3)
					{
						SDL_RenderCopy(gRenderer, gTexturePlayer[p1.getCurrentFrame()], NULL, p1.getAttackRect());
					}
					else
					{
						SDL_RenderCopy(gRenderer, gTexturePlayer[p1.getCurrentFrame()], NULL, p1.getRect());
					}
				}
				
				if (deltaTime.getTime() >= 1.f / 60.f)
				{
					deltaTime.start();
				}

				
				



				//Update screen
				SDL_RenderPresent(gRenderer);

				for (i = 0; i < enemies.size(); i++)
				{
					if (checkCollision(enemies[i].getRect(), p1.getRect()))
					{
						if (p1.getImmunityState() == 0)
						{
							Mix_PlayChannel(-1, gHurtSound, 0);
						}
						p1.takeDamage(32);
						healthRect.w = p1.getHealth();
						if (p1.getHealth() <= 0)
						{
							gameOver(&quit);
						}
					}

				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

void gameOver(bool *quit)
{
	//Event handler
	SDL_Event e;

	bool restart = false;

	

	SDL_Color color = { 178, 16, 48 };
	SDL_Surface* surfaceGameOver = TTF_RenderText_Solid(gFontMed,"GAME OVER", color);
	SDL_Texture* textureGameOver = SDL_CreateTextureFromSurface(gRenderer, surfaceGameOver);
	SDL_Rect gameOverRect = { 106, 64, surfaceGameOver->w, surfaceGameOver->h };

	SDL_Surface* surfacePressStart = TTF_RenderText_Solid(gFontMed, "Press START (W) to try again...", color);
	SDL_Texture* texturePressStart = SDL_CreateTextureFromSurface(gRenderer, surfacePressStart);
	SDL_Rect pressStartRect = { 64, 128, surfacePressStart->w, surfacePressStart->h };

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	//SDL_RenderFillRect(gRenderer, &gameOverRect);
	SDL_RenderCopy(gRenderer, textureGameOver, NULL, &gameOverRect);
	//SDL_RenderFillRect(gRenderer, &pressStartRect);
	SDL_RenderCopy(gRenderer, texturePressStart, NULL, &pressStartRect);
	SDL_RenderPresent(gRenderer);

	//While application is running
	while (!*quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				*quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_w)
				{
					restart = true;
				}
			}

		}
		if (restart)
		{
			p1 = Player();

			maxHealthRect.w = p1.getMaxHealth();

			healthRect.w = p1.getHealth();

			enemies.clear();

			deltaTime.start();

			int randomEnemy = rand() % 10;

			if (randomEnemy < 5)
			{
				enemies.push_back(Kirzos());
			}
			else if (randomEnemy < 8)
			{
				enemies.push_back(Olril());
			}
			else
			{
				enemies.push_back(Unnath());
			}
			break;
		}
	}
	SDL_DestroyTexture(textureGameOver);
	SDL_DestroyTexture(texturePressStart);
	SDL_FreeSurface(surfacePressStart);
	SDL_FreeSurface(surfaceGameOver);
}