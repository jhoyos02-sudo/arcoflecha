#include "bow.h"
#include "arrow.h"
#include "vector2D.h"
#include "game.h"

using namespace std;

Bow::Bow(const Rectangle& hit, const Vector2D<float>& vel, Texture* text)
	: sceneObject(hit, text, nullptr), armado(false), disparaFlecha(false), numFlechas(0), velocidad(vel) { }

void
Bow::handleEvent(const SDL_Event& event) {
	if (event.type == SDL_EVENT_KEY_DOWN) {
		switch (event.key.key) {
		case SDLK_UP:
			velocidad = Vector2D<float>(0, -1);
			break;
		case SDLK_DOWN:
			velocidad = Vector2D<float>(0, 1); 
			break;
		case SDLK_LEFT:
			if (numFlechas>0) armado = true;
			break;
		case SDLK_RIGHT:
			if (armado) {
				armado = false;
				disparaFlecha = true;
			}
			break;
		default:
			break;
		}
	}
	else velocidad = Vector2D<float>(0, 0);
}

void
Bow::render() const {
	textura->renderFrame(hitbox.to_sdl(), 0, !armado);
}

bool
Bow::update(float delta){
	if (hitbox.getTopLeftCorner().getY() + hitbox.getHeight() + velocidad.getY() * delta * VEL < Game::WINDOW_HEIGHT && 
		hitbox.getTopLeftCorner().getY() + velocidad.getY() * delta * VEL > 0) 
		hitbox.move(velocidad * delta * VEL);
	return true;
}

void 
Bow::arrowShot() {
	disparaFlecha = false;
	numFlechas--;
}


