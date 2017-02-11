#include "Player.h"

Player::Player()
{
    // set this from the level, but not here
    _x = 0;//SCREEN_WIDTH - 100;
    _y = 0; //SCREEN_HEIGHT - 100;
}


Player::~Player()
{

}


AssetList Player::assetData()
{
    AssetList assets;

    Asset asset;
    asset.spriteFilename = "player.png";
    asset.name = "player";
    assets.push_back(asset);
    this->assetName = "player";

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
