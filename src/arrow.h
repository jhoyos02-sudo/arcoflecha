
#ifndef ARROW_H
#define ARROW_H

#include "vector2D.h"
#include "texture.h"
#include "rectangle.h"
#include "mobileObject.h"

class Game;

class Arrow : public mobileObject {
private:

public:
	Arrow(Game* game, const Rectangle& collider, const Vector2D<float>& velocidad, Texture* texture);

	void render() const override;

	bool update(float deltaTime) override;
};

#endif // ARROW_H
