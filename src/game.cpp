#include "game.h"
#include <string>
#include <SDL3_image/SDL_image.h>
#include "texture.h"

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Bow & Arrow 1.0";
constexpr const char* IMAGE_ROOT = "../assets/images/";
constexpr const char* LEVEL_ROOT = "../assets/levels/";

constexpr const float ESCALA_GLOBOS = 0.4f;
constexpr const float ESCALA_ARCOFLECHA = 0.3f;
constexpr const int NUM_FLECHAS = 3;

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{"bow.png", 1, 2},
	{"arrow.png"},
	TextureSpec{"balloons.png", 7, 6},
	TextureSpec{"digits.png", 1, 10}

};

Game::Game()
  : exit(false)
{
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw "SDL_Init: "s + SDL_GetError();

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
	                                 WINDOW_WIDTH, WINDOW_HEIGHT,
	                                 0, &window, &renderer))
		throw "window or renderer: "s + SDL_GetError();

	// Carga las texturas al inicio
	try {
		textures.fill(nullptr);
		string imgRoot = IMAGE_ROOT;

		for (size_t i = 0; i < textures.size(); i++) {
			auto [name, nrows, ncols] = textureList[i];
			textures[i] = new Texture(renderer, (imgRoot + name).c_str(), nrows, ncols);
		}
	}
	catch (...) {
		// TODO: liberar la memoria reservada
		throw; // relanza la excepción
	}

	// Configura que se pueden utilizar capas translúcidas
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	// TODO: crear los objetos del juego
	arco = new Bow(Rectangle(Vector2D<>(0, WINDOW_HEIGHT / 2), getTexture(BOW)->getFrameWidth() * ESCALA_ARCOFLECHA, getTexture(BOW)->getFrameHeight() * ESCALA_ARCOFLECHA), Vector2D<float>(0, 0), NUM_FLECHAS, getTexture(BOW)); // Provisional porque es horrible

	random = mt19937_64(random_device()());
}

Game::~Game()
{
	// TODO: liberar la memoria reservada por la clase
}

void
Game::render() const
{
	SDL_RenderClear(renderer);

	// Renderiza el arco
	arco->render();

	// Renderiza todos los globos que hay en la escena
	for (int i = 0; i < globos.size(); i++) {
		globos[i]->render();
	}

	// Renderiza todas las flechas que hay en la escena
	for (int i = 0; i < flechas.size(); i++) {
		flechas[i]->render();
	}

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	
	// Actualiza el estado de todos los globos de la escena
	for (int i = 0; i < globos.size(); i++) {
		if (!globos[i]->update(FRAME_PERIOD)) { // Si el globo se encuentra fuera de la pantalla lo elimina de la lista
			delete globos[i];
			globos.erase(globos.begin() + i); 
			i--;
		}
	}

	// Actualiza el estado del arco
	arco->update(FRAME_PERIOD);

	// Actualiza el estado de todas las flechas de la escena
	for (int i = 0; i < flechas.size(); i++) {
		if (!flechas[i]->update(FRAME_PERIOD)) { // Si la flecha se encuentra fuera de la pantalla lo elimina de la lista
			delete flechas[i];
			flechas.erase(flechas.begin() + i);
			i--;
		}
	}

	if(SDL_GetTicks() % 500 < FRAME_PERIOD) apareceGlobo(); // Aparecen globos una vez por segundo
}

void
Game::run()
{

	while (!exit) {
		Uint32 start = SDL_GetTicks();

		handleEvents();
		update();
		render();

		Uint32 delta = SDL_GetTicks() - start;
		if (delta < FRAME_PERIOD) SDL_Delay(FRAME_PERIOD - delta);
	}
}

void
Game::handleEvents()
{
	SDL_Event event;

	// Only quit is handled directly, everything else is delegated
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			exit = true;

		if (arco->handleEvent(event)) {
			disparaFlecha(arco->getPos());
		}
	}
}

bool
Game::checkCollision(const Rectangle& rect)
{
	// TODO
	return false;
}

void
Game::apareceGlobo() {
	// Define el tamaño del globo en función del tamaño de la textura y la constante de escala
	int globoAncho = getTexture(BALLOON)->getFrameWidth() * ESCALA_GLOBOS;
	int globoAlto = getTexture(BALLOON)->getFrameHeight() * ESCALA_GLOBOS;
	 
	// Randomiza la posición en x en función de el tamaño del globo y la pantalla,y la velocidad del globo 
	int globoX = uniform_int_distribution<int>(globoAncho, WINDOW_WIDTH - globoAncho)(random);
	float globoVel = uniform_real_distribution<float>(0.1f, 1.5f)(random);

	// Con los parámetros anteriores crea un collider rectangular en la parte inferior de la pantalla
	Rectangle globoBox(Vector2D<float>(globoX, WINDOW_HEIGHT - globoAlto), globoAncho, globoAlto);

	// Randomiza el color del globo en función de las filas que tenga la textura
	int globoColor = uniform_int_distribution<int>(0, getTexture(BALLOON)->getNumRows() - 1)(random);

	// Con todo lo anterior crea un objeto de tipo globo y lo agrega a la lista de globos de la escena
	globos.push_back(new Balloon(globoBox, globoColor, Vector2D<float>(0, -globoVel), getTexture(BALLOON)));
}

void
Game::disparaFlecha(Vector2D<float> pos) {
	int flechaAlto = getTexture(ARROW)->getFrameWidth() * ESCALA_ARCOFLECHA;
	int flechaAncho = getTexture(ARROW)->getFrameHeight() * ESCALA_ARCOFLECHA;

	Vector2D<float> flechaVel = Vector2D<float>(3, 0);

	Rectangle flechaBox(Vector2D<float>(pos.getX(), pos.getY() + (getTexture(BOW)->getFrameHeight()  - getTexture(ARROW)->getFrameHeight()) * ESCALA_ARCOFLECHA / 2.0), flechaAlto, flechaAncho);

	flechas.push_back(new Arrow(this, flechaBox, flechaVel, getTexture(ARROW)));
}
