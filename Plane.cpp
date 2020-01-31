#include "Plane.h"

Plane::Plane(Vector2f pos, Vector2f vel, float facing, float accel, Color color, int lives) : Projectile(pos, vel) {
    _face = facing;
    _accel = accel;
    _accelph = accel;
    _col = color;
    _life = lives;
    _energy = 0;
    _powerOn = 0;
}

Plane::Plane() {
    Plane(Vector2f(0, 0), Vector2f(0, 0), 0, 2, Color::White);
}

void Plane::leftP() {
    _face -= PLANE_TURN;
}

void Plane::rightP() {
    _face += PLANE_TURN;
}

void Plane::upP() {
    _vel += finalVel(_accel, _face);
}

void Plane::downP() {
    _vel -= finalVel(_accel, _face);
}

void Plane::setAccel(float accel) {
    _accel = accel;
}

void Plane::draw(Vector2f screenPos, RenderWindow &window) {
    VertexArray ret(LinesStrip, 2);
    Vector2f relPos = _pos - screenPos + Vector2f(SCREEN_SIZE / 2, SCREEN_SIZE / 2);
    ret[0].position = relPos;
    ret[0].color = _col;
    ret[1].position = relPos - finalVel(_accel * 10, _face);
    ret[1].color = _col;
    window.draw(ret);
    ret[1].position = relPos - finalVel(_accel * 10, _face + 200);
    window.draw(ret);
    ret[1].position = relPos - finalVel(_accel * 10, _face - 200);
    window.draw(ret);
    ret[1].position = relPos + _vel;
    ret[0].color = Color::Red;
    ret[1].color = Color::Red;
    window.draw(ret);
}

void Plane::showEnemiesP(Vector2f screenPos, RenderWindow &window, Plane enemy) {
    VertexArray v(LinesStrip, 2);
    Vector2f dir((enemy.pos().x - _pos.x) / RADAR_RANGE, (enemy.pos().y - _pos.y) / RADAR_RANGE);
    Vector2f relPos = _pos - screenPos + Vector2f(SCREEN_SIZE / 2, SCREEN_SIZE / 2);
    if (abs(dir.x) > 50) dir.x = (50 * dir.x / abs(dir.x));
    if (abs(dir.y) > 50) dir.y = (50 * dir.y / abs(dir.y));
    v[0].position = relPos;
    v[0].color = ENEMY;
    v[1].position = relPos + dir;
    v[1].color = ENEMY;
    window.draw(v);
}

float Plane::facing() {
    return _face;
}

int goodMod(float f, int i) {
    int ph = (int)f % i;
    if (ph < 0) ph += i;
    return ph;
}

void Plane::ai(Plane player) {
//    if (isFacing(player)) _vel += finalVel(_accel, _face);
//    else _face += PLANE_TURN;
}

void Plane::moveP() {
    _pos += _vel;
    _vel += GRAVITY;
    if (_pos.y > WATER_LEVEL) _vel += BUOYANCY;
    if (_pos.y - 100 > WATER_LEVEL) _vel += BUOYANCY;
    if (_pos.y - 200 > WATER_LEVEL) _vel += BUOYANCY;
    if (_pos.y < HEIGHT_LIMIT) {
        _accel *= STALL;
        _vel.y += 2;
    }
    else _accel = _accelph;
    _vel.x *= DECAY.x;
    _vel.y *= DECAY.y;
    if (_energy++ >= CHARGED_BEAM) _energy = CHARGED_BEAM;
    _powerOn++;
    _powerOn %= 10;
}

int Plane::life() {
    return _life;
}

int Plane::energy() {
    return _energy;
}

int Plane::shoot() {
    _energy = 0;
}

void Plane::death() {
    _life--;
}

void Plane::drawBeam(Vector2f screenPos, Vector2f beamPos, RenderWindow &window, int beamWidth) {
    Vector2f relPos = beamPos - screenPos + Vector2f(SCREEN_SIZE / 2, SCREEN_SIZE / 2);
    RectangleShape rect;
    rect.setFillColor(BEAM);
    rect.setPosition(relPos.x - beamWidth / 2, 0);
    rect.setSize(Vector2f(beamWidth, SCREEN_SIZE));
    window.draw(rect);
    rect.setPosition(0, relPos.y - beamWidth / 2);
    rect.setSize(Vector2f(SCREEN_SIZE, beamWidth));
    window.draw(rect);
}

bool Plane::hit(Vector2f beamPos) {
    if (abs(_pos.x - beamPos.x) < BEAM_WIDTH) {
        _life--;
        _vel.x += (_pos.x - beamPos.x) * KNOCKBACK;
        return true;
    } else if (abs(_pos.y - beamPos.y) < BEAM_WIDTH) {
        _life--;
        _vel.y += (_pos.y - beamPos.y) * KNOCKBACK;
        return true;
    }
    return false;
}

void Plane::GUI(RenderWindow &window) {
    RectangleShape rect;
    rect.setPosition(0, 0);
    rect.setSize(Vector2f(SCREEN_SIZE * (_energy / (float)CHARGED_BEAM), 10));
    rect.setFillColor(CHARGED1);
    if (_energy == CHARGED_BEAM && _powerOn > 5) rect.setFillColor(CHARGED2);
    window.draw(rect);
}