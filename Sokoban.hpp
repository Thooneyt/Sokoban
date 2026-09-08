// Copyright 2026 Soon Thao
#pragma once

#include <iostream>

#include "SpriteSheet.hpp"

#include <SFML/Graphics.hpp>

namespace SB {
enum class Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
static const int TILE_SIZE = 64;

Sokoban();
explicit Sokoban(const std::string&);  // Optional

sf::Vector2u size() const { return {width(), height()}; }
unsigned int height() const;
unsigned int width() const;

sf::Vector2u windowSize() const;  // Optional

sf::Vector2u playerLoc() const;

bool isWon() const;  // Part B

void movePlayer(Direction dir);  // Part B
void reset();  // Part B

void undo();  // Optional XC
void redo();  // Optional XC

friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
friend std::istream& operator>>(std::istream& in, Sokoban& s);

std::ostream& printMatrix(std::ostream& out) const;

 protected:
void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
std::vector<std::vector<char>> matrix;
std::vector<std::vector<char>> originalMap;
sf::Vector2u playerPos;
SB::Direction playerDir;
sb::SpriteSheet Sprites;
int goals;
// Any fields you need go here.
};

std::ostream& operator<<(std::ostream& out, const Sokoban& s);
std::istream& operator>>(std::istream& in, Sokoban& s);
}  // namespace SB
