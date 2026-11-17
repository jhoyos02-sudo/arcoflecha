#include "butterfly.h"
#include "game.h"

Butterfly::Butterfly(const Rectangle& hit, const Vector2D<float>& vel, int dir, Texture* text)
	: mobileObject(vel, hit, text, nullptr), direccion(dir), muerto(false), frame(0), random(std::mt19937_64(std::random_device()())) {
}

bool
Butterfly::hit(const Rectangle& obj) {
	if (hitbox.hasIntersection(obj) && !muerto) {
		muerto = true;
		return true;
	}
	else return false;
}

void
Butterfly::render() const {
	textura->renderFrame(hitbox.to_sdl(), direccion, frame);
}

bool
Butterfly::update(float delta) {

	mobileObject::update(delta*VEL_MARIPOSA);

	if (muerto) {
		velocidad = Vector2D<float>(0, 2);
		if (hitbox.getTopLeftCorner().getY() + hitbox.getHeight() > Game::WINDOW_HEIGHT) return false;
	}
	else {

		if (hitbox.getTopLeftCorner().getY() < 0) {
			velocidad = Vector2D<float>(velocidad.getX(), 1);
		}

		if (hitbox.getTopLeftCorner().getY() + hitbox.getHeight() > Game::WINDOW_HEIGHT) {
			velocidad = Vector2D<float>(velocidad.getX(), -1);
		}

		if (hitbox.getTopLeftCorner().getX() < 0) {
			velocidad = Vector2D<float>(1, velocidad.getY());
			direccion = 3; 
			frame = 0; 
		}

		if (hitbox.getTopLeftCorner().getX() + hitbox.getWidth() > Game::WINDOW_WIDTH) {
			velocidad = Vector2D<float>(-1, velocidad.getY());
			direccion = 2;
			frame = 0; 
		}

		if(std::uniform_int_distribution<int>(0, 99)(random) < 5) { 
			direccion = 3 - (direccion%2); 
			velocidad = Vector2D<float>((direccion == 2) ? -1 : 1, velocidad.getY());
		}
		frame++;
		frame %= 10;
		finGiro();
	}

	return true;
}

void
Butterfly::finGiro() {
	if (direccion == 2 && frame == 9) {
		direccion = 0; 
	}
	else if (direccion == 3 && frame == 9) {
		direccion = 1; 
	}
}
