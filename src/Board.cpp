#include "Board.hpp"    
#include <iostream>

//Constructor to initialize an empty board
Board::Board() {
    grid = std::vector<std::vector<int>>(HEIGHT, std::vector<int>(WIDTH, 0));
}



//Draw the board on the SFML window
void Board::draw(sf::RenderWindow& window) {
    sf::RectangleShape block(sf::Vector2f(30, 30));

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] != 0) {
                //Draw only filled cells
                block.setFillColor(sf::Color::White);
                block.setPosition(x * 30, y * 30);
                window.draw(block);
            }
        }
    }
}

//Check for collisions with board edges or locked cells
bool Board::checkCollision(const Tetrimino &piece) const {
    const auto &shape = piece.getShape();
    for (int i = 0; i < shape.size(); i++){
        for (int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j] == 1) {
                int newX = piece.posX + j;
                int newY = piece.posY + i;

                //Check if out of bounds
                if (newX < 0 || newX >= WIDTH || newY >= HEIGHT) {
                    return true;
                } 

                //Checkl if collides with existing blocks
                if (newY >= 0 && grid[newY][newX] != 0) {
                    return true;
                } 
            }
        }
    }

    return false;
}

//Lock the Tetrimino onto the board
void Board::lockPiece(const Tetrimino &piece) {
    const auto &shape = piece.getShape();

    for (int i = 0; i < shape.size(); i++) {
        for (int j = 0; j < shape[i].size(); j++) {
            if (shape[i][j] == 1) {
                int newX = piece.posX + j;
                int newY = piece.posY + i;

                if (newY >= 0 && newX >= 0 && newX < WIDTH && newY < HEIGHT) {
                    grid[newY][newX] = 1;
                }
            }
        }
    }
}

//Clear completed lines and return the number of lines cleared
int Board::clearLines() {
    int linesCleared = 0;
    for (int y = 0; y < HEIGHT; y++) {
        if (isRowFull(y)) {
            clearRow(y);
            linesCleared++;
        }
    }

    return linesCleared;
}

//Check if a new piece can be places (game over condition)
bool Board::isGameOver(const Tetrimino& piece) const {
    return checkCollision(piece);
}

//Check if a row is full
bool Board::isRowFull(int row) const {
    for (int x = 0; x < WIDTH; x++) {
        if (grid[row][x] == 0) {
            return false;
        }
    }

    return true;
}

//Clear a row and move everything above it down
void Board::clearRow(int row) {
    for (int y = row; y > 0; y--) {
        for (int x = 0; x < WIDTH; x++) {
            grid[y][x] = grid[y - 1][x];
        }
    }

    //Clear the top row
    for (int x = 0; x < WIDTH; x++) {
        grid[0][x] = 0;
    }
}

//New function to clear the entire board
void Board::clearBoard() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = 0; //Set all cells to empty
        }
    }
}