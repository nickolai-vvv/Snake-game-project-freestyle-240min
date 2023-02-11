#include "stdafx.h"

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

struct SnakeNode {
    COORD coord;
    COORD prev_coord;
    SnakeNode* next;

    SnakeNode() : coord({ 0,0 }), prev_coord({ 0,0 }), next(nullptr) {}
    SnakeNode(COORD coord): coord(coord), prev_coord(coord), next(nullptr){}
};

struct Snake {
    SnakeNode* head;
    SnakeNode* tail;
    direction dir;

    Snake() : head(nullptr), tail(nullptr), dir(direction::NONE) {}

    /// <summary>
    /// Содержит ли змеюка элементы?
    /// Does the snake contain elements?
    /// </summary>
    /// <returns>true or false</returns>
    bool isEmpty();

    /// <summary>
    /// Создаёт первый элемент - голову с координатами. 
    /// Creates the first element - a head with coordinates
    /// </summary>
    /// <param name="coord">Координаты в матрице (игровом поле). 
    /// Coordinates in the matrix (playing field)</param>
    void pushHead(COORD coord);

    /// <summary>
    /// Увеличивает хвост на один элемент, по сути реализация односвязного списка. 
    /// Increases the tail by one element, in fact, the implementation of a singly linked list.
    /// </summary>
    void pushTail();

    /// <summary>
    /// Метод, который совершает движение змеюки в соответствии с выбранным направлением.
    /// A method that makes the snake move in accordance with the chosen direction.
    /// </summary>
    void go();

    ~Snake();
};