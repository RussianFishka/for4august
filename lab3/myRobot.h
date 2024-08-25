//
// Created by Марат on 23.08.2024.
//

#ifndef LAB3TA_MYROBOT_H
#define LAB3TA_MYROBOT_H
#include "cellandother.h"
#include <vector>
#include <iostream>
#include <fstream>
struct Position {
    int x, y;
};
std::vector<std::vector<CELL>> loadMaze(const std::string& filename, Position& startPos);
class Robot {
    private:
        int maxDrones = 10;
        int curDrones = 10;
        Position pos;
        bool isOperational = true;
        std::vector<std::vector<CELL>> maze;
        std::vector<std::vector<CELL>> explored;
    public:
        Robot(Position startPos, const std::vector<std::vector<CELL>>& maze)
                : pos(startPos), maze(maze), explored(maze.size(), std::vector<CELL>(maze[0].size(), UNDEF)) {
            if (maze[pos.x][pos.y] != WALL) {
                explored[pos.x][pos.y] = maze[pos.x][pos.y];
            } else {
                std::cerr << "Ошибка: начальная позиция робота находится на стене." << std::endl;
                isOperational = false;
            }
            std::cout << "You are here" << std::endl;
            printExplored();
        }
        int getcurDrones(){
            return curDrones;
        }
        bool moveUp() {
            if (!isOperational){
                return false;
            }
            if (pos.x > 0 && maze[pos.x - 1][pos.y] != WALL && maze[pos.x - 1][pos.y] != EXIT) {
                pos.x--;
                updateMaze();
                printExplored();
                return true;
            }
            stopIfWallOrExit(pos.x - 1, pos.y);
            return false;
        }

        bool moveDown() {
            if (!isOperational){
                return false;
            }
            if (pos.x < maze.size() - 1 && maze[pos.x + 1][pos.y] != WALL && maze[pos.x + 1][pos.y] != EXIT) {
                pos.x++;
                updateMaze();
                printExplored();
                return true;
            }
            stopIfWallOrExit(pos.x + 1, pos.y);
            return false;
        }

        bool moveLeft() {
            if (!isOperational){
                return false;
            }
            if (pos.y > 0 && maze[pos.x][pos.y - 1] != WALL && maze[pos.x ][pos.y - 1] != EXIT) {
                pos.y--;
                updateMaze();
                printExplored();
                return true;
            }
            stopIfWallOrExit(pos.x, pos.y - 1);
            return false;
        }

    bool moveRight() {
        if (!isOperational){
            return false;
        }
        if (pos.y < maze[0].size() - 1 && maze[pos.x][pos.y + 1] != WALL && maze[pos.x][pos.y + 1] != EXIT) {
            pos.y++;
            updateMaze();
            printExplored();
            return true;
        }
        stopIfWallOrExit(pos.x, pos.y + 1);
        return false;
    }

    void updateMaze() {
        explored[pos.x][pos.y] = maze[pos.x][pos.y];
    }
private:
    void stopIfWallOrExit(int x, int y) {
        if (maze[x][y] == WALL) {
            isOperational = false;
            std::cout << "Робот столкнулся со стеной и больше не может двигаться." << std::endl;
            std::cout << "Лабиринт выглядел так " << std::endl;
            printMaze();
        } else if (maze[x][y] == EXIT) {
            isOperational = false;
            std::cout << "Поздравляем! Робот нашел выход и завершил свою работу." << std::endl;
            std::cout << "Лабиринт выглядел так " << std::endl;
            printMaze();
        }
    }
public:
    bool sendDrones(int sizeDrones) {
        if(sizeDrones > curDrones){
            std::cout << "У нас нет столько разведчиков" << std::endl;
            return false;
        }
        std::vector<std::vector<CELL>> droneExploration = explored;
        for (int i = 0; i < sizeDrones; ++i) {
            Position dronePos = pos;
            for (int j = 0; j < 5; ++j) {
                int direction = rand() % 4;
                switch (direction) {
                    case 0: // UP
                        if (dronePos.x > 0 && maze[dronePos.x - 1][dronePos.y] != WALL) {
                            dronePos.x--;
                        } else {
                            if(dronePos.x > 0) {
                                dronePos.x--;
                            }
                            j = 5; // Остановить движение разведчика
                        }
                        break;
                    case 1: // DOWN
                        if (dronePos.x < maze.size() - 1 && maze[dronePos.x + 1][dronePos.y] != WALL) {
                            dronePos.x++;
                        } else {
                            if(dronePos.x < maze.size() - 1) {
                                dronePos.x++;
                            }
                            j = 5; // Остановить движение разведчика
                        }
                        break;
                    case 2: // LEFT
                        if (dronePos.y > 0 && maze[dronePos.x][dronePos.y - 1] != WALL) {
                            dronePos.y--;
                        } else {
                            if(dronePos.y > 0) {
                                dronePos.y--;
                            }
                            j = 5; // Остановить движение разведчика
                        }
                        break;
                    case 3: // RIGHT
                        if (dronePos.y < maze[0].size() - 1 && maze[dronePos.x][dronePos.y + 1] != WALL) {
                            dronePos.y++;
                        } else {
                            if(dronePos.y < maze[0].size() - 1) {
                                dronePos.y++;
                            }
                            j = 5; // Остановить движение разведчика
                        }
                        break;
                }
                droneExploration[dronePos.x][dronePos.y] = maze[dronePos.x][dronePos.y];
            }
        }
        std::cout << "Разведка" << std::endl;
        printDroneExploration(droneExploration);
        std::cout << "Разведка" << std::endl;
        curDrones -= sizeDrones;
        return true;
    }
private:
    void printDroneExploration(const std::vector<std::vector<CELL>>& droneExploration) const {
        for (int i = 0; i < droneExploration.size(); ++i) {
            for (int j = 0; j < droneExploration[i].size(); ++j) {
                switch (droneExploration[i][j]) {
                    case EMPTY: std::cout << " "; break;
                    case WALL: std::cout << "#"; break;
                    case EXIT: std::cout << "E"; break;
                    case UNDEF: std::cout << "?"; break;
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
private:
    void printMaze() const {
        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                if (i == pos.x && j == pos.y) {
                    std::cout << "R";
                } else {
                    switch (maze[i][j]) {
                        case EMPTY: std::cout << " "; break;
                        case WALL: std::cout << "#"; break;
                        case EXIT: std::cout << "E"; break;
                        case UNDEF: std::cout << "?"; break;
                    }
                }
            }
            std::cout << std::endl;
        }
    }
    void printExplored() const {
        for (int i = 0; i < explored.size(); ++i) {
            for (int j = 0; j < explored[i].size(); ++j) {
                if (i == pos.x && j == pos.y) {
                    std::cout << "R";
                } else {
                    switch (explored[i][j]) {
                        case EMPTY: std::cout << " "; break;
                        case WALL: std::cout << "#"; break;
                        case EXIT: std::cout << "E"; break;
                        case UNDEF: std::cout << "?"; break;
                    }
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};



#endif //LAB3TA_MYROBOT_H
