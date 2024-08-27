#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "myRobot.h"
// Весь код, который ты уже предоставил, включая определения CELL, Position, Robot и функции loadMaze

enum Direction { UP, RIGHT, DOWN, LEFT };

// Функция для поворота направо
Direction turnRight(Direction dir) {
    return static_cast<Direction>((dir + 1) % 4);
}

// Функция для поворота налево
Direction turnLeft(Direction dir) {
    return static_cast<Direction>((dir + 3) % 4);
}

// Функция для движения в текущем направлении
bool moveInDirection(Robot& robot, Direction dir) {
    switch (dir) {
        case UP: return robot.moveUp();
        case RIGHT: return robot.moveRight();
        case DOWN: return robot.moveDown();
        case LEFT: return robot.moveLeft();
    }
    return false;
}

int main() {
    std::srand(std::time(nullptr)); // Инициализация генератора случайных чисел

    std::string filename = "maze.txt";
    Position startPos;
    std::vector<std::vector<CELL>> maze = loadMaze(filename, startPos);

    Robot robot(startPos, maze);

    // Переменная для хранения разведанных данных
    std::vector<std::vector<CELL>> discovered(maze.size(), std::vector<CELL>(maze[0].size(), UNDEF));

    Direction currentDirection = RIGHT;
    // заданы размеры лабиринта
    int x = 1;// задается в программе начальное положение задает строку
    int y = 2; // задает столбец
    // когда двигаюсь в произвольном направлении обновляю эти координаты.
    // Основной цикл движения робота
    while (1) {
        // Отправляем дронов для исследования, если есть не исследованные клетки вокруг текущей позиции
        // getcurdrones
        bool sendDrone = false;
        /*if (robot.getcurDrones() > 0) { позже добавишь
            if ((x > 0 && discovered[x - 1][y] == UNDEF) ||
                (x < discovered.size() - 1 && discovered[x + 1][y] == UNDEF) ||
                (y > 0 && discovered[x][y - 1] == UNDEF) ||
                (y < discovered[0].size() - 1 && discovered[x][y + 1] == UNDEF)) {
                sendDrone = true;
            }
        }*/

        // Отправляем дронов, если есть не исследованные клетки
        if (sendDrone) { // заменяем на пока есть дроны
            std::vector<CELL> explored = robot.sendDrones(5);

         /*   // Обновляем переменную discovered
            int index = 0;
            for (int i = 0; i < discovered.size(); ++i) {
                for (int j = 0; j < discovered[i].size(); ++j) {
                    if (discovered[i][j] == UNDEF && explored[index] != UNDEF) {
                        discovered[i][j] = explored[index];
                    }
                    index++;
                }
            }*/// просто assign
        }
        bool find exit;
        void dfs(std::vector<std::vector<CELL>>& discovered, Position pos, Direction dir) {
            if (foundExit) return;
            // до вызова обновляем
            int x = pos.x;
            int y = pos.y;


            // Проверяем, является ли текущая клетка стеной или уже посещенной
            if (discovered[x][y] == WALL || discovered[x][y] == VISITED) { // посещенную клетку делаем стеной
                return;
            }

            // Проверяем, является ли текущая клетка выходом
            if (discovered[x][y] == EXIT) {
                foundExit = true;
                return;
            }

            // Помечаем текущую клетку как посещенную
            discovered[x][y] = VISITED;

            // Рекурсивно исследуем соседние клетки
            Position directions[] = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
            int moves[] = {3, 4, 1, 2}; // Соответствующие движения: вперед, назад, налево, направо

            for (int i = 0; i < 4; ++i) {
                Direction newDir = static_cast<Direction>((dir + i) % 4);
                if (moveInDirection(robot, newDir)) {
                    path.push_back(moves[i]);
                    dfs(robot, discovered, directions[i], newDir);
                    if (foundExit) return;
                    path.pop_back();
                }
            }
        }








        // Проверяем, найден ли выход
        bool exitFound = false;
        for (const auto& row : discovered) {
            for (const auto& cell : row) {
                if (cell == EXIT) {
                    std::cout << "Выход найден!" << std::endl;
                    exitFound = true;
                    break;
                }
            }
            if (exitFound) break;
        }
        if (exitFound) break;
         // правило правой руки
        // Двигаем робота в текущем направлении
        if (!moveInDirection(robot, currentDirection)) {
            // Если движение невозможно, поворачиваем налево
            currentDirection = turnLeft(currentDirection);
        } else {
            // Если движение возможно, поворачиваем направо
            currentDirection = turnRight(currentDirection);
        }
    }

    if (!robot.isOperational()) {
        std::cout << "Робот не смог найти выход." << std::endl;
    }

    return 0;
}