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

