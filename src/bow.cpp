#include "bow.h"

using namespace std;



Bow::Bow(Game* g, Vector2D<float> topLeft, int nFlechas, Texture* text) : game(g), numFlechas(nFlechas), textura(text) {
	armado = false;
	direccion = Vector2D<float>(0, 0);
	hitbox = Rectangle(topLeft, text->getFrameHeight() * Game::ESCALA_ARCOFLECHA, text->getFrameWidth() * Game::ESCALA_ARCOFLECHA);
}

bool
Bow::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_W:
				direccion = Vector2D<float>(0, -1);
				break;

			case SDLK_S:
				direccion = Vector2D<float>(0, 1);
				break;

			case SDLK_A:
				if (numFlechas > 0) {
					armado = true;
					numFlechas--;
				}
				break;

			case SDLK_D:
				if (armado) {
					armado = false;
					return true;
				}
				break;

			default: direccion = Vector2D<float>(0, 0);
		}
	}
	else direccion = Vector2D<float>(0, 0);

	return false;
}

void
Bow::render() const {
	textura->renderFrame(hitbox.to_sdl(), 0, !armado);	
}

bool
Bow::update(float delta) {
	bool keep = true;

	if (hitbox.moved(direccion * delta).getTopLeftCorner().getY() >= 0 && hitbox.moved(direccion * delta).getTopLeftCorner().getY() + hitbox.getHeight() <= Game::WINDOW_HEIGHT) {
		hitbox.move(direccion * delta);
	}

	return keep;
}

Vector2D<float>
Bow::getPos() {
	return hitbox.getTopLeftCorner();
}
