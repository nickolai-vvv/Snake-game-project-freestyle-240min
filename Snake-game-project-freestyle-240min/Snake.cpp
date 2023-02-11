#include "Snake.h"

bool Snake::isEmpty() { return head == nullptr; }

void Snake::pushHead(COORD coord) {
    SnakeNode* p = new SnakeNode(coord);
    p->prev_coord = p->coord;
    
    // Голова и хвост указывают на один и тот же элемент
    // The head and tail point to the same element
    head = p;
    tail = p;
}//pushHead

void Snake::pushTail() {
    // Хвост появляется на месте предыдущих координат хвоста
    // The tail appears in place of the previous tail coordinates
    SnakeNode* p = new SnakeNode({ tail->prev_coord.X, tail->prev_coord.Y });
    
    // Хвост - теперь новый элемент
    // The tail is now a new element
    tail->next = p;
    tail = p;
}//pushTail

void Snake::go() {
    // Если ничего нет, то и ходить незачем.
    // If there is nothing, then there is no need to take a step.
    if (isEmpty()) return;
    
    // Временная переменная для прохода по всей змеюке
    // A temp var for passing through the entire snake
    SnakeNode* p = head;
    p->prev_coord = p->coord;

    // Изменяем координаты головы в соответствии с направлением
    // Change the coordinates of the head in accordance with the direction
    switch (dir) {
    case direction::UP:
        p->coord.X--;
        break;
    case direction::DOWN:
        p->coord.X++;
        break;
    case direction::LEFT:
        p->coord.Y--;
        break;
    case direction::RIGHT:
        p->coord.Y++;
        break;
    }//switch

    // Если змеюка выходит за рамки, то телепортируем её
    // If the snake goes out of bounds, then we teleport it
    if (p->coord.X < 0) p->coord.X = 37 - 1;
    if (p->coord.X > 37 - 1) p->coord.X = 0;
    if (p->coord.Y > 74 - 1) p->coord.Y = 0;
    if (p->coord.Y < 0) p->coord.Y = 74 - 1;

    // (1) предыдущие координаты следующего элемента сдвигаются (теперь равны текущим координатам)
    // (1) the previous coordinates of the next element are shifted (now equal to the current coordinates of these element)
    // 
    // (2) Координаты следующиго элемента - предыдущие координаты текущего элемента
    // (2) The coordinates of the next element are the previous coordinates of the current element
    // 
    // Если тяжело, то советую нарисовать список
    // If it's hard, then I advise you to draw a list
    /*
    * c - текущие координаты    - current coords
    * p - предыдущие координаты - previous coords
    *     
    * Будем считать, что голова уже совершила шаг.
    * Let's assume that the head has already made a step.
    * 
    *    ||
    *    ||
    *    \/
    * ---------      ---------      ---------
    * | head  |      | tail1 |      | tail2 |
    * ---------  ->  ---------  ->  ---------
    * | c 4 0 |      | c 2 0 |      | c 1 0 |
    * | p 3 0 |      | p 1 0 |      | p 0 0 |
    * ---------      ---------      ---------
    * 
    * p-next = tail1
    * 
    * Сперва "подтягиваем" предыдущие координаты к текущим. В противном случае потеряем их. 
    * Не забываем также, что, на мой взгляд, операции ++ и -- некорректны, т.к. направлений 4.
    * First, we "pull up" the previous coordinates to the current ones. Otherwise we will lose them.
    * Also do not forget that, in my opinion, the operations ++ and -- are incorrect, because there are 4 directions.
    * 
    * tail1->prev_coord = 2 0 = tail1.coord
    *
    *    ||
    *    ||
    *    \/
    * ---------      ---------      ---------
    * | head  |      | tail1 |      | tail2 |
    * ---------  ->  ---------  ->  ---------
    * | c 4 0 |      | c 2 0 |      | c 1 0 |
    * | p 3 0 |      | p 2 0 |      | p 0 0 |
    * ---------      ---------      ---------
    *
    * Теперь же подтягиваем текущие координаты tail1.
    * Now pull up the current coordinates of tail1.
    * 
    * tail1->coord = 3 0 = head->prev_coord
    * 
    *    ||
    *    ||
    *    \/
    * ---------      ---------      ---------
    * | head  |      | tail1 |      | tail2 |
    * ---------  ->  ---------  ->  ---------
    * | c 4 0 |      | c 3 0 |      | c 1 0 |
    * | p 3 0 |      | p 2 0 |      | p 0 0 |
    * ---------      ---------      ---------
    * 
    * Далее сдвигаемся на элемент по списку
    * Next, move to the item1 in the list
    * 
    *                   ||
    *                   ||
    *                   \/
    * ---------      ---------      ---------
    * | head  |      | tail1 |      | tail2 |
    * ---------  ->  ---------  ->  ---------
    * | c 4 0 |      | c 3 0 |      | c 1 0 |
    * | p 3 0 |      | p 2 0 |      | p 0 0 |
    * ---------      ---------      ---------
    */
  
    while (p->next) {
        p->next->prev_coord = p->next->coord; //(1)
        p->next->coord = p->prev_coord; // (2)
        p = p->next;
    }//while
}//go

Snake::~Snake() {
    // Временная переменная для ходьбы по списку
    // Temp var for walking through the list
    SnakeNode* p = new SnakeNode();
    while (!head) {
        p = head;
        head = head->next;
        delete p;
    }//while 
}//~Snake()