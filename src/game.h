#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>	
#include <random>
#include "rectangle.h"
#include "arrow.h"
#include "balloon.h"
#include "bow.h"
#include <string>
#include <SDL3_image/SDL_image.h>

#include "butterfly.h"
#include "texture.h"
#include "vector2D.h"
#include "gameError.h"
#include "fileFormatError.h"
#include "fileNotFoundError.h"
#include "sdlError.h"
#include <fstream>

// Declaraciones anticipadas
class Texture;
class Balloon;
class Bow;
class Arrow;
class Butterfly;

/**
 * Clase principal del juego.
 */
class Game
{
public:
	// Número de actualizaciones por segundo
	static constexpr int FRAME_RATE = 30;
	// Periodo entre actualizaciones en milisegundos
	static constexpr int FRAME_PERIOD = 1000 / FRAME_RATE;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 1200;
	static constexpr int WINDOW_HEIGHT = 900;
	static constexpr int SCORE_X = 900;
	static constexpr int SCORE_Y = 900;

	enum TextureName
	{
		BOW = 0,
		ARROW,
		ARROW2,	
		BALLOON,
		SCORE,
		BUTTERFLY,
		NUM_TEXTURES
	};

private:
	std::mt19937_64 randomGenerator;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Bow* bow;
	std::vector<Arrow*> arrows;
	std::vector<Balloon*> balloons;
	std::vector<Butterfly*> butterflies;
	std::array<Texture*, NUM_TEXTURES> textures;

	void render() const;
	void update();
	void handleEvents();
	void spawnBalloon();
	void spawnButterflies();
	void shootArrow();

	struct Score {
		int points;
		Rectangle rect;
		Texture* texture;
	};	

	struct BgColor {
		int red;
		int green;
		int blue;
	};

	Score score;
	Texture* arrowTexture;
	BgColor bgColor;
	int balloonDelay;
	int goal;
	int level;
	int numButterflies;
	int balspeed;
	int endTime;
	bool exit;

	// Elemento del juego

public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	void loadLevel(int levelNumber);

	// Comprueba si hay algún objeto colocado en ese rectángulo
	void checkCollision(const Rectangle& rect);
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
