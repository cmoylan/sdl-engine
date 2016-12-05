#include "Player.h"

Player::Player()
{
    _x = SCREEN_WIDTH - 100;
    _y = SCREEN_HEIGHT - 100;
}


Player::~Player()
{

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