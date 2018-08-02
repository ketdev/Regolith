#pragma once

#include <vector>

namespace core {

	// The game interface, implements all cross-platform logic 
	// the platform implementation should call these functions
	class Game {
	public:
		// Called on game start, initializes and starts the game logic
		Game();

		// Called on game end, saves and closes the state
		~Game();

		// Called in a loop to handle commands
		void eventLoop();

		// Called on received input from the user
		void input();

	private: // Systems

	};

}