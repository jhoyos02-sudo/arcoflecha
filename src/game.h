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

	static constexpr float SCALE_FACTOR = 0.5f;
	static constexpr float BUTTERFLY_SIZE_FACTOR = 1.3f;

	static constexpr float COTA_INF_VEL = 0.2f;
	static constexpr float COTA_SUP_VEL = 0.5f;

	static constexpr float END_TIME = 2000;
	
	enum TextureName
	{
		BOW = 0,
		ARROW,
		NUM_ARROWS,	
		BALLOON,
		DIGITS,
		BUTTERFLY,
		NUM_TEXTURES
	};

private:
	std::mt19937_64 random;

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	Bow* arco;
	std::vector<Arrow*> flechas;
	std::vector<Balloon*> globos;
	std::vector<Butterfly*> mariposas;

	void render() const;
	void update();
	void handleEvents();
	void apareceGlobo();
	void apareceMariposas();
	void disparaFlecha();

	struct Marcador {
		int puntos;
		Rectangle rect;
		Texture* text;
	};	

	struct BgColor {
		int rojo;
		int verde;
		int azul;
	};

	Marcador marcador;
	Texture* texturaFlecha;
	BgColor bgColor;
	int globoRetardo;
	int objetivo;
	int nivel;
	int numMariposas;
	int globoVel;
	int endTime;
	bool fin;

	// Elemento del juego

public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	void loadLevel(int nivel);

	// Comprueba si hay algún objeto colocado en ese rectángulo
	void checkCollision(const Rectangle& rect);
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
