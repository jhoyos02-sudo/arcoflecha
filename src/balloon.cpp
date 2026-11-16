#include "balloon.h"
#include "game.h"

Balloon::Balloon(const Rectangle& rect, const Vector2D<float>& vel, int color, Texture* texture)	
	: mobileObject(vel, rect, texture, nullptr), color(color), exploded(false), animationFrame(0) { }

bool 
Balloon::hit(const Rectangle& obj) {
	bool collision = collider.hasIntersection(obj);

	if (collision && !exploded) {
		exploded = true;
		return collision;
	}
	else return false;

}

void
Balloon::render() const {
	texture->renderFrame(collider.to_sdl(), color, animationFrame);
}

bool
Balloon::update(float delta) {

	mobileObject::update(delta);


	if (exploded && (SDL_GetTicks() % ANIMATION_RATE < Game::FRAME_PERIOD)) {
		velocidad = Vector2D<float>(0, 0);
		animationFrame++;
		if (animationFrame >= 6) 
			 return false;
	}
	
	if (collider.getTopLeftCorner().getY() < 0) {
		return false;
	}

	return true;
}

