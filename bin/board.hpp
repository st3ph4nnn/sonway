#pragma once

#include "../lib/raylib.h"

#include "utility.hpp"
#include "cells.hpp"

int length = 96;
int lines = 54;

namespace board {
    int density = 6;
    
    void clear() {
        cells.clear();

        for (int i = 0; i < length; i++) 
            cells.emplace_back(std::vector<Cell>(lines, Cell()));

        for (int i = 0; i < length; i++) {
            for (int j = 0; j < lines; j++) {
                cells[i][j].x = j;
                cells[i][j].y = i;

                if (i == 0 || i == length-1 || j == 0 || j == lines-1) {
                    cells[i][j].state = CellStates::BORDER;
                    continue;
                }

                if (utility::random(1, 4 * density) == 1)
                    cells[i][j].state = CellStates::ALIVE;
            }
        }
    }

    void draw() {
        for (int i = 0; i < length; i++)
            for (int j = 0; j < lines; j++) {
                if (cells[i][j].state == CellStates::BORDER) {
                    DrawRectangle(4 + 20 * i, 4 + 20 * j, 11, 11, RED);
                    continue;
                }

                if (cells[i][j].state == CellStates::DEAD)
                    continue;

                DrawRectangle(20 * i, 20 * j, 19, 19, BLACK);
            }
    }

    void setStates() {
        for (int i = 0; i < length; i++) 
            for (int j = 0; j < lines; j++)
                if (cells[i][j].state != CellStates::BORDER)
                    cells[i][j].state = cells[i][j].nextState;
    }

    void generate() {
        for (int i = 0; i < length; i++)
            for (int j = 0; j < lines; j++) {
                cells[i][j].calculateState();
            }
        
        setStates();
    }
}