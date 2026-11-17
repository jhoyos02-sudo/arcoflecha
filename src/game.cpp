#include "game.h"

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Bow & Arrow 1.0";
constexpr const char* IMAGE_ROOT = "../assets/images/";
constexpr const char* LEVEL_ROOT = "../assets/levels/";

// Estructura para especificar las texturas que hay que
// cargar y el tamaño de su matriz de frames
struct TextureSpec
{
	const char* name;
	int nrows = 1;
	int ncols = 1;
};

constexpr array<TextureSpec, Game::NUM_TEXTURES> textureList{
	TextureSpec{ "bow.png", 1, 2 },
	{ "arrow.png" },
	{ "arrow2.png" },
	TextureSpec{ "balloons.png", 7, 6 },
	TextureSpec{ "digits.png", 1, 10 },
	TextureSpec{ "butterfly.png", 4, 10 }
};



Game::Game()
	: fin(false)
{
	// Carga SDL y crea la ventana con su renderizador
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw SDLError();

	if (!SDL_CreateWindowAndRenderer(WINDOW_TITLE,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		0, &window, &renderer))
		throw SDLError();

	textures.fill(nullptr);
	string imgRoot = IMAGE_ROOT;

	for (size_t i = 0; i < textures.size(); i++) {
		auto [name, nrows, ncols] = textureList[i];
		textures[i] = new Texture(renderer, (imgRoot + name).c_str(), nrows, ncols);
		if (textures[i] == NULL) throw SDLError();
	}

	endTime = 0;

	marcador.puntos = 0;
	marcador.text = getTexture(DIGITS);
	marcador.rect = Rectangle({ 130, 10 }, 10, 1);

	texturaFlecha = getTexture(NUM_ARROWS);

	// Configura que se pueden utilizar capas translúcidas
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	random = mt19937_64(random_device()()); // Inicializa el generador de números aleatorios

	apareceGlobo();

	arco = new Bow(Rectangle(Vector2D<float>(50, WINDOW_HEIGHT / 2), // Posición
		getTexture(BOW)->getFrameWidth() * SCALE_FACTOR, getTexture(BOW)->getFrameHeight() * SCALE_FACTOR), // Tamaño del arco
		Vector2D<float>(0, 0), // Velocidad inicial 
		getTexture(BOW)); // Textura del arco

}

void
Game::apareceGlobo() {
	int globoAncho = getTexture(BALLOON)->getFrameWidth() * SCALE_FACTOR;
	int globoAlto = getTexture(BALLOON)->getFrameHeight() * SCALE_FACTOR;

	int globoX = uniform_int_distribution<int>(globoAncho + 40, WINDOW_WIDTH - globoAncho)(random); // Posición aleatoria del globo
	float globoVel = uniform_real_distribution<float>(COTA_INF_VEL, COTA_SUP_VEL)(random); // Velocidad aleatoria del globo

	Rectangle globoBox(Vector2D<float>(globoX, WINDOW_HEIGHT - globoAlto), //Posición
		globoAncho, globoAlto); // Tamaño del globo

	int globoColor = uniform_int_distribution<int>(0, getTexture(BALLOON)->getNumRows() - 1)(random); // Color del globo

	globos.push_back(new Balloon(globoBox, Vector2D<float>(0, -(globoVel + globoVel)), globoColor, getTexture(BALLOON)));
}

void
Game::apareceMariposas() {
	int mariAncho = getTexture(BUTTERFLY)->getFrameWidth() * BUTTERFLY_SIZE_FACTOR;
	int mariAlto = getTexture(BUTTERFLY)->getFrameHeight() *  BUTTERFLY_SIZE_FACTOR;

	int mariX = uniform_int_distribution<int>(mariAncho, WINDOW_WIDTH - mariAncho)(random); // Posición aleatoria de la mariposa
	int mariY = uniform_int_distribution<int>(mariAlto, WINDOW_HEIGHT - mariAlto)(random); // Posición aleatoria de la mariposa

	Rectangle mariBox(Vector2D<float>(mariX, mariY), //Posición
		mariAncho, mariAlto); // Tamaño de la mariposa

	int mariDir = uniform_int_distribution<int>(0, 1)(random);
	int mariVelX = (mariDir == 0) ? -1 : 1;
	int mariVelY = uniform_int_distribution<int>(0, 1)(random) ? 1 : -1;

	mariposas.push_back(new Butterfly(mariBox, Vector2D<float>(mariVelX, mariVelY), mariDir, getTexture(BUTTERFLY)));
}

void
Game::disparaFlecha() {
	Texture* arrowTexture = getTexture(ARROW);
	Rectangle bowCollider = arco->getHitbox();

	Rectangle arrowCollider(Vector2D<float>(bowCollider.getTopLeftCorner().getX(), bowCollider.getTopLeftCorner().getY() + bowCollider.getHeight() * SCALE_FACTOR / 2 + arrowTexture->getFrameHeight() * SCALE_FACTOR / 2), // Posición
		arrowTexture->getFrameWidth() * SCALE_FACTOR, arrowTexture->getFrameHeight() * SCALE_FACTOR); // Tamaño de la flecha

	flechas.push_back(new Arrow(this, arrowCollider, Vector2D<float>(1, 0), arrowTexture));
	arco->arrowShot();
}

