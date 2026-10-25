#ifndef BOW_H
#define BOW_H

#include <SDL3/SDL.h>
#include "texture.h"
#include "rectangle.h"
#include "vector2D.h"
#include "game.h"

class Game;

class Bow 
{
private:
	Game* game;
	Rectangle hitbox;
	Vector2D<float> direccion;
	int numFlechas;
	bool armado;
	Texture* textura;

public:
	Bow(Game* g, Vector2D<float> topLeft, int nFlechas, Texture* textura);
	bool handleEvent(const SDL_Event& event);
	void render() const;
	bool update(float delta);
	Vector2D<float> getPos();
};

#endif // BOW_H
