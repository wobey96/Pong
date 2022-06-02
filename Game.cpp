#include "Game.h"


Game::Game()
{
	mWindow = nullptr; 
	mIsRunning = true; 
	std::cout << " Constructor Created " << std::endl; 
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO); 

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(" Pong", 100, 100, 1024, 768, 0); 

	if (!mWindow)
	{
		SDL_Log(" Failed to create window: %s ", SDL_GetError()); 
		return false; 
	}

	return true; 
}

void Game::HelloTest()
{
	std::cout << " Hello From Test func " << std::endl; 
}


void Game::ProcessInput()
{
	std::cout << " Call from ProcessInput Fucntion" << std::endl;
	SDL_Event event; 
	// While there are still events in the queue
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false; 
				break; 
			//default:
			//break;
		}
	}

	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL); 
	// If escape is pressed, also end loop 
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false; 
	}
}

void Game::UpdateGame()
{
	std::cout << " Call from UpdateGame Fucntion" << std::endl;
}

void Game::GenerateOutput()
{
	std::cout << " Call from GenerateOutput Fucntion" << std::endl; 
}



void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow); 
	SDL_Quit(); 
}

void Game::RunLoop()
{ 
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame(); 
		GenerateOutput(); 
	}
}