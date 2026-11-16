#include "butterfly.h"
#include "game.h"

Butterfly::Butterfly(const Rectangle& rect, const Vector2D<float>& vel, int dir, Texture* texture)
	: mobileObject(vel, rect, texture, nullptr), direction(dir), shot(false), animationFrame(0), randomGenerator(std::mt19937_64(std::random_device()())) {
}

bool
Butterfly::hit(const Rectangle& obj) {
	bool collision = collider.hasIntersection(obj);

	if (collision && !shot) {
		shot = true;
		return collision;
	}
	else return false;

}

void
Butterfly::render() const {
	texture->renderFrame(collider.to_sdl(), direction, animationFrame);
}

bool
Butterfly::update(float delta) {

	mobileObject::update(delta*BUTTERFLY_SPEED);

	if (shot) {
		velocidad = Vector2D<float>(0, 2);
		if (collider.getTopLeftCorner().getY() + collider.getHeight() > Game::WINDOW_HEIGHT) return false;
	}
	else {

		if (collider.getTopLeftCorner().getY() < 0) {
			velocidad = Vector2D<float>(velocidad.getX(), 1);
		}

		if (collider.getTopLeftCorner().getY() + collider.getHeight() > Game::WINDOW_HEIGHT) {
			velocidad = Vector2D<float>(velocidad.getX(), -1);
		}

		if (collider.getTopLeftCorner().getX() < 0) {
			velocidad = Vector2D<float>(1, velocidad.getY());
			direction = 3; // Cambiar la dirección a derecha
			animationFrame = 0; // Reiniciar el frame de animación
		}

		if (collider.getTopLeftCorner().getX() + collider.getWidth() > Game::WINDOW_WIDTH) {
			velocidad = Vector2D<float>(-1, velocidad.getY());
			direction = 2; // Cambiar la dirección a izquierda
			animationFrame = 0; // Reiniciar el frame de animación
		}

		if(std::uniform_int_distribution<int>(0, 99)(randomGenerator) < 5) { // 5% de probabilidad de cambiar de dirección
			direction = 3 - (direction%2); // Cambiar la dirección
			velocidad = Vector2D<float>((direction == 2) ? -1 : 1, velocidad.getY());
		}

		animationFrame++;
		animationFrame %= 10;
		returnDir();
	}

	return true;

}

void
Butterfly::returnDir() {

	if (direction == 2 && animationFrame == 9) {
		direction = 0; // Cambiar la dirección a izquierda
	}
	else if (direction == 3 && animationFrame == 9) {
		direction = 1; // Cambiar la dirección a derecha
	}
	
}