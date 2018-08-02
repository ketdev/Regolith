#include <regolith/core/game.h>
#include <stdio.h> 

namespace core {

	Game::Game() {
		printf("Game()\n");
	}

	Game::~Game() {
		printf("~Game()\n");

	}

	void Game::eventLoop() {

	}

	void Game::input() {
		printf("input()\n");
	}

}