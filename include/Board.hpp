#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tetrimino.hpp"

class Board {
    public: 
        static const int WIDTH = 10;
        static const int HEIGHT = 20;

        Board();

        //Draw the board on the window
        void draw(sf::RenderWindow& window);

        //Check for collisions with the board edges or locked cells
        bool checkCollision(const Tetrimino& piece) const;

        //Lock the Tetrimino onto the board
        void lockPiece(const Tetrimino& piece);

        //Clear completed lines and return the numbr of lines cleared
        int clearLines();

        //Check if a new piece can be placed (game over condition)
        bool isGameOver(const Tetrimino& piece) const;
        
        //New function to clear the board
        void clearBoard();
    
    private:
        std::vector<std::vector<int>> grid; //2D grid representing the board
        //Helper function to check if a row is full
        bool isRowFull(int row) const;
        //Helper function to clear a row
        void clearRow(int row);
};

#endif