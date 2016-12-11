#include "Player.h"

Player::Player()
{
    _x = SCREEN_WIDTH - 100;
    _y = SCREEN_HEIGHT - 100;
}


Player::~Player()
{

}


AssetList Player::getAssets()
{
    // return a vector of Assets
    Asset player = {
        "sprite.png", // filename
        nullptr, // texture
        _x, // coords
        _y,
        0, // clips
        0
    };
    AssetList assets;
    assets.push_back(player);
    return  assets;
}


Vector2D Player::getPos()
{
    Vector2D pos = {_x, _y};
    return pos;
}


void Player::move(int x, int y)
{
    _x += x;
    _y += y;
}


void Player::move(Vector2D direction)
{
    move(direction.x, direction.y);
}