//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

#include "game.h"

int main(int argc, char* argv[])
{
	try {
		Game game('1');

		game.run();
	}

	catch (const std::exception& stdError) {
		std::cout << "Error: " << stdError.what() << std::endl;
	}

	catch (const char* sdlError) {
		std::cout << "Error de SDL: " << sdlError << std::endl;
	}

	catch (...) {
		std::cout << "Error desconocido" << std::endl;
	}

	return 0;
}
