#include "mainFun.h"


vector<bool> keys(5);
vector<Plane> planes;
vector<Vector2f> clouds;
Vector2i beamCount(0, 0);

bool bounded(float f) {return 0 <= f && f <= SCREEN_SIZE;}
bool within(Vector2f v) {
    return bounded(v.x) && bounded(v.y);
}

Vector2f center(int i=0) {
    return planes[i].pos() + finalVel(SCREEN_SIZE / 20, planes[i].facing());
}

void left(int i=0) {
    planes[i].leftP();
}
void right(int i=0) {
    planes[i].rightP();
}
void up(int i=0) {
    planes[i].upP();
}
void down(int i=0) {
//    planes[0].drawBeam(center(i), );
}
//void space() {
//    for (int i = 0; i < planes.size(); i++) {
//        planes[i].spaceP();
//    }
//}

void drawPlanes(RenderWindow &window, int pov) {
    for (Plane p : planes) {
        p.draw(center(pov), window);
    }
}

Vector2f cloudPos(int i, int pov) {
    Vector2f ph = clouds[i] - center(pov);
    int xDir = (SCREEN_SIZE * ph.x / abs(ph.x)) * 4;
    int yDir = (SCREEN_SIZE * ph.y / abs(ph.y)) * 4;
    for (ph.x; !(-SCREEN_SIZE < ph.x && ph.x < SCREEN_SIZE) && !bounded(ph.x / 5); ph.x -= xDir);
    for (ph.y; !(-5 * SCREEN_SIZE < ph.y && ph.y < 0) && !bounded(ph.y / 5); ph.y -= yDir);
//    ph = Vector2f((int)ph.x % (5 * SCREEN_SIZE), (int)ph.y % (2 * SCREEN_SIZE));
    return ph;
}

void drawClouds(RenderWindow &window, int pov) {
    Vector2f ph = center(pov);
    while (clouds.size() < NUM_CLOUDS) {
        clouds.push_back(Vector2f(rand() % (5 * SCREEN_SIZE), -rand() % (5 * SCREEN_SIZE)));
    }
    for (int i = 0; i < clouds.size(); i++) {
        Vector2f ph = cloudPos(i, pov);
//        clouds[i].x += 2;
        RectangleShape rect;
        rect.setPosition(cloudPos(i, pov));
        rect.setSize(Vector2f(CLOUD_SIZE, CLOUD_SIZE / 2));
        rect.setFillColor(CLOUD);
        window.draw(rect);
    }
}

void drawWater(RenderWindow &window, int pov) {
    RectangleShape rect;
    rect.setPosition(Vector2f(0, SCREEN_SIZE / 2 - center(pov).y));
    rect.setSize(Vector2f(SCREEN_SIZE, center(pov).y + SCREEN_SIZE / 2));
    rect.setFillColor(WATER);
    window.draw(rect);
}

void showEnemies(RenderWindow &window, int pov) {
    planes[pov].showEnemiesP(center(pov), window, planes[!pov]);
}

vector<bool> getKeys() {
    return keys;
}

void setKey(bool set, int key) {
    keys[key] = set;
}

vector<Plane> getPlayers() {
    return planes;
}

void pushPlayer(Plane toAdd) {
    toAdd.setAccel(2);
    planes.push_back(toAdd);
}

void killPlayer() {
    planes = {};
    beamCount = Vector2i(0, 0);
}

void update() {
    Vector2f ph = center();
    for (int i = 0; i < planes.size(); i++) {
        planes[i].moveP();
        if (i == 0) continue;
        planes[i].ai(planes[0]);
    }
    if (keys[0]) {
        left(0);
    }
    if (keys[1]) {
        left(1);
    }
    if (keys[2]) {
        right(0);
    }
    if (keys[3]) {
        right(1);
    }
    if (keys[4]) {
        up(0);
    }
    if (keys[5]) {
        up(1);
    }
    if (keys[6]) {
        down(0);
    }
    if (keys[7]) {
        down(1);
    }

}

void GUI(RenderWindow &window, int pov) {
    planes[pov].GUI(window);
}

void beam(int pov) {
    if (pov && planes[1].energy() >= CHARGED_BEAM) {
        beamCount.y = BEAM_WIDTH;
    }
    else if (!pov && planes[0].energy() >= CHARGED_BEAM) {
        beamCount.x = BEAM_WIDTH;
    }
}

void doDraw(RenderWindow &window, int pov) {
    Font arial;
    arial.loadFromFile("data/arial.ttf");
    stringstream ss;
    ss << "Player Lives: " << to_string(planes[pov].life()) << endl;
    ss << "Enemy Lives:  " << to_string(planes[!pov].life());
    Text txt;
    txt.setString(ss.str());
    txt.setFont(arial);
    txt.setCharacterSize(30);
    txt.setFillColor(Color::Black);
    txt.setPosition(10, SCREEN_SIZE - 80);
    window.clear(BACK);
    drawPlanes(window, pov);
    drawWater(window, pov);
    drawClouds(window, pov);
    showEnemies(window, pov);
    window.draw(txt);
    GUI(window, pov);
}

void end(RenderWindow &window, String winner) {
//    int count = 0;
//    while (window.isOpen()) {
//        count += 20;
//        window.clear(BACK);
//        Font arial;
//        arial.loadFromFile("data/arial.ttf");
//        Text txt;
//        txt.setString(winner);
//        txt.setFont(arial);
//        txt.setCharacterSize(100);
//        txt.setFillColor(Color::Black);
//        txt.setPosition(90 * cos(count / (float)10) + 100, (SCREEN_SIZE - 200) / 2 * sin(count / (float)100) + (SCREEN_SIZE - 200) / 2);
//        window.draw(txt);
//        window.display();
//        Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window.close();
//            } else if (event.type == Event::KeyPressed) {
//                window.close();
//            }
//        }
//    }
    return;
}


bool handle(RenderWindow &window, RenderWindow &window2) {
    doDraw(window, 0);
    doDraw(window2, 1);
//    planes[0].drawBeam(center(0), planes[0].pos(), window, 10);
    if (beamCount.x != 0) {
        planes[0].shoot();
        planes[0].drawBeam(center(0), planes[0].pos(), window, beamCount.x);
        planes[1].drawBeam(center(1), planes[0].pos(), window2, beamCount.x);
        if (planes[1].hit(planes[0].pos())) planes[1].death();
        if (planes[1].life() < 0) {
            window2.close();
//            end(window, "Player one wins!");
            return false;
        }
        beamCount.x -= 2;
    }
    if (beamCount.y != 0) {
        planes[1].shoot();
        planes[0].drawBeam(center(0), planes[1].pos(), window, beamCount.y);
        planes[1].drawBeam(center(1), planes[1].pos(), window2, beamCount.y);
        if (planes[0].hit(planes[1].pos())) planes[0].death();
        if (planes[0].life() < 0) {
            window2.close();
            return false;
            end(window, "Player two wins!");
        }
        beamCount.y -= 2;
    }
    window.display();
    window2.display();
    return true;
}


