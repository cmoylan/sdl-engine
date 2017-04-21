#pragma once

#include <iostream>

#include "constants.h"
#include "guile.h"
#include "uuid.h"

#include "Drawable.h"
#include "MessageCentre.h"
#include "Vector2D.h"


class Player : public Drawable {

public:
    // prototyping scriptable here

    SCM lc_init;
    SCM lc_update;
    SCM lc_collision;

    inline void initLifecycleFunctions()
    {
        scm_c_primitive_load_path("player.scm");

        lc_init = Guile::lookup("init");
        lc_update = Guile::lookup("update");
        lc_collision = Guile::lookup("collision");
    }
    // END prototyping

    int _uuid = generateUuid();

    Player();
    ~Player();

    // generic start-up stuff that I don't want in the constructor
    void init();


    void setScreenPositionFromOffset(int x, int y);

    // Point spriteClips()

    AssetList assetData();

    void handleCollisionEvent(Message message);
};
