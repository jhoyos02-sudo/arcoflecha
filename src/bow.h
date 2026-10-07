#ifndef BOW_H
#define BOW_H

#include <SDL3/SDL.h>
#include "texture.h"
#include "rectangle.h"
#include "vector2D.h"

class Bow 
{
private:
	Rectangle hitbox;

	Vector2D<float> direccion;

	int numFlechas;

	bool armado;

	Texture* textura;

public:
	void handleEvent(const SDL_Event& event);
	void render() const;
	bool update(float delta);

};

#endif // BOW_H
