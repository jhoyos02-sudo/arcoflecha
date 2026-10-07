#ifndef BALOON_H
#define BALOON_H

#include "rectangle.h"
#include "vector2D.h"
#include "texture.h"

enum Colores {
	AZUL,
	VERDE,
	NARANJA,
	ROJO,
	AMARILLO,
	ROSA,
	MORADO
};

class Baloon 
{
private:
	Rectangle hitbox;

	Colores color;

	Vector2D<float> velocidad;

	Texture* textura;

public:
	bool hit(const Rectangle& obj);
	void render() const;
	bool update(float delta);

};

#endif // BALOON_H
