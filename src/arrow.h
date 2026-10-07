#ifndef ARROW_H
#define ARROW_H

#include "rectangle.h"
#include "vector2D.h"
#include "game.h"

class Arrow 
{
private:
	Game* game;

	Rectangle hitbox;

	Vector2D<float> velocidad;

	Texture* textura;

public:
	void render() const;
	bool update(float delta);

};

#endif // ARROW_H