void
Game::render() const
{
	SDL_SetRenderDrawColor(renderer,
		static_cast<Uint8>(bgColor.rojo),
		static_cast<Uint8>(bgColor.verde),
		static_cast<Uint8>(bgColor.azul),
		SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	for (int i = 0; i < globos.size(); i++)
		globos[i]->render();

	for (int i = 0; i < flechas.size(); i++)
		flechas[i]->render();

	for (int i = 0; i < mariposas.size(); i++)
		mariposas[i]->render();

	arco->render();

	int cifra, num, i = 0;
	num = marcador.puntos;
	while (num != 0) {
		cifra = num % 10;
		num /= 10;
		marcador.text->renderFrame(Rectangle(marcador.rect.getTopLeftCorner() + Point2D<>(WINDOW_WIDTH - 300 - (marcador.text->getFrameWidth() * i), 0),
			marcador.text->getFrameWidth(),
			marcador.text->getFrameHeight()).to_sdl(), 0, cifra);
		i++;
	}
	for (int j = 0; j < arco->getNumFlechas(); j++) {
		SDL_Point centroFlecha;
		centroFlecha.x = texturaFlecha->getFrameWidth() / 2;
		centroFlecha.y = texturaFlecha->getFrameWidth() / 2;
		texturaFlecha->render(Rectangle(Point2D<>(100 + j * texturaFlecha->getFrameHeight(), texturaFlecha->getFrameHeight() + 50), texturaFlecha->getFrameWidth(), texturaFlecha->getFrameHeight()).to_sdl(), 90.0);
	}

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	if (arco->getNumFlechas() <= 0 && !fin) {
		fin = true;
		endTime = END_TIME;
	}

	for (int i = 0; i < globos.size(); i++) {
		if (!globos[i]->update(FRAME_PERIOD)) {
			delete globos[i];
			globos.erase(globos.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < flechas.size(); i++) {
		if (!flechas[i]->update(FRAME_PERIOD)) {
			delete flechas[i];
			flechas.erase(flechas.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < mariposas.size(); i++) {
		if (!mariposas[i]->update(FRAME_PERIOD)) {
			delete mariposas[i];
			mariposas.erase(mariposas.begin() + i);
			i--;
		}
	}

	if (SDL_GetTicks() % globoRetardo < FRAME_PERIOD) {
		apareceGlobo();
	}

	if (arco->isShootingArrow()) {
		disparaFlecha();
	}

	arco->update(FRAME_PERIOD);

	if (fin) endTime -= FRAME_PERIOD;
	else if (marcador.puntos >= objetivo) {
		loadLevel(++nivel);
	}
}

void
Game::run()
{
	for (int i = 0; i < numMariposas; i++) {
		apareceMariposas();
	}

	while (!fin || endTime > 0) {
		Uint32 start = SDL_GetTicks();

		handleEvents();
		update();
		render();

		Uint32 delta = SDL_GetTicks() - start;
		if (delta < FRAME_PERIOD) SDL_Delay(FRAME_PERIOD - delta);
	}
}

void
Game::loadLevel(int levelNumber) {
	try {
		ifstream archivo(LEVEL_ROOT + std::to_string(levelNumber) + ".txt");
		if (!archivo.is_open()) throw FileNotFoundError(LEVEL_ROOT + std::to_string(levelNumber) + ".txt");

		string lectura;
		int maxArrows = 0;

		while (!archivo.eof())
		{
			archivo >> lectura;
			if (lectura == "arrows") archivo >> maxArrows;
			else if (lectura == "baldelay") archivo >> globoRetardo;
			else if (lectura == "goal") archivo >> objetivo;
			else if (lectura == "bgcolor") archivo >> bgColor.rojo >> bgColor.verde >> bgColor.azul;
			else if (lectura == "balspeed") archivo >> globoVel;
			else if (lectura == "butterflies") archivo >> numMariposas;
			else archivo.ignore();
		}

		archivo.close();

		if (maxArrows != 0 && globoRetardo != 0) {
			arco->loadArrows(maxArrows);
		}
		else throw FileFormatError(LEVEL_ROOT + std::to_string(levelNumber) + ".txt", "Invalid format");
	}
	catch (FileNotFoundError& e) {
		cout << e.what() << endl;
	}
	catch (FileFormatError& e) {
		cout << e.what() << endl;
	}
	catch (SDLError& e) {
		cout << e.what() << endl;
	}
}

void
Game::handleEvents()
{
	if (!fin) {
		SDL_Event event;

		// Only quit is handled directly, everything else is delegated
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT)
				fin = true;
			arco->handleEvent(event);
		}
	}
}


void
Game::checkCollision(const Rectangle& rect)
{
	int i = 0;
	int j = 0;
	bool collisionDetected = false;

	while (i < globos.size() && !collisionDetected) {
		collisionDetected = globos[i]->hit(rect);
		if (collisionDetected) marcador.puntos++;
		++i;
	}

	while (j < mariposas.size() && !collisionDetected) {
		collisionDetected = mariposas[j]->hit(rect);
		if (collisionDetected && marcador.puntos > 0) marcador.puntos-=3;
		++j;
	}
}

Game::~Game()
{
	for (int i = 0; i < globos.size(); i++) {
		delete globos[i];
	}
	for (int i = 0; i < flechas.size(); i++) {
		delete flechas[i];
	}
	for (int i = 0; i < textures.size(); i++) {
		delete textures[i];
	}
	for (int i = 0; i < mariposas.size(); i++) {
		delete mariposas[i];
	}
	delete arco;
}
