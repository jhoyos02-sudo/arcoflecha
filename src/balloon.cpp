#include "balloon.h"

using namespace std;

Balloon::Balloon(Rectangle h, int c, Vector2D<float> vel, Texture* text) : color(Colores(c)), velocidad(vel), textura(text), hitbox(h) {
	explotado = false;

	lastDelta = 0;
	frame = 0;
	finAnim = false;

	frames_anim = 5;
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
	textura->renderFrame(hitbox.to_sdl(), color, frame);
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
		// Comprueba que ha pasado suficiente tiempo entre frames y ejecuta la animación
		if (lastDelta - delta > frames_anim) {
			if (frame < 5) frame++;
			else finAnim = true;

			// Resetea lastDelta para el siguiente frame de la animación
			lastDelta = 0;
		}
		
		lastDelta += delta;
	}

	// Cuando termina la animación destruye el globo
	if (finAnim) {
		return false;
	}

	return true;
}

Balloon::~Balloon() {
	textura = nullptr;
}
