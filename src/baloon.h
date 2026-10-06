#ifndef BALOON_H
#define BALOON_H

#include "texture.h"
#include "rectangle.h"
#include "vector2D.h"

class Baloon 
{
	Rectangle hitbox;
	Texture textura;
	Vector2D velocidad;
};

#endif // BALOON_H
