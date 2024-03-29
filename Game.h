#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


// Holds Coordinates 
struct Vector2
{
	float x; 
	float y; 
};

class Game
{
	public:
		Game(); 
		// Initialize the game 
		bool Initialize(); 
		// Runs the game loop until the game is over
		void RunLoop(); 
		// Shutdown the game 
		void Shutdown(); 

		void HelloTest();
	private:
		// Helper functions for the game loop 
		void ProcessInput(); 
		void UpdateGame(); 
		void GenerateOutput(); 

		// Window created by SDL 
		SDL_Window* mWindow; 

		// Game should continue to run 
		bool mIsRunning; 

		// SDL Render Variable 
		SDL_Renderer* mRenderer; 

		// vectors for paddle position
		Vector2 mPaddlePos; 

		// vector for ball's position 
		Vector2 mBallPos; 

		//Frame Rate Calculation variable 
		Uint32 mTicksCount; 

		Vector2 mBallVel;

		// Direction of paddle
		int mPaddleDir;

};