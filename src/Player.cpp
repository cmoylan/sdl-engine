#include "Player.h"

Player::Player()
{
    //_screenX = 0;
    //_screenY = 0;
}


Player::~Player()
{

}


AssetList Player::assetData()
{
    AssetList assets;

    Asset asset;
    asset.spriteFilename = "player.png";
    asset.name = "player.png";
    assets.push_back(asset);
    this->assetName = "player.png";

    return assets;
}


// TODO: move this into drawable
// void Player::move(int x, int y)
// {
//     // if is player
//     this->screenX += x;
//     this ->screenY += y;
//     // and then always update level pox
//     this->levelX += x;
//     this->levelY += y;
//
//     //
//     // DO THIS
//     // this updates screen pos and level pos
//     //
// }
//
//
// void Player::move(Vector2D direction)
// {
//     move(direction.x, direction.y);
// }
