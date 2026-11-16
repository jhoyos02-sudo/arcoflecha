#include "game.h"

using namespace std;

// Constantes
constexpr const char* const WINDOW_TITLE = "Bow & Arrow 1.0";
constexpr const char* IMAGE_ROOT = "../assets/images/";
constexpr const char* LEVEL_ROOT = "../assets/levels/";
constexpr const float SCALE_FACTOR = 0.5f;
constexpr const float BALLON_SPEED_MIN = 0.2f; // Velocidad mínima de los globos
constexpr const float BALLON_SPEED_MAX = 0.5f; // Velocidad máxima de los globos
constexpr const float END_TIME = 2000; //Tiempo en milisegundos que tarda el juego en terminar una vez se acaban las flechas
constexpr const float BUTTERFLY_SIZE_FACTOR = 1.3f; // Factor de escala para las mariposas

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
	: exit(false)
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

	score.points = 0;
	score.texture = getTexture(SCORE);
	score.rect = Rectangle({ 130, 10 }, 10, 1);

	arrowTexture = getTexture(ARROW2);

	// Configura que se pueden utilizar capas translúcidas
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	randomGenerator = mt19937_64(random_device()()); // Inicializa el generador de números aleatorios

	spawnBalloon();

	bow = new Bow(Rectangle(Vector2D<float>(50, WINDOW_HEIGHT / 2), // Posición
		getTexture(BOW)->getFrameWidth() * SCALE_FACTOR, getTexture(BOW)->getFrameHeight() * SCALE_FACTOR), // Tamaño del arco
		Vector2D<float>(0, 0), // Velocidad inicial 
		getTexture(BOW)); // Textura del arco

}

void
Game::spawnBalloon() {
	int balloonWidth = getTexture(BALLOON)->getFrameWidth() * SCALE_FACTOR;
	int balloonHeight = getTexture(BALLOON)->getFrameHeight() * SCALE_FACTOR;

	int balloonX = uniform_int_distribution<int>(balloonWidth + 40, WINDOW_WIDTH - balloonWidth)(randomGenerator); // Posición aleatoria del globo

	float balloonSpeed = uniform_real_distribution<float>(BALLON_SPEED_MIN, BALLON_SPEED_MAX)(randomGenerator); // Velocidad aleatoria del globo

	Rectangle balloonRect(Vector2D<float>(balloonX, WINDOW_HEIGHT - balloonHeight), //Posición
		balloonWidth, balloonHeight); // Tamaño del globo

	int balloonColor = uniform_int_distribution<int>(0, getTexture(BALLOON)->getNumRows() - 1)(randomGenerator); // Color del globo

	balloons.push_back(new Balloon(balloonRect, Vector2D<float>(0, -(balspeed + balloonSpeed)), balloonColor, getTexture(BALLOON)));
}

void
Game::spawnButterflies() {
	int butterflyWidth = getTexture(BUTTERFLY)->getFrameWidth() * BUTTERFLY_SIZE_FACTOR;
	int butterflyHeight = getTexture(BUTTERFLY)->getFrameHeight() *  BUTTERFLY_SIZE_FACTOR;

	int butterflyX = uniform_int_distribution<int>(butterflyWidth, WINDOW_WIDTH - butterflyWidth)(randomGenerator); // Posición aleatoria de la mariposa
	int butterflyY = uniform_int_distribution<int>(butterflyHeight, WINDOW_HEIGHT - butterflyHeight)(randomGenerator); // Posición aleatoria de la mariposa
	Rectangle butterflyRect(Vector2D<float>(butterflyX, butterflyY), //Posición
		butterflyWidth, butterflyHeight); // Tamaño de la mariposa

	int butterflyDir = uniform_int_distribution<int>(0, 1)(randomGenerator); // Dirección de la mariposa

	int butterflyVelX = (butterflyDir == 0) ? -1 : 1; // Velocidad X de la mariposa

	int butterflyVelY = uniform_int_distribution<int>(0, 1)(randomGenerator) ? 1 : -1;; // Velocidad Y de la mariposa

	butterflies.push_back(new Butterfly(butterflyRect, Vector2D<float>(butterflyVelX, butterflyVelY), butterflyDir, getTexture(BUTTERFLY)));
}

void
Game::shootArrow() {
	Texture* arrowTexture = getTexture(ARROW);
	Rectangle bowCollider = bow->getCollider();

	Rectangle arrowCollider(Vector2D<float>(bowCollider.getTopLeftCorner().getX(), bowCollider.getTopLeftCorner().getY() + bowCollider.getHeight() * SCALE_FACTOR / 2 + arrowTexture->getFrameHeight() * SCALE_FACTOR / 2), // Posición
		arrowTexture->getFrameWidth() * SCALE_FACTOR, arrowTexture->getFrameHeight() * SCALE_FACTOR); // Tamaño de la flecha

	arrows.push_back(new Arrow(this, arrowCollider, Vector2D<float>(1, 0), arrowTexture));
	bow->arrowShot();
}

void
Game::render() const
{
	SDL_SetRenderDrawColor(renderer,
		static_cast<Uint8>(bgColor.red),
		static_cast<Uint8>(bgColor.green),
		static_cast<Uint8>(bgColor.blue),
		SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	for (int i = 0; i < balloons.size(); i++)
		balloons[i]->render();

	for (int i = 0; i < arrows.size(); i++)
		arrows[i]->render();

	for (int i = 0; i < butterflies.size(); i++)
		butterflies[i]->render();

	bow->render();

	int cifra, num, i = 0;
	num = score.points;
	while (num != 0) {
		cifra = num % 10;
		num /= 10;
		score.texture->renderFrame(Rectangle(score.rect.getTopLeftCorner() + Point2D<>(WINDOW_WIDTH - 300 - (score.texture->getFrameWidth() * i), 0),
			score.texture->getFrameWidth(),
			score.texture->getFrameHeight()).to_sdl(), 0, cifra);
		i++;
	}
	for (int j = 0; j < bow->getArrows(); j++) {
		SDL_Point centerArrow;
		centerArrow.x = arrowTexture->getFrameWidth() / 2;
		centerArrow.y = arrowTexture->getFrameWidth() / 2;
		arrowTexture->render(Rectangle(Point2D<>(100 + j * arrowTexture->getFrameHeight(), arrowTexture->getFrameHeight() + 50), arrowTexture->getFrameWidth(), arrowTexture->getFrameHeight()).to_sdl(), 90.0);
	}

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	if (bow->getArrows() <= 0 && !exit) {

		exit = true;
		endTime = END_TIME;
	}

	for (int i = 0; i < balloons.size(); i++) {
		if (!balloons[i]->update(FRAME_PERIOD)) {
			delete balloons[i];
			balloons.erase(balloons.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < arrows.size(); i++) {
		if (!arrows[i]->update(FRAME_PERIOD)) {
			delete arrows[i];
			arrows.erase(arrows.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < butterflies.size(); i++) {
		if (!butterflies[i]->update(FRAME_PERIOD)) {
			delete butterflies[i];
			butterflies.erase(butterflies.begin() + i);
			i--;
		}
	}

	if (SDL_GetTicks() % balloonDelay < FRAME_PERIOD) {
		spawnBalloon();
	}

	if (bow->isShootingArrow()) {
		shootArrow();
	}

	bow->update(FRAME_PERIOD);

	if (exit)
		endTime -= FRAME_PERIOD;
	else if (score.points >= goal) {
		loadLevel(++level);
	}

}

void
Game::run()
{
	for (int i = 0; i < numButterflies; i++) {
		spawnButterflies();
	}

	while (!exit || endTime > 0) {
		Uint32 start = SDL_GetTicks();

		handleEvents();
		update();
		render();

		Uint32 delta = SDL_GetTicks() - start;
		if (delta < FRAME_PERIOD)
			SDL_Delay(FRAME_PERIOD - delta);
	}
}

void
Game::loadLevel(int levelNumber) {
	try {
		ifstream isc(LEVEL_ROOT + std::to_string(levelNumber) + ".txt");
		if (!isc.is_open()) throw FileNotFoundError(LEVEL_ROOT + std::to_string(levelNumber) + ".txt");
		string read;
		int maxArrows = 0;

		while (!isc.eof())
		{
			isc >> read;
			if (read == "arrows")
				isc >> maxArrows;
			else if (read == "baldelay")
				isc >> balloonDelay;
			else if (read == "goal")
				isc >> goal;
			else if (read == "bgcolor")
				isc >> bgColor.red >> bgColor.green >> bgColor.blue;
			else if (read == "balspeed")
				isc >> balspeed;
			else if (read == "butterflies")
				isc >> numButterflies;
			else isc.ignore();
		}

		isc.close();

		if (maxArrows != 0 && balloonDelay != 0) {
			bow->loadArrows(maxArrows);
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
	if (!exit) {
		SDL_Event event;

		// Only quit is handled directly, everything else is delegated
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT)
				exit = true;
			bow->handleEvent(event);
		}
	}
}


void
Game::checkCollision(const Rectangle& rect)
{
	int i = 0;
	int j = 0;
	bool collisionDetected = false;

	while (i < balloons.size() && !collisionDetected) {
		collisionDetected = balloons[i]->hit(rect);
		if (collisionDetected) score.points++;
		++i;
	}

	while (j < butterflies.size() && !collisionDetected) {
		collisionDetected = butterflies[j]->hit(rect);
		if (collisionDetected && score.points > 0) score.points-=3;
		++j;
	}
}

Game::~Game()
{
	for (int i = 0; i < balloons.size(); i++) {
		delete balloons[i];
	}
	for (int i = 0; i < arrows.size(); i++) {
		delete arrows[i];
	}
	for (int i = 0; i < textures.size(); i++) {
		delete textures[i];
	}
	for (int i = 0; i < butterflies.size(); i++) {
		delete butterflies[i];
	}
	delete bow;

}