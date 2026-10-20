#include "bow.h"

using namespace std;

Bow::Bow(Rectangle hit, Vector2D<float> dir, int nFlechas, Texture* text) {
	hitbox = hit;
	direccion = dir;
	numFlechas = nFlechas;
	armado = false;
	textura = text;
}

void
Bow::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
			case SDLK_W:
				if (hitbox.getTopLeftCorner().getY() >= 0) {
					direccion = Vector2D<float>(0, -1);
				}
				else direccion = Vector2D<float>(0, 0);
				break;

			case SDLK_S:
				if (hitbox.getTopLeftCorner().getY() + hitbox.getHeight() <= Game::WINDOW_HEIGHT) {
					direccion = Vector2D<float>(0, 1);
				}
				else direccion = Vector2D<float>(0, 0);
				break;

			case SDLK_A:
				armado = true;
				break;

			case SDLK_D:
				if (armado) {
					armado = false;
				}
				break;

			default: direccion = Vector2D<float>(0, 0);
		}
	}
	else direccion = Vector2D<float>(0, 0);


	// Ojala
	/*if (event.type == SDL_EVENT_KEY_UP) {
		direccion = Vector2D<float>(0, 0);
	}*/
}

void
Bow::render() const {
	textura->renderFrame(hitbox.to_sdl(), 0, !armado);	
}

bool
Bow::update(float delta) {
	bool keep = true;
	hitbox.move(direccion * delta);
	cout<< hitbox.getTopLeftCorner().getY()<<endl;
	return keep;
}
