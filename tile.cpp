//
// Created by sanje on 7/31/2023.
//

#include "tile.h"
Tile::Tile(int x, int y) {
    tileTexture.loadFromFile("files/images/tile_hidden.png");
    tileSprite.setTexture(tileTexture);
    tileSprite.setPosition(x,y);
}
//Tile::Tile(int i, int j) {
  //  tileTexture.loadFromFile("files/images/tile_hidden.png");
//    tileSprite.setTexture(tileTexture);




void Tile::setPosition(float x, float y) {
    tileSprite.setPosition(x,y);
}