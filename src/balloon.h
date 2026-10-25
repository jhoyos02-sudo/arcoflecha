#ifndef BALLOON_H
#define BALLOON_H

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

class Balloon 
{
private:
	Rectangle hitbox;
	Colores color;
	Vector2D<float> velocidad;
	Texture* textura;

	bool explotado;

	float lastDelta;
	int frame;
	bool finAnim;
	Uint8 frames_anim;

public:
	
	Balloon(Rectangle h, int c, Vector2D<float> vel, Texture* text);
	bool hit(const Rectangle& obj);
	void render() const;
	bool update(float delta);
	~Balloon();

};

#endif // BALLOON_H
