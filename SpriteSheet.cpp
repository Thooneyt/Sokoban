// Copyright 2026 Soon Thao
#include "SpriteSheet.hpp"

namespace sb {
TextureView::TextureView(std::shared_ptr<sf::Texture> Texture,
sf::IntRect view) : sharedTexture(Texture), currView(view) {
    if (!Texture) {
        throw std::exception();
    }
    if (view.size.x > static_cast<int>(Texture->getSize().x) ||
        view.size.y > static_cast<int>(Texture->getSize().y)) {
        throw std::exception();
    }
    if (view.position.x < 0 || view.position.y < 0) {
        throw std::exception();
    }
}

TextureView TextureView::crop(sf::IntRect area) const {
if (area.size.x + area.position.x > static_cast<int>(currView.size.x) ||
    area.size.y + area.position.y > static_cast<int>(currView.size.y)) {
        throw std::out_of_range("Out of Range!");
    }
// First crop check checks for
// if the size of the crop will push it out of bounds.
if (area.position.x < 0 || area.position.y < 0) {
        throw std::out_of_range("Out of Range!");
    }
        // Second crop check checks for
        // if the position from which it crops is out of bounds.
    return TextureView(sharedTexture, sf::IntRect(
        {area.position.x + currView.position.x, area.position.y + currView.position.y},
        {area.size.x, area.size.y}));
}

sf::Vector2u TextureView::getSize() const {
    return sf::Vector2u(currView.size.x, currView.size.y);
    // currView members x and y will give the Vector2u of the current view.
}

sf::Sprite TextureView::toSprite() const {
    return sf::Sprite(*sharedTexture, currView);
    // If currView is done right, it has the
    // position and size of the Sprite already
    // so just dereference the texture and
    // return a sprite using the constructor.
}

sf::Image TextureView::toImage() const {
    sf::Image img = sharedTexture->copyToImage();
    sf::Image currImg(sf::Vector2u(currView.size.x, currView.size.y));
    if (!currImg.copy(img, sf::Vector2u(0, 0), currView, true)) {
         throw std::exception();
    }
    // The above is literally only there
    // because of ignoring return value error.
    return currImg;
}

SpriteSheet::SpriteSheet(sf::Image img, sf::Vector2u tileSize)
    : sheetTileSize(tileSize), margins(0) {
        currTexture = std::make_shared<sf::Texture>();
        if (!currTexture->loadFromImage(img)) {
            throw std::exception();
        }
        if (tileSize.x <= 0 || tileSize.y <= 0) {
            throw std::exception();
        }
}
SpriteSheet::SpriteSheet(sf::Image img, sf::Vector2u tileSize, int margin)
    : sheetTileSize(tileSize), margins(margin) {
        currTexture = std::make_shared<sf::Texture>();
        // Initialize the shared pointer.
    if (!currTexture->loadFromImage(img)) {
        throw std::exception();
    }
    // The above throws if the either the shared pointer is NULL,
    // or if it fails to load the image.
}
sf::Vector2u SpriteSheet::getTileSize() const {
    return {sheetTileSize.x, sheetTileSize.y};
}
sf::Vector2u SpriteSheet::size() const {
    return {static_cast<unsigned int>(width()),
        static_cast<unsigned int>(height())};
}
size_t SpriteSheet::length() const {
    return width() * height();
}
size_t SpriteSheet::width() const {
    return ((currTexture->getSize().x) / (sheetTileSize.x));
}
size_t SpriteSheet::height() const {
    return ((currTexture->getSize().y) / (sheetTileSize.y));
}
TextureView SpriteSheet::operator[](sf::Vector2u pt) const {
    if (pt.x >= width() || pt.y >= height()) {
        throw std::out_of_range("out of range!");
    }  // Checks if pt indices are within bounds.
    int row = pt.x * (sheetTileSize.x + margins);
    int column = pt.y * (sheetTileSize.y + margins);
    // row and column are just converting from pt to pixel dimensions.
    return TextureView(currTexture, sf::IntRect({row, column},
        {static_cast<int>(sheetTileSize.x),
            static_cast<int>(sheetTileSize.y)}));
}
TextureView SpriteSheet::operator[](size_t i) const {
    if (i >= width() * height()) {
        throw std::out_of_range("out of range!");
    }

    int column = (i % width()) * (sheetTileSize.x + margins);
    // i is an index value, to get proper row position divide i by the width
    // sheetTileSize.x + margins used to convert to pixel dimensions.
    int row = (i / width()) * (sheetTileSize.y + margins);
    return TextureView(currTexture, sf::IntRect({column, row},
        {static_cast<int>(sheetTileSize.x),
        static_cast<int>(sheetTileSize.y)}));
}
};  // namespace sb
