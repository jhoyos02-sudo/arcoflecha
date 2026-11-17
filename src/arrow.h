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
	Arrow(Game* g, const Rectangle& hit, const Vector2D<float>& vel, Texture* text);
	void render() const override;
	bool update(float delta) override;
};

#endif // ARROW_H
