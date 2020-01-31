#include "mainFun.h"


void mainWrap() {
    srand(time(NULL));

    killPlayer();

    pushPlayer(Plane(Vector2f(100000, 0), Vector2f(0, 0), 2500, 6, PLAYER, 100));
    pushPlayer(Plane(Vector2f(100000, 0), Vector2f(0, 0), 0, 6, PLAYER, 100));

    RenderWindow window(VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Air Rompers: Player 1");
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(30);

    RenderWindow window2(VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Air Rompers: Player 2");
    window2.setMouseCursorVisible(false);
    window2.setFramerateLimit(30);
    window2.setPosition(Vector2i(-1500, 0));

    window.requestFocus();
    while(window.isOpen()) {

        if (!handle(window, window2)) return;
//        doDraw(window, 0);

        update();

//        window.display();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case Keyboard::Escape:
//                    case Keyboard::Q:
                        window.close();
                        break;
                    case Keyboard::Left:
                        setKey(true, 0);
                        break;
                    case Keyboard::A:
                        setKey(true, 1);
                        break;
                    case Keyboard::Right:
                        setKey(true, 2);
                        break;
                    case Keyboard::D:
                        setKey(true, 3);
                        break;
                    case Keyboard::Up:
                        setKey(true, 4);
                        break;
                    case Keyboard::W:
                        setKey(true, 5);
                        break;
                    case Keyboard::Down:
                        setKey(true, 6);
                        beam(0);
                        break;
                    case Keyboard::S:
                        setKey(true, 7);
                        beam(1);
                        break;
                }
            } else if (event.type == Event::KeyReleased) {
                switch (event.key.code) {
                    case Keyboard::Left:
                        setKey(false, 0);
                        break;
                    case Keyboard::A:
                        setKey(false, 1);
                        break;
                    case Keyboard::Right:
                        setKey(false, 2);
                        break;
                    case Keyboard::D:
                        setKey(false, 3);
                        break;
                    case Keyboard::Up:
                        setKey(false, 4);
                        break;
                    case Keyboard::W:
                        setKey(false, 5);
                        break;
                    case Keyboard::Down:
                        setKey(false, 6);
                        break;
                    case Keyboard::S:
                        setKey(false, 7);
                        break;
                }
            }
        }
    }
}

int main() {

    while (true) mainWrap();

    return 0;
}
