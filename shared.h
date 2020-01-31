#ifndef SFML_TEMPLATE_CONST_H
#define SFML_TEMPLATE_CONST_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;

#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
using namespace std;

const int SCREEN_SIZE = 1000, MAX_ANGLE = 10000, NUM_KEYS = 8,
        NUM_CLOUDS = 100, CLOUD_SIZE = 200, BULLET_LONGEVITY = 5;
const float PI = 3.14159265, PLANE_TURN = 190, TERMINAL = 20, STALL = .9;
const Vector2f GRAVITY(0, 1.2), BUOYANCY(0, -4), DECAY(.94, .94);
const Color BACK(Color::Cyan), CLOUD(Color::White), BEAM(Color::Yellow),
        WATER(Color::Blue), PLAYER(Color::Black), ENEMY(Color::Magenta),
        CHARGED1(Color(244, 185, 66)), CHARGED2(Color::Red);
const int WATER_LEVEL = 0, HEIGHT_LIMIT = -6000, BEAM_WIDTH = 100,
        CHARGED_BEAM = 100, RADAR_RANGE = 500, KNOCKBACK = 5;


float getRad(float angle);
Vector2f finalVel(float speed, float angle);
Vector2f finalVel(Vector2f speedAngle);

#endif
