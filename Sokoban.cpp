// Copyright 2026 Soon Thao
#include <iostream>
#include <string>
#include <algorithm>

#include "Sokoban.hpp"

#include <SFML/Graphics.hpp>

namespace SB {
Sokoban::Sokoban() : matrix(), originalMap(), playerPos({0, 0}), playerDir(SB::Direction::Down),
Sprites(sf::Image("sokoban_tilesheet.png"), {TILE_SIZE, TILE_SIZE}), goals(0) {}

unsigned int Sokoban::height() const {
    if (matrix.empty()) {
        throw std::out_of_range("Error: Matrix is empty!");
    }
    return matrix.size();
}

unsigned int Sokoban::width() const {
    if (matrix.empty()) {
        throw std::out_of_range("Error: Matrix is empty!");
    }
    return matrix.at(0).size();
}

sf::Vector2u Sokoban::playerLoc() const {
    return playerPos;
}

bool Sokoban::isWon() const {
int wonCount = 0;
for (unsigned int i = 0; i < matrix.size(); i++) {
    auto findFilledAreas = find(matrix[i].begin(), matrix[i].end(), '1');
    if (findFilledAreas != matrix[i].end()) {
        wonCount++;
    }
}
return goals == wonCount;
}

void Sokoban::movePlayer(Direction dir) {
int OffsetX = 0;
int OffsetY = 0;
// Switch used to get offset depending on direction
switch (dir) {
case (Direction::Up):
playerDir = Direction::Up;
OffsetY = -1;
break;
case (Direction::Down):
playerDir = Direction::Down;
OffsetY = 1;
break;
case (Direction::Left):
playerDir = Direction::Left;
OffsetX = -1;
break;
case (Direction::Right):
playerDir = Direction::Right;
OffsetX = 1;
break;
}
// newPosX and newPosY used to check the spot player is moving to.
int newPosX = playerPos.x + OffsetX;
int newPosY = playerPos.y + OffsetY;
// PushX and PushY are used to test correct coordinates for box push or otherwise
int pushX = playerPos.x + (OffsetX * 2);
int pushY = playerPos.y + (OffsetY * 2);
if (newPosX < 0 || newPosX >= static_cast<int>(width()) ||
newPosY < 0 || newPosY >= static_cast<int>(height())) {
return;
}
char newPos = matrix[newPosY][newPosX];  // Player Coords moving to
if (newPos == 'A' || newPos == '1') {
    if (pushX < 0 || pushX >= static_cast<int>(width())
    || pushY < 0 || pushY >= static_cast<int>(height())) {
     return;
}
char newBoxPos = matrix[pushY][pushX];  // Coords of where object is moving
if (newBoxPos != 'A' && newBoxPos != '#' && newBoxPos != '1') {
    matrix[pushY][pushX] = (matrix[pushY][pushX] == 'a') ? '1' : 'A';
    matrix[newPosY][newPosX] = (matrix[newPosY][newPosX] == 'a' ||
        matrix[newPosY][newPosX] == '1') ? 'a' : '.';
} else {
    return;
}
}
// Change Player Position only if newPos is not a wall
if (matrix[newPosY][newPosX] != '#') {
    matrix[playerPos.y][playerPos.x] = (originalMap[playerPos.y][playerPos.x] == 'a'
        || originalMap[playerPos.y][playerPos.x] == '1') ? 'a' : '.';
    playerPos = {static_cast<uint>(newPosX), static_cast<uint>(newPosY)};
    matrix[newPosY][newPosX] = '@';
}
}

void Sokoban::reset() {
    // reset involves just setting matrix to the original map
    // and then reset the playerPos based off where it was before through loop.
    matrix = originalMap;
    for (uint i = 0; i < matrix.size(); i++) {
        for (uint j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == '@') {
                playerPos = {j, i};
            }
        }
    }
}

std::ostream& SB::Sokoban::printMatrix(std::ostream& out) const {
    out << std::endl;
    for (uint64_t i = 0; i < matrix.size(); i++) {
        for (uint64_t j = 0; j < matrix[i].size(); j++) {
            out << matrix[i][j];
        }
        out << std::endl;
    }
    return out;
}
// Written to check matrix print.
void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (uint64_t i = 0; i < matrix.size(); i++) {
        sf::Sprite sprite(Sprites[65].toSprite());
        for (uint64_t j = 0; j < matrix[i].size(); j++) {
            // switch case, character values are specific sprites from the sheet
            switch (matrix[i][j]) {
                case '@':
                    sprite = Sprites[89].toSprite();
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    if (originalMap[i][j] == 'a' || originalMap[i][j] == '1') {
                        sprite = Sprites[39].toSprite();
                        sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                        target.draw(sprite, states);
                    }
                    switch (playerDir) {
                        case (Direction::Down):
                            sprite = Sprites[65].toSprite();
                            break;
                        case (Direction::Up):
                            sprite = Sprites[68].toSprite();
                            break;
                        case (Direction::Right):
                            sprite = Sprites[91].toSprite();
                            break;
                        case (Direction::Left):
                            sprite = Sprites[94].toSprite();
                            break;
                    }
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    break;
                case '.':
                    sprite = Sprites[89].toSprite();
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    break;
                case '#':
                    sprite = Sprites[84].toSprite();
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    break;
                case 'a':
                    sprite = Sprites[89].toSprite();
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    sprite = Sprites[39].toSprite();
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    break;
                case 'A':
                    sprite = Sprites[89].toSprite();
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    sprite = Sprites[7].toSprite();
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    break;
                case '1':
                    sprite = Sprites[89].toSprite();
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    sprite = Sprites[59].toSprite();
                    sprite.setPosition({static_cast<float>(j * TILE_SIZE),
                        static_cast<float>(i * TILE_SIZE)});
                    target.draw(sprite, states);
                    break;
                default:
                    continue;
            }
        }
    }
}

std::istream& operator>>(std::istream& in, Sokoban& s) {
    unsigned int row, column;
    in >> row;
    in >> column;
    s.matrix.resize(row, std::vector<char>(column));
    s.originalMap.resize(row, std::vector<char>(column));
    int Areas = 0;
    for (unsigned int i = 0; i < row; i++) {
        for (unsigned int j = 0; j < column; j++) {
            in >> s.matrix[i][j];
            s.originalMap[i][j] = s.matrix[i][j];
            if (s.matrix[i][j] == '@') {
                s.playerPos = {j, i};
            }
            if (s.matrix[i][j] == 'A' || s.matrix[i][j] == '1') {
                s.goals += 1;
            }
            if (s.matrix[i][j] == 'a' || s.matrix[i][j] == '1') {
                Areas++;
            }
        }
    }
    if (Areas < s.goals) {
        s.goals = Areas;
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    out << s.height() << " " << s.width();
    s.printMatrix(out);
    return out;
}

}  // namespace SB
