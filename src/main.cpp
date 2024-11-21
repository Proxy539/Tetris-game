#include <SFML/Graphics.hpp>
#include "Tetrimino.hpp"    
#include "Board.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris game");
    window.setFramerateLimit(60);

    srand(time(0));//Random seed

    Board board;
    Tetrimino piece(rand() % 7);//Random Tetrimino piece
    Tetrimino nextPiece(rand() % 7);
    Tetrimino holdPiece(rand() % 7); //Held Tetrimino piece
    Tetrimino ghostPiece = piece; //Start with the same shape as the current piece
    bool hasHeld = false; //Can hold only once per drop
    int dropSpeed = 500;//Default drop speed (milliseconds)
    sf::Clock clock; //Timer for automatice piece dropping


    int score = 0;//Initialize score
    int level = 1;
    int linesCleared = 0;
    bool isPaused = false; //Tracks pause state

    //Load font for displaying the score
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        return -1; //Exit if font not found
    }

    sf::Text scoreText, levelText, gameOverText, restartText, holdText, pauseText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(650, 50);

    levelText.setFont(font);
    levelText.setCharacterSize(20);
    levelText.setFillColor(sf::Color::White);
    levelText.setPosition(650, 100);

    holdText.setFont(font);
    holdText.setCharacterSize(20);
    holdText.setFillColor(sf::Color::White);
    holdText.setString("Hold");
    holdText.setPosition(50, 50);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(200, 200);

    restartText.setFont(font);
    restartText.setCharacterSize(20);
    restartText.setFillColor(sf::Color::White);
    restartText.setString("Press R to Restart or Q to Quit");
    restartText.setPosition(180, 300);

    pauseText.setFont(font);
    pauseText.setCharacterSize(50);
    pauseText.setFillColor(sf::Color::Yellow);
    pauseText.setString("PAUSED");
    pauseText.setPosition(300, 250);

    bool isGameOver = false;

    //Main game loop
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            ghostPiece = piece;//Copt the current piece
            while (!board.checkCollision(ghostPiece)) {
                ghostPiece.posY++; //Move ghost down until collision
            }
            ghostPiece.posY--; //Adjust to the last valid position

            if (event.type == sf::Event::Closed) {
                    window.close();
            }    

            //Handle keyboard inputs for controls
            if (!isGameOver) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Left) {
                        piece.posX--;
                        if (board.checkCollision(piece)) {
                            piece.posX++;//Undo move if collision
                        }
                    } else if (event.key.code == sf::Keyboard::Right) {
                        piece.posX++;
                        if (board.checkCollision(piece)) {
                            piece.posX--;//Undo move if collision
                        }
                    } else if (event.key.code == sf::Keyboard::Down) {
                        piece.posY++;

                        if (board.checkCollision(piece)) {
                            piece.posY--;
                            board.lockPiece(piece);
                            int lines = board.clearLines();
                            linesCleared += lines;

                            //Add score based on the number of lines cleared
                            switch(lines) {
                                case 1: score += 100; break;
                                case 2: score += 300; break;
                                case 3: score += 500; break;
                                case 4: score += 800; break;
                            }

                            if (linesCleared >= 10) {
                                level++;
                                linesCleared -= 10;
                                dropSpeed = std::max(100, dropSpeed - 50);
                            }

                            piece = nextPiece;
                            nextPiece = Tetrimino(rand() % 7);
                            hasHeld = false; //Allow hold again

                            if (board.isGameOver(piece)) {
                                isGameOver = true;
                            }
                        }
                    } else if (event.key.code == sf::Keyboard::Up) {
                        piece.rotate();
                        if (board.checkCollision(piece)) {
                            piece.rotate();
                        }
                    } else if (event.key.code == sf::Keyboard::C) {
                        //Hold piece logic 
                        if (!hasHeld) {
                            if (holdPiece.getShape().empty()) {
                                holdPiece = piece;
                                piece = nextPiece;
                                nextPiece = Tetrimino(rand() % 7);
                            } else {
                                std::swap(holdPiece, piece);
                            }
                            piece.posX = 3; //Reset position
                            piece.posY = 0;
                            hasHeld = true;
                        }
                    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
                        isPaused = !isPaused; //Toggle pause state
                    } else if (event.key.code == sf::Keyboard::Space) {
                        while (!board.checkCollision(piece)) {
                            piece.posY++;
                        }

                        piece.posY--;
                        board.lockPiece(piece);
                        int lines = board.clearLines();
                        linesCleared += lines;

                        switch(lines) {
                            case 1: score += 100; break;
                            case 2: score += 300; break;
                            case 3: score += 500; break;
                            case 4: score += 800; break;
                        }

                        if (linesCleared >= 10) {
                            level++;
                            linesCleared -= 10;
                            dropSpeed = std::max(100, dropSpeed - 50);
                        }

                        piece = nextPiece;
                        nextPiece = Tetrimino(rand() % 7);
                        hasHeld = false; //Allow hold again
                        if (board.isGameOver(piece)) {
                            isGameOver = true;
                        }
                    }
                }
            } else {
                //Game over state
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::R) {
                        //Reset game
                        score = 0;
                        level = 1;
                        linesCleared = 0;
                        dropSpeed = 500;
                        isGameOver = false;
                        board.clearBoard();
                        piece = Tetrimino(rand() % 7);
                        nextPiece = Tetrimino(rand() % 7);
                        holdPiece = Tetrimino(rand() % 7); //Reset hold
                        hasHeld = false;
                    } else if (event.key.code == sf::Keyboard::Q) {
                        window.close();
                    }
                }
            }
        }
        if (!isGameOver && clock.getElapsedTime().asMilliseconds() > dropSpeed) {
            piece.posY++;

            if (board.checkCollision(piece)) {
                piece.posY--;
                board.lockPiece(piece);
                int lines = board.clearLines();
                linesCleared += lines;

                switch(lines) {
                    case 1: score += 100; break;
                    case 2: score += 300; break;
                    case 3: score += 500; break;
                    case 4: score += 800; break;
                }

                if (linesCleared >= 10) {
                    level++;
                    linesCleared -= 10;
                    dropSpeed = std::max(100, dropSpeed - 50);
                }

                piece = nextPiece;
                nextPiece = Tetrimino(rand() % 7);
                hasHeld = false; //Allow hold again
                if (board.isGameOver(piece)) {
                    isGameOver = true;
                }
            }

            clock.restart();
        }

        //Update score and level display
        scoreText.setString("Score: " + std::to_string(score));
        levelText.setString("Level: " + std::to_string(level));

        if (!isPaused && !isGameOver) {
            window.clear(sf::Color::Black);
            board.draw(window);
            piece.draw(window, 0, 0, false);
            ghostPiece.draw(window, 0, 0, true);//Pass a flag to indicate it's a ghost piece
            nextPiece.drawPreview(window, 10, 5);//Draw the next piece in preview
            holdPiece.drawPreview(window, 10, 10); //Draw hold piece
            window.draw(scoreText);
            window.draw(levelText);
        }

        if (isGameOver) {
            window.draw(gameOverText);
            window.draw(restartText);
        }

        if (isPaused) {
            window.draw(pauseText);
        }

        window.display();
    }

    return 0;
}