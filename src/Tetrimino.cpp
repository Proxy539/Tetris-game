#include "Tetrimino.hpp"    
#include <iostream>

//Define the Tetrimino shapes (I, O, T, S, Z, J, L)
std::vector<std::vector<std::vector<int>>> tetriminoShapes = {
    //I shape
    {
        {1, 1, 1, 1}
    },
    //O shape
    {
        {1, 1},
        {1, 1}
    },
    //T shape
    {
        {0, 1, 0},
        {1, 1, 1}
    },
    //S shape
    {
        {0, 1, 1},
        {1, 1, 0}
    },
    //Z shape
    {
        {1, 1, 0},
        {0, 1, 1}
    },
    //J shape
    {
        {1, 0, 0},
        {1, 1, 1}
    },
    //L shape
    {
        {0, 0, 1},
        {1, 1, 1}
    }
};

//Tetrimino colors 
std::vector<sf::Color> tetriminoColors = {
    sf::Color::Cyan,
    sf::Color::Yellow,
    sf::Color::Magenta,
    sf::Color::Green,
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color::White
};

Tetrimino::Tetrimino(int type): posX(3), posY(0) {
    shape = tetriminoShapes[type];
    color = tetriminoColors[type];
}

void Tetrimino::rotate() {
    std::vector<std::vector<int>> rotated(shape[0].size(), std::vector<int>(shape.size()));
    for (size_t i = 0; i < shape.size(); i++) {
        for (size_t j = 0; j < shape[i].size(); j++) {
            rotated[j][shape.size() - 1 - i] = shape[i][j];
        }
    }
    shape = rotated;
}

const std::vector<std::vector<int>> & Tetrimino::getShape() const {
    return shape;
}

void Tetrimino::draw(sf::RenderWindow &window, int offsetX, int offsetY, bool isGhost = false) {
    sf::RectangleShape block(sf::Vector2f(30, 30));
    block.setFillColor(color);

    for (size_t i = 0; i < shape.size(); i++) {
        for (size_t j = 0; j < shape[i].size(); j++) {
            if (shape[i][j] == 1) {
                block.setPosition((posX + j + offsetX) * 30, (posY + i + offsetY) * 30);

                if (isGhost) {
                    block.setFillColor(sf::Color(255, 255, 255, 100)); //Semi-transparent
                } else {
                    block.setFillColor(color);
                }

                window.draw(block);
            }
        }
    }
}

void Tetrimino::drawPreview(sf::RenderWindow &window, int offsetX, int offsetY) {
    sf::RectangleShape block(sf::Vector2f(50, 50)); //Smaller block size for preview
    block.setFillColor(color);

    for (size_t i = 0; i < shape.size(); i++) {
        for (size_t j = 0; j < shape[i].size(); j++) {
            if (shape[i][j] == 1) {
                block.setPosition((offsetX + j) * 50, (offsetY + i)* 50);
                window.draw(block);
            }
        }
    }
}