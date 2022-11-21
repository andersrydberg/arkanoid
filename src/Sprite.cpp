//
// Created by Anders Rydberg on 2022-11-21.
//

#include "Sprite.h"

Sprite::Sprite() : Sprite(0, 0, 0, 0) {

}

Sprite::Sprite(int x, int y, int w, int h) : rect {x, y, w, h} {

}
