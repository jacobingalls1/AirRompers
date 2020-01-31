#ifndef SFML_TEMPLATE_PLANE_H
#define SFML_TEMPLATE_PLANE_H

#include "shared.h"
#include "Projectile.h"
using namespace std;


class Plane : public Projectile {
private:
    float _face;
    float _accel;
    float _accelph;
    Color _col;
    int _life;
    int _energy;
    int _powerOn;
public:
    Plane(Vector2f pos, Vector2f vel, float facing, float accel, Color color, int lives=10);
    Plane();
    void leftP();
    void rightP();
    void upP();
    void downP();
    void setAccel(float accel);
    void draw(Vector2f screenPos, RenderWindow &window);
    void showEnemiesP(Vector2f screenPos, RenderWindow &window, Plane enemy);
    float facing();
    void ai(Plane player);
    void moveP();
    int life();
    int energy();
    int shoot();
    void death();
    void drawBeam(Vector2f screenPos,
    Vector2f beamPos, RenderWindow &window, int beamWidth);
    bool hit(Vector2f beamPos);
    void GUI(RenderWindow &window);

};


#endif
