// Copyright 2026 Soon Thao
#include <cstdlib>
#include <fstream>
#include "Sokoban.hpp"
#include "SpriteSheet.hpp"


int main(int argc, char* argv[]) {
    sf::Image SokobanTiles("sokoban_tilesheet.png");
    sb::SpriteSheet Tiles(SokobanTiles, {64, 64});
    SB::Sokoban game;
    std::cout << "attempting opening of " << argv[1] << std::endl;
    std::ifstream Inputfile(argv[1]);
    if (!Inputfile) {
        throw std::runtime_error("Error: Could not open file!");
    }
    Inputfile >> game;
    sf::RenderWindow gameWindow(sf::VideoMode({game.width() * 64, game.height() * 64}),
        "Sokoban Game");
    sf::Font victoryFont("Text.TTF");
    sf::Text victoryText(victoryFont);
    victoryText.setString("Congratulations! You Won!");
    victoryText.setCharacterSize(25);
    victoryText.setFillColor(sf::Color::Black);
    victoryText.setOrigin({static_cast<float>(victoryText.getLocalBounds().size.x / 2),
        static_cast<float>(victoryText.getLocalBounds().size.y / 2)});
    victoryText.setPosition({static_cast<float>(game.width() * 64 / 2),
        static_cast<float>(game.height() * 64 / 2)});
    while (gameWindow.isOpen()) {
        while (const std::optional event = gameWindow.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                gameWindow.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                // If disables movement if you won the game
                if (!game.isWon()) {
                    switch (key->code) {
                        case (sf::Keyboard::Key::W):
                            game.movePlayer(SB::Direction::Up);
                            break;
                        case (sf::Keyboard::Key::A):
                            game.movePlayer(SB::Direction::Left);
                            break;
                        case (sf::Keyboard::Key::S):
                            game.movePlayer(SB::Direction::Down);
                            break;
                        case (sf::Keyboard::Key::D):
                            game.movePlayer(SB::Direction::Right);
                            break;
                        default:
                            break;
                    }
                }
                if (key->code == sf::Keyboard::Key::R) {
                    game.reset();
                    break;
                }
            }
        }
        gameWindow.clear();
        gameWindow.draw(game);
        if (game.isWon()) {
            gameWindow.draw(victoryText);
        }
        gameWindow.display();
    }
    return 0;
}
