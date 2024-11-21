#ifndef TETRIMINO_HPP
#define TETRIMINO_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Tetrimino {
    public:
        //Constructor to initialize Tetrimino shape and color
        Tetrimino(int type);

        //Rotate the Tetrimino
        void rotate();

        //Get the current shape of the Tetrimino
        const std::vector<std::vector<int>> &getShape() const;

        //Draw the Tetrimino on the window
        void draw(sf::RenderWindow &window, int offsetX, int offsetY, bool isGhost);

        void drawPreview(sf::RenderWindow &window, int offsetX, int offsetY);

        //Tetrimino's position
        int posX, posY;
        
    private:
        std::vector<std::vector<int>> shape;
        sf::Color color;
};

#endif