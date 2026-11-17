#include "balloon.h"
#include "game.h"

Balloon::Balloon(const Rectangle& h, const Vector2D<float>& vel, int c, Texture* text)	
	: mobileObject(vel, h, text, nullptr), color(c), explotado(false), frame(0) { }

bool 
Balloon::hit(const Rectangle& obj) {
	if (hitbox.hasIntersection(obj) && !explotado) {
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
	mobileObject::update(delta);

	if (explotado && (SDL_GetTicks() % FRAMES_ANIMACION < Game::FRAME_PERIOD)) {
		velocidad = Vector2D<float>(0, 0);
		frame++;
		if (frame >= 6) 
			 return false;
	}
	
	if (hitbox.getTopLeftCorner().getY() < 0) {
		return false;
	}

	return true;
}

