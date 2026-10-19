#include "balloon.h"

using namespace std;

Balloon::Balloon(Rectangle h, int c, Vector2D<float> vel, Texture* text) {
	color = Colores(c);
	velocidad = vel;
	textura = text;
	hitbox = h;
}

bool 
Balloon::hit(const Rectangle& obj) {
	return hitbox.hasIntersection(obj);
}

void
Balloon::render() const {
	textura->renderFrame(hitbox.to_sdl(), color, 0);
}

bool
Balloon::update(float delta) {
	bool keep = true;
	hitbox.move(velocidad * delta);
	if (hitbox.getTopLeftCorner().getY() + hitbox.getHeight() < 0) {
		return false;
	}
	return keep;
}

Balloon::~Balloon() {
	textura = nullptr;
}
