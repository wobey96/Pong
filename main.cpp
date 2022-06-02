#include <iostream>
#include "Game.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello World " << std::endl;
	Game game; 
	game.HelloTest(); 
	bool success = game.Initialize(); 

	if (success)
	{
		game.RunLoop(); 
	}

	game.Shutdown(); 
	return 0; 
}