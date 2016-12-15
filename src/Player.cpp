#include "Player.h"

Player::Player()
{
    _x = SCREEN_WIDTH - 100;
    _y = SCREEN_HEIGHT - 100;
    std::cout << "making a player" << std::endl;
}


Player::~Player()
{
    
}


AssetList Player::assetData()
{
    AssetList assets;
    
    Asset asset;
    asset.spriteFilename = "sprite.png";
    asset.name = "player";
    assets.push_back(asset);
    
    return assets;
}


void Player::move(int x, int y)
{
    this->_x += x;
    this ->_y += y;
}


void Player::move(Vector2D direction)
{
    move(direction.x, direction.y);
}