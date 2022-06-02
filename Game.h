#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

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
		// Helper function for the game loop 
		void ProcessInput(); 
		void UpdateGame(); 
		void GenerateOutput(); 

		// Widdow created by SDL 
		SDL_Window* mWindow; 
		// Game should continue to run 
		bool mIsRunning; 
		// SDL Render Variable 
		SDL_Renderer* mRenderer; 
};