//
// Tecnología de la Programación de Videojuegos 1
// Facultad de Informática UCM
//
// Plantilla de proyecto con SDL
//

#include "game.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	Game game;
	game.loadLevel(1);
	game.run();

	return 0;
}
