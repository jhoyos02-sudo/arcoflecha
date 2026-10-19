#include "bow.h"

using namespace std;

Bow::Bow(Rectangle hit, Vector2D<float> dir, int nFlechas, bool arm, Texture* text) {
	hitbox = hit;
	direccion = dir;
	numFlechas = nFlechas;
	armado = arm;
	textura = text;
}

void
Bow::handleEvent(const SDL_Event& event) {

}

void
Bow::render() const {
	textura->render(hitbox.to_sdl());
}

bool
Bow::update(float delta) {
	bool keep = true;

	return keep;
}
