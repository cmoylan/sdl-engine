#include "Player.h"

Player::Player()
{
    _x = SCREEN_WIDTH - 100;
    _y = SCREEN_HEIGHT - 100;
}


Player::~Player()
{
    
}


// AssetList Player::getAssets()
// {
//     // return a vector of Assets
//     // also store a pointer to the asset because that's not hacky
//     Asset* player = new Asset;
//     player->spriteFilename = "sprite.png";
//     player->parent = this;
//     this->asset = player;
//     AssetList assets;// = new Asset();
//     assets.push_back(player);
// 
//     return  assets;
// }


void Player::move(int x, int y)
{
    this->_x += x;
    this ->_y += y;
}


void Player::move(Vector2D direction)
{
    move(direction.x, direction.y);
}