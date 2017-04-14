#include "Player.h"

Player::Player()
{
    messageCentre().subscribe("collision", _uuid, bind(
                                   &Player::handleCollisionEvent, this, placeholders::_1)
                             );
}


Player::~Player()
{
    // FIXME: need to unsubscribe events here
    //messageCentre().
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
    cout << "collision from player!: " << message.test << endl;
}


void Player::setScreenPositionFromOffset(int x, int y)
{
}

