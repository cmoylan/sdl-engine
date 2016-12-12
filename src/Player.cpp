#include "Player.h"

Player::Player()
{
    _x = SCREEN_WIDTH - 100;
    _y = SCREEN_HEIGHT - 100;
}


Player::~Player()
{
    free(asset);
}


AssetList Player::getAssets()
{
    // return a vector of Assets
    // also store a pointer to the asset because that's not hacky
    Asset* player = new Asset;
    player->spriteFilename = "sprite.png";
    player->parent = this;
    this->asset = player;
    AssetList assets;// = new Asset();
    assets.push_back(player);
    //this->aaa = "asdf";
    return  assets;
}


// Vector2D Player::getPos()
// {
//     Vector2D pos = {_x, _y};
//     return pos;
// }


void Player::move(int x, int y)
{
    std::cout << "moving" << std::endl;
    this->_x += x;
    this ->_y += y;
    
    this->aaa = "toast";
}


void Player::move(Vector2D direction)
{
    move(direction.x, direction.y);
}

// int Player::x()
// {
//     return _x;
// }
// 
// int Player::y()
// {
//     return _y;
// }

