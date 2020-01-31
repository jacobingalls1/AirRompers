#ifndef SFML_TEMPLATE_MAINFUN_H
#define SFML_TEMPLATE_MAINFUN_H

#include "Plane.h"
#include "shared.h"
using namespace std;


void left();
void right();
void up();
void down();
void space();
void drawPlanes(RenderWindow &window, int pov=0);
void drawClouds(RenderWindow &window, int pov=0);
void drawWater(RenderWindow &window, int pov=0);
void showEnemies(RenderWindow &window, int pov=0);
vector<bool> getKeys();
void setKey(bool set, int key);
vector<Plane> getPlayers();
void pushPlayer(Plane);
void killPlayer();
void update();
void GUI(RenderWindow &window, int pov=0);
void beam(int pov=0);
void doDraw(RenderWindow &window, int pov=0);
bool handle(RenderWindow &window, RenderWindow &window2);

#endif
