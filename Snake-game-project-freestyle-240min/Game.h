#pragma once

#include "stdafx.h"
#include "Snake.h"

enum TYPEOFCELL {
	NOTHING,	// 0 - ничего
	SNAKE,		// 1 - змея 
	YUMMY		// 2 - вкусняшка
};

class Game
{
	const int   HEIGHT_IN_PX, WIDTH_IN_PX;			// высота/ширина консоли в пикселях. console height/width in pixels.
	const short HEIGHT_IN_CELLS, WIDTH_IN_CELLS;	// высота/ширина консоли в ячейках.  console height/width in cells.
	const int	ROWS, COLS;							// размеры матрицы игрового поля.	 dimension of the matrix of the playing field.

	int** matrix;	// Матрица игрового поля. The matrix of the playing field. 0 - NOTHING (ничего), 1 - SNAKE (змея), 2 - YUMMY (вкусняшка)
	size_t score;	// Рекорд/размер змеи. Record/snake size.
	Snake snake;	// Класс змеюки. Snake class.

	HANDLE h;		// Дескриптор, необходим для работы с цветами и координатами в консоли. The descriptor required to work with colors and coordinates in the console.

public:

	Game()
		: HEIGHT_IN_PX(800), WIDTH_IN_PX(800)
		, HEIGHT_IN_CELLS(HEIGHT_IN_PX / 16 - 4), WIDTH_IN_CELLS(WIDTH_IN_PX / 10 - 4)
		, ROWS(37), COLS(74)
		, matrix(new int* [ROWS]) // rows - 37 cols - 74 
		, score(1)
		, h(GetStdHandle(STD_OUTPUT_HANDLE))
	{
		matrix[0] = new int[ROWS * COLS];
		for (size_t i = 1; i < ROWS; ++i)
			matrix[i] = matrix[i - 1] + COLS;

		for (size_t i = 0; i < ROWS; ++i)
			for (size_t j = 0; j < COLS; ++j)
				matrix[i][j] = TYPEOFCELL::NOTHING;
	}//Game()

	/// <summary>
	/// Инициализация настроек и отрисовка рамки.
	/// Initializing settings & drawing the frame.
	/// </summary>
	void init();

	/// <summary>
	/// Метод, в которой игровой цикл.
	/// The method in which the game loop is.
	/// </summary>
	void loop();

	/// <summary>
	/// Генерация случайного числа в диапазоне [Lo, Hi].
	/// Generating a random number in a range [Lo, Hi].
	/// </summary>
	/// <param name="Lo">Нижняя граница. Lower bound.</param>
	/// <param name="Hi">Верхняя граница. Upper bound.</param>
	/// <returns></returns>
	short random(int Lo, int Hi);

	/// <summary>
	/// Отрисовка матрицы на экран консоли (не используется). Drawing matrix to the console screen (don't use).
	/// </summary>
	void drawMatrix();

	/// <summary>
	/// Точечная отрисовка ячейки по координатам в консоли. 
	/// </summary>
	/// <param name="coord">Координаты отрисовки</param>
	/// <param name="typeofcell">Тип ячейки: голова - светло-зеленая, тело змеи - зеленое, вкусняшка - красное. Cell type: head - light green, snake body - green, yummy - red.</param>
	/// <param name="isSnakeHead">Является ли выводимая ячейка головой змеи? Is the output cell the head of a snake?</param>
	void drawCell(COORD const& coord, TYPEOFCELL typeofcell, bool isSnakeHead = false);
	
	/// <summary>
	/// Вывод рекорда. Drawing record
	/// </summary>
	void drawScore();

	/// <summary>
	/// Заполнить матрицу нулями. Fill the matrix with zeros.
	/// </summary>
	void fillMatrixZeros();
	
	/// <summary>
	///	Отрисовка змеи после совершенного шага. Drawing a snake after a step
	/// </summary>
	void drawSnakeAfterGo();

	~Game();
};

