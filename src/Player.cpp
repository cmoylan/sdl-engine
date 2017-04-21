#include "Player.h"

Player::Player()
{

}


Player::~Player()
{
    // FIXME: need to unsubscribe events here
    //messageCentre().
}


void Player::init()
{
    messageCentre().subscribe("collision", _uuid, bind(
                                  &Player::handleCollisionEvent, this, placeholders::_1)
                             );

    initLifecycleFunctions();
    scm_call_0(lc_init);
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
    scm_call_0(lc_collision);
}


void Player::setScreenPositionFromOffset(int x, int y)
{
}

