#ifndef SFML_TEMPLATE_PROJECTILE_H
#define SFML_TEMPLATE_PROJECTILE_H

#include "shared.h"
using namespace std;

class Projectile {
protected:
    Vector2f _pos;
    Vector2f _vel;
public:
    Projectile(Vector2f pos, Vector2f vel);
    Projectile();
    void setPos(Vector2f pos);
    Vector2f pos();
    void setVel(Vector2f vel);
    void accel(Vector2f accel);
    Vector2f vel();
    void move();
};


#endif
