#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include <random>
#include <fstream>
#include <string>

// #include "rectangle.h"
#include "balloon.h"
#include "arrow.h"
#include "bow.h"

// Declaraciones anticipadas
class Texture;
class Balloon;
class Arrow;
class Bow;

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

	// Parámetros del juego
	static constexpr float ESCALA_GLOBOS = 0.4f;
	static constexpr float ESCALA_ARCOFLECHA = 0.3f;
	static constexpr float VELOCIDAD_FLECHA = 2;

	enum TextureName
	{
		BOW = 0,
		ARROW,
		BALLOON,
		DIGITS,
		NUM_TEXTURES
	};

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;

	void render() const;
	void update();
	void handleEvents();

	bool exit;

	// Elemento del juego
	std::vector<Balloon*> globos;
	std::vector<Arrow*> flechas;
	int globoRetardo;
	int nFlechas;
	Bow* arco;

	std::mt19937_64 random;

public:
	Game(char niv);
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	bool checkCollision(const Rectangle& rect);

	void apareceGlobo();
	void disparaFlecha(Vector2D<float> pos);

	bool loadLevel(char nivel);
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
