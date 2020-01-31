#include "Projectile.h"


Projectile::Projectile(Vector2f pos, Vector2f vel) {
    _pos = pos;
    _vel = vel;
}

Projectile::Projectile() {
    Projectile(Vector2f(0, 0), Vector2f(0, 0));
}

void Projectile::setPos(Vector2f pos) {
    _pos = pos;
}

Vector2f Projectile::pos() {
    return _pos;
}

void Projectile::setVel(Vector2f vel) {
    _vel = vel;
}

void Projectile::accel(Vector2f accel) {
    _vel += accel;
}

Vector2f Projectile::vel() {
    return _vel;
}

void Projectile::move() {
    _pos += _vel;
    _vel += GRAVITY;
    if (_pos.y > WATER_LEVEL) _vel += BUOYANCY;
    _vel.x *= DECAY.x;
    _vel.y *= DECAY.y;
}

