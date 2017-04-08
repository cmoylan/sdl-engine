#include "Player.h"

Player::Player()
{
    messageCentre().subscribe("collision", bind(
                                  &Player::handleCollisionEvent, this, placeholders::_1)
                             );
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


void Player::handleCollisionEvent(Message message)
{
    cout << "collision from player!" << endl;
}


void Player::setScreenPositionFromOffset(int x, int y)
{
}

