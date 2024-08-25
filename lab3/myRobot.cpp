//
// Created by Марат on 23.08.2024.
//
#include "myRobot.h"
std::vector<std::vector<CELL>> loadMaze(const std::string& filename, Position& startPos) {
    std::ifstream file(filename);
    //if (!file) {
    //    std::cerr << "Не удалось открыть файл." << std::endl;
    //    exit(1);
    //}

    int rows, cols;
    file >> rows >> cols;
    file >> startPos.x >> startPos.y;

    std::vector<std::vector<CELL>> maze(rows, std::vector<CELL>(cols, EMPTY));
    std::string line;
    std::getline(file, line); // Пропустить оставшуюся часть строки с позициями. Пробелы и прочее
    bool exitFound = false;
    for (int i = 0; i < rows; ++i) {
        std::getline(file, line);
        for (int j = 0; j < cols; ++j) {
            switch (line[j]) {
                case '#': maze[i][j] = WALL; break;
                case ' ': maze[i][j] = EMPTY; break;
                case 'E': maze[i][j] = EXIT; exitFound = true; break;
            }
        }
    }
    if (!exitFound) {
        std::cerr << "Ошибка: в лабиринте нет выхода." << std::endl;
        exit(1);
    }
    return maze;
}