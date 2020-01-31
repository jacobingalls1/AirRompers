#include "shared.h"

float getRad(float angle) {
    return PI * 2 * ((int)angle % MAX_ANGLE) / MAX_ANGLE;
}

Vector2f finalVel(float speed, float angle) {
    return Vector2f(speed * cos(getRad(angle)), speed * sin(getRad(angle)));
}

Vector2f finalVel(Vector2f speedAngle) {
    return finalVel(speedAngle.x, speedAngle.y);
}