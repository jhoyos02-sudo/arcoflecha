#include "bow.h"
#include "arrow.h"
#include "vector2D.h"
#include "game.h"

using namespace std;

Bow::Bow(const Rectangle& collider, const Vector2D<float>& velocity, Texture* texture)
	: sceneObject(collider, texture, nullptr), isArmed(false), shootArrow(false), arrows(0), velocity(velocity) { }

void
Bow::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_UP:
			velocity = Vector2D<float>(0, -1);
			break;
		case SDLK_DOWN:
			velocity = Vector2D<float>(0, 1); 
			break;
		case SDLK_LEFT:
			if (arrows>0) isArmed = true;
			break;
		case SDLK_RIGHT:
			if (isArmed) {
				isArmed = false;
				shootArrow = true;
			}
			break;
		default:
			break;
		}
	}
	else velocity = Vector2D<float>(0, 0);
}

void
Bow::render() const {
	texture->renderFrame(collider.to_sdl(), 0, !isArmed);
}

bool
Bow::update(float deltaTime){
	if (collider.getTopLeftCorner().getY() + collider.getHeight() + velocity.getY() * deltaTime * SPEED < Game::WINDOW_HEIGHT && 
		collider.getTopLeftCorner().getY() + velocity.getY() * deltaTime * SPEED > 0) 
		collider.move(velocity * deltaTime * SPEED);
	return true;
}

void 
Bow::arrowShot() {
	shootArrow = false;
	arrows--;
}


