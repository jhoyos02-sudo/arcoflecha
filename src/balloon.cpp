#include "balloon.h"

using namespace std;

Balloon::Balloon(Rectangle h, int c, Vector2D<float> vel, Texture* text) {
	color = Colores(c);
	velocidad = vel;
	textura = text;
	hitbox = h;

	explotado = false;
}

bool 
Balloon::hit(const Rectangle& obj) {
	if (hitbox.hasIntersection(obj)) {
		explotado = true;
		return true;
	}
	else return false;
}

void
Balloon::render() const {
	textura->renderFrame(hitbox.to_sdl(), color, 0);
}

bool
Balloon::update(float delta) {
	// Mueve el globo teniendo en cuenta delta
	hitbox.move(velocidad * delta);

	// Si se sale del rango de la pantalla devuelve false
	if (hitbox.getTopLeftCorner().getY() + hitbox.getHeight() < 0) {
		return false;
	}

	if (explotado) {
		return false;
	}

	return true;
}

Balloon::~Balloon() {
	textura = nullptr;
}
