// Copyright 2026 Soon Thao
#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace sb {

class TextureView {
 public:
    TextureView(std::shared_ptr<sf::Texture> Texture, sf::IntRect view);
    // Add constructors
    TextureView crop(sf::IntRect area) const;
    sf::Vector2u getSize() const;

    sf::Sprite toSprite() const;
    sf::Image toImage() const;  // Optional
 private:
    const std::shared_ptr<sf::Texture> sharedTexture;
    sf::IntRect currView;
    // Fields go here
};

class SpriteSheet {
 public:
    SpriteSheet(sf::Image img, sf::Vector2u tileSize);
    SpriteSheet(sf::Image img, sf::Vector2u tileSize, int margin);
    // You can add additional constructors if desired

    sf::Vector2u getTileSize() const;

    sf::Vector2u size() const;
    size_t length() const;
    size_t width() const;
    size_t height() const;

    TextureView operator[](sf::Vector2u pt) const;
    TextureView operator[](size_t i) const;
 private:
    std::shared_ptr<sf::Texture> currTexture;
    sf::Vector2u sheetTileSize;
    int margins;
    // Fields go here
};
}  // namespace sb
