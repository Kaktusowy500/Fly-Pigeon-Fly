#include <iostream>
#include <ctime>
#include "Menu.h"
#include "AssetsManager.h"
#include "StateManager.h"

int main() {
	srand(static_cast<unsigned>(time(NULL)));


	
	try {
		//Init 
		std::unique_ptr<StateManager> stateMan(new StateManager());
		std::unique_ptr<AssetsManager> assetsMan(new AssetsManager());

		assetsMan->loadTexturesFromFile("Textures/textures.txt", "Textures");
		assetsMan->loadFont("joyMono", "Fonts/joystix_monospace.ttf");
	
		//Add menu state, pass raw pointers to stateManager and assetsManager 
		stateMan->pushState(std::make_unique<Menu>(stateMan.get(),assetsMan.get()));

		// Game loop
		stateMan->gameLoop();
		}
	catch (AssetsManager::invalid_map_arg& e) {//recatch custom exception from get resource methods
		std::cout << e.what() << std::endl;
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what() << std::endl;
		}
	catch (std::bad_alloc& e) {
		std::cout <<"Allocation error: "<< e.what() << std::endl;
	}
	

	return 0;
}

/*TODO
menu exit
sounds
*/