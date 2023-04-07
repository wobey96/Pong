#include "Game.h"

const int thickness = 15; // thickness of walls 
const int SCREEN_MAX_WIDTH = 1024;
const float paddleH = 100.0f;

// getting back into this: Simple Test
// another simple test 12/30/2022
// Sample Test 04/05/2023

Game::Game()
{
	std::cout << " Constructor Created " << std::endl;



	mWindow = nullptr; 
	mIsRunning = true; 
	mRenderer = nullptr; 

	mTicksCount = 0;

	mBallPos.x = SCREEN_MAX_WIDTH / 2; 
	mBallPos.y = SCREEN_MAX_WIDTH / 2; 

	mPaddlePos.x = 0; 
	mPaddlePos.y = SCREEN_MAX_WIDTH / 2;

	mPaddleDir = 0;

}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO); 

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Creating the window
	mWindow = SDL_CreateWindow(" Pong", 100, 100, 1024, 768, 0); 
	if (!mWindow)
	{
		SDL_Log(" Failed to create window: %s ", SDL_GetError()); 
		return false; 
	}

	// Creating the renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ); // enabling vsync
	if (!mRenderer)
	{
		SDL_Log(" Failed to create renderer: %s ", SDL_GetError());
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

	mPaddleDir = 0; 
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1; 
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1; 
	}


}

void Game::UpdateGame()
{
	std::cout << " Call from UpdateGame Fucntion" << std::endl;

	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	
	// Delta Time is the difference in ticks from last screen converted to seconds
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f; 

	// Clamp maximum delta time value 
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// TODO: Update object in game world as functino of delta time!
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}

	// Update Tick counts (for next frame)
	mTicksCount = SDL_GetTicks(); 

	// TODO: Update object in game world as function of delta time 
	// update(deltaTime)
}

void Game::GenerateOutput()
{
	std::cout << " Call from GenerateOutput Fucntion" << std::endl; 

	// Graphics drawing code goes here
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255); // color screen 

	SDL_RenderClear(mRenderer); // clear back buffer to the current draw color

	/* Draw game world object here. Afer clearing back buffer but before swapping */

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); // drawing wall

	// Top Wall
	SDL_Rect wall{ 0, 0, SCREEN_MAX_WIDTH, thickness };
	SDL_RenderFillRect(mRenderer, &wall);

	// Bottom Wall
	wall.y = 768 - thickness; 
	SDL_RenderFillRect(mRenderer, &wall);

	// Right Wall
	wall.x = SCREEN_MAX_WIDTH - thickness;
	wall.y = 0; 
	wall.w = thickness; 
	wall.h = SCREEN_MAX_WIDTH; 
	SDL_RenderFillRect(mRenderer, &wall); 

	// Paddle 
	SDL_Rect paddle
	{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);


	// Ball
	SDL_Rect ball
	{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);




	SDL_RenderPresent(mRenderer); // sawap front and back buffer 

}



void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow); 
	SDL_Quit(); 
	SDL_DestroyRenderer(mRenderer); 
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