#include "Game.h"

void Game::init()
{
	// Console title
	system("Title Snake-game-project-freestyle-240min");
	/*
	* change font to Lucinda console
	CONSOLE_FONT_INFOEX consoleFont;
	wcscpy(consoleFont.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(h, false, &consoleFont);
	*/

	// Для генерации случайных чисел - To generate random numbers
	srand(GetTickCount());

	// Разместить консоль с заданным размером по центру экрана
	// Place the console with the specified size in the center of the screen
	RECT rectConsole;
	GetWindowRect(GetConsoleWindow(), &rectConsole);
	SetWindowPos(GetConsoleWindow(), nullptr,
		GetSystemMetrics(SM_CXSCREEN) / 2 - WIDTH_IN_PX / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - HEIGHT_IN_PX / 2,
		WIDTH_IN_PX, HEIGHT_IN_PX, SWP_SHOWWINDOW);

	/*
	* Попытка создания адаптивной рамки, базирующейся на размер окна консоли
	* Attempt to create an adaptive frame based on the size of the console window
	*
	* Лучше использовать фиксированный размер
	* It is better to use fixed sizes

	for (size_t i = 0; i < WIDTH / 10 - 4; ++i) {
		SetConsoleCursorPosition(h, { (short)i, 0 });
		std::cout << "-";
		SetConsoleCursorPosition(h, { (short)i, 4 });
		std::cout << "-";
		SetConsoleCursorPosition(h, { (short)i, (short)((HEIGHT / 16 - 4) - 4) });
		std::cout << "-";
		SetConsoleCursorPosition(h, { (short)i, (short)(HEIGHT / 16 - 4) });
		std::cout << "-";
	}//for

	for(size_t i = 0; i <= HEIGHT / 16 - 4; ++i) {
		SetConsoleCursorPosition(h, { 0, (short)i });
		std::cout << "|";
		SetConsoleCursorPosition(h, { (short)(WIDTH / 10 - 5), (short)i });
		std::cout << "|";
	}//for

	// (WIDTH / 10 - 4) / 2 - середина экрана - middle of the screen
	SetConsoleCursorPosition(h, { (short)((WIDTH / 10 - 4) / 2 - 10), 2 });
	std::cout << "score: ";

	SetConsoleCursorPosition(h, { (short)((WIDTH / 10 - 4) / 2 - 10), (short)((HEIGHT / 16 - 4) - 2) });
	std::cout << "ESC - exit from game";
	*/

	/*
	* ----------
	* 
	* ----------
	*
	*
	* 
	* ----------
	*/
	for (short i = 0; i < WIDTH_IN_CELLS; ++i) {
		SetConsoleCursorPosition(h, { i, 0 });
		std::cout << "-";
		SetConsoleCursorPosition(h, { i, 4 });
		std::cout << "-";
		SetConsoleCursorPosition(h, { i, (short)(HEIGHT_IN_CELLS - 4) });
		std::cout << "-";
		SetConsoleCursorPosition(h, { i, HEIGHT_IN_CELLS });
		std::cout << "-";
	}//for

	/*
	* |----------|
	* |          |
	* |----------|
	* |          |
	* |          |
	* |          |
	* |----------|
	*/
	for (short i = 0; i <= HEIGHT_IN_CELLS; ++i) {
		SetConsoleCursorPosition(h, { 0, i });
		std::cout << "|";
		SetConsoleCursorPosition(h, { (short)(WIDTH_IN_CELLS - 1), i });
		std::cout << "|";
	}//for

	/*
	* |----------|
	* |	score:   |
	* |----------|
	* |          |
	* |          |
	* |          |
	* |----------|
	*/
	SetConsoleCursorPosition(h, { (short)(WIDTH_IN_CELLS / 2 - 10), 2 });
	std::cout << "score: ";

	SetConsoleCursorPosition(h, { (short)(WIDTH_IN_CELLS / 2 - 10), (short)(HEIGHT_IN_CELLS - 2) });
	std::cout << "ESC - exit from game";

	SetConsoleCursorPosition(h, { 35, 2 });
}//init()

void Game::loop()
{
	// Если flagGame == false, то бесконечный цикл с игрой прекращается
	// If flagGame == false, then the endless loop with the game stops
	int flagGame = true;

	// Случайное время до появления вкусняшки
	// Random time to spawn the yummy
	int time2yummy = random(1000, 3000);

	// Создание головы со случайными координатами
	// Creating a head with random coordinates
	snake.pushHead({ random(0,ROWS - 1), random(0, COLS - 1) });
	matrix[snake.head->coord.X][snake.head->coord.Y] = 1;

	// Бесконечный игровой цикл
	// Endless game cycle
	while (flagGame) {

		// Каждую итерацию цикла время до вкусняшки уменьшается
		// Each iteration of the cycle, the time to spawn the yummy is reduced
		time2yummy -= 100;
		if (time2yummy < 0) {
			// Генерация случайных координат вкусняшки
			// Generating random coordinates of a yummy
			COORD yummy_coord = { random(0, ROWS - 1), random(0, COLS - 1) };

			// Занесение вкусняшки в матрицу игрового поля
			// Adding yummy to the matrix of the playing field
			matrix[yummy_coord.X][yummy_coord.Y] = TYPEOFCELL::YUMMY;
			time2yummy = random(1000, 5000);

			// Отрисовка ячейки в консоли
			// Drawing a cell in the console
			drawCell(yummy_coord, TYPEOFCELL::YUMMY);
		}//if

		if (_kbhit() && (_getch())) {

			switch (_getch()) {

			// Реализована защита от дурака: нельзя двигаться в обратную сторону, если размер змейки > 1
			// Fool protection is implemented: cannot move in the opposite direction if the size of the snake is > 1				

			case VK_UP: case 72: case 'W': case 'w': case 'ц': case 'Ц':
				if (snake.dir == direction::DOWN && snake.head->next)
					break;
				snake.dir = direction::UP;
				break;

			case VK_DOWN: case 80: case 'S': case 's': case 'ы': case 'Ы':
				if (snake.dir == direction::UP && snake.head->next)
					break;
				snake.dir = direction::DOWN;
				break;

			case VK_LEFT: case 75: case 'A': case 'a': case 'ф': case 'Ф':
				if (snake.dir == direction::RIGHT && snake.head->next)
					break;
				snake.dir = direction::LEFT;
				break;

			case VK_RIGHT: case 77: case 'D': case 'd': case 'В': case 'в':
				if (snake.dir == direction::LEFT && snake.head->next)
					break;
				snake.dir = direction::RIGHT;
				break;

			case VK_RETURN: case 27:
				flagGame = false;
				break;
			} // switch arrows
		}//if

		// Шаг змеи в соответствии с направлением
		// Snake's step according to the direction
		snake.go();

		// Если наступили на вкусняшку, то змеюка растет
		// If you stepped on a yummy, then the snake grows
		if (matrix[snake.head->coord.X][snake.head->coord.Y] == TYPEOFCELL::YUMMY) {
			snake.pushTail();
			++score;
		}//if get yummy

		// Если укусили себя, то игра окончена
		// If you bite yourself, then the game is over
		if (matrix[snake.head->coord.X][snake.head->coord.Y] == TYPEOFCELL::SNAKE && snake.head->next) {
			flagGame = false;
		}////if get snake

		drawSnakeAfterGo();

		drawScore();
		Sleep(150);
	}//while

	SetConsoleCursorPosition(h, { (short)(WIDTH_IN_CELLS / 2 - 4), (short)(WIDTH_IN_CELLS / 4 + 4) });
	std::cout << "GAME OVER";

	SetConsoleCursorPosition(h, { 3 , (short)(HEIGHT_IN_CELLS - 5) });
	system("pause");
}//loop

short Game::random(int Lo, int Hi) { return Lo + rand() % (Hi - Lo + 1); }

void Game::fillMatrixZeros()
{
	for (size_t i = 0; i < ROWS; ++i)
		for (size_t j = 0; j < COLS; ++j)
			matrix[i][j] = TYPEOFCELL::NOTHING;
}//fillMatrixZeros

void Game::drawScore()
{
	SetConsoleCursorPosition(h, { 35, 2 });
	cout << score;
	SetConsoleCursorPosition(h, { 35, 2 });
}//drawScore

//old
void Game::drawMatrix()
{
	for (short i = 0; i < ROWS; ++i) {
		for (short j = 0; j < COLS; ++j) {
			SetConsoleCursorPosition(h, { (short)(1 + j), (short)(i + 5) });
			matrix[i][j] == 0 ? std::cout << " " : std::cout << matrix[i][j];
		}//for j
	}//for i
}

void Game::drawCell(COORD const& coord, TYPEOFCELL typeofcell, bool isSnakeHead)
{
	/*
	* Thnx https://stackoverflow.com/questions/17125440/c-win32-console-color
	BLACK             = 0,
	DARKBLUE          = FOREGROUND_BLUE,
	DARKGREEN         = FOREGROUND_GREEN,
	DARKCYAN          = FOREGROUND_GREEN | FOREGROUND_BLUE,
	DARKRED           = FOREGROUND_RED,
	DARKMAGENTA       = FOREGROUND_RED | FOREGROUND_BLUE,
	DARKYELLOW        = FOREGROUND_RED | FOREGROUND_GREEN,
	DARKGRAY          = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	GRAY              = FOREGROUND_INTENSITY,
	BLUE              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	GREEN             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	CYAN              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	RED               = FOREGROUND_INTENSITY | FOREGROUND_RED,
	MAGENTA           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	YELLOW            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	WHITE             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
	*/
	
	// +1 и +5 потому что ещё есть рамка, а отсчет ведется от левого верхнего края
	// +1 & +5 because there is still a frame, and the coord is from the upper left edge
	SetConsoleCursorPosition(h, { short(coord.Y + 1), short(coord.X + 5) });

	switch (typeofcell)
	{
	case NOTHING:
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::cout << " ";
		break;
	case SNAKE:
		isSnakeHead ? SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_GREEN)
			: SetConsoleTextAttribute(h, FOREGROUND_GREEN);
		std::cout << (char)219;
		break;
	case YUMMY:
		SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED);
		std::cout << (char)219;
		break;
	}//switch

	SetConsoleTextAttribute(h, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	SetConsoleCursorPosition(h, { 35, 2 });
}//drawCell

void Game::drawSnakeAfterGo()
{
	if (!snake.isEmpty()) {
		// Временная переменная для ходьбы по списку
		// Temp var for walking through the list
		SnakeNode* p = snake.head;

		// Отдельная отрисовка головы
		// Separate draw the head
		drawCell({ p->coord.X, p->coord.Y }, TYPEOFCELL::SNAKE, true);
		drawCell({ p->prev_coord.X, p->prev_coord.Y }, TYPEOFCELL::NOTHING);
		p = p->next;

		while (p) {
			// Последовательная отрисовка других элементов + занесение в матрицу игрового поля
			// Sequential rendering of other elements + entering into the matrix of the playing field
			drawCell({ p->coord.X, p->coord.Y }, TYPEOFCELL::SNAKE);
			drawCell({ p->prev_coord.X, p->prev_coord.Y }, TYPEOFCELL::NOTHING);

			matrix[p->prev_coord.X][p->prev_coord.Y] = 0;
			matrix[p->coord.X][p->coord.Y] = 1;
			p = p->next;
		}//while

	}//if
}//drawSnakeAfterGo

Game::~Game()
{
	delete[] matrix[0];
	delete[] matrix;
}//~Game

/*
void Game::drawSnakeAfterGo(Snake& SNAKE)
{
	if (!SNAKE.isEmpty()) {
		SnakeBlock* p = SNAKE.head;
		while (p) {
			// После сделаноо шага текущие коорд = 1
			SetConsoleCursorPosition(h, { (short)(1 + p->coord.Y), (short)(p->coord.X + 5) });
			std::cout << (char)219;
			// Предыдущие = 0
			SetConsoleCursorPosition(h, { (short)(1 + p->prev_coord.Y), (short)(p->prev_coord.X + 5) });
			std::cout << " ";

			//SetConsoleCursorPosition(h, { 0,0 });
			SetConsoleCursorPosition(h, { 35, 2 });

			matrix[p->prev_coord.X][p->prev_coord.Y] = 0;
			matrix[p->coord.X][p->coord.Y] = 1;
			p = p->next;

		}//while
	}//if
}
*/
//loop