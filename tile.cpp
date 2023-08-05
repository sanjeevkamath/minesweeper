//
// Created by sanje on 7/31/2023.
//

#include "tile.h"
Tile::Tile(int x, int y) {
//    tileTexture.loadFromFile("files/images/tile_hidden.png");
    hiddenTexture.loadFromFile("files/images/tile_hidden.png");
    revealedTexture.loadFromFile("files/images/tile_revealed.png");
    flagTexture.loadFromFile("files/images/flag.png");
    mineTexture.loadFromFile("files/images/mine.png");


    tileSprite.setTexture(hiddenTexture);
    flagSprite.setTexture(flagTexture);
    mineSprite.setTexture(mineTexture);
    pauseSprite.setTexture(revealedTexture);


    tileSprite.setPosition(x,y);
    flagSprite.setPosition(x,y);
    mineSprite.setPosition(x,y);
    pauseSprite.setPosition(x,y);
    numberSprite.setPosition(x,y);







}

void Tile::markFlag() {
    if (hidden)    flag = !flag;
}






void Tile::exposeTile(){
    if(hasMine){
        cout << "Game over" << endl;
        return;
    }
    if(!flag && hidden){

        tileSprite.setTexture(revealedTexture);
        hidden = false;
        if(neighboringMines != 0){

            numberTexture.loadFromFile(numMinesString);
            numberSprite.setTexture(numberTexture);
        }
//        else {
//            revealEmptyTiles();
//        }
//
    }

}



void Tile::revealEmptyTiles(){
    if(neighboringMines > 0) {
        return;
    }
    for (int i = 0; i < adjacentTiles.size(); i++) {
        Tile* adjacentTile = adjacentTiles.at(i);
        if (adjacentTile->hidden && !adjacentTile->flag) {
            adjacentTile->exposeTile();

        }
}}

//            void Tile::revealEmptyTiles(){
//
//                for (int i = 0; i < adjacentTiles.size(); i++) {
//                    Tile* adjacentTile = adjacentTiles.at(i);
//                    if (!adjacentTile->hidden || adjacentTile->flag) {
//                        // Skip tiles that are already revealed or flagged
//                        continue;
//                    }
//                    adjacentTile->exposeTile();
//                    if (adjacentTile->neighboringMines == 0) {
//                        // If the adjacent tile has no neighboring mines, recursively reveal its adjacent tiles
//                        adjacentTile->revealEmptyTiles();
//                    }
//                }
//
//            }