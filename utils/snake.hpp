#pragma once

#include "pos.hpp"
#include <vector>

class snake {

private:
    std::vector<pos> body;
    dir direction;
    bool shouldGrow;

public:
    snake(int startX, int startY);

    void move();
    void changeDirection(dir newDir);
    void grow();

    pos getHead() const;
    const std::vector<pos>& getBody() const;
    void wrap(int width, int height, int uiHeight);
    bool checkSelfCollision() const;
};


snake::snake(int startX, int startY) {
    direction = RIGHT;
    shouldGrow = false;

    body.push_back({startX,     startY});
    body.push_back({startX - 1, startY});
    body.push_back({startX - 2, startY});
}

void snake::move() {

    pos newHead = body[0];

    switch (direction) {
        case UP:    newHead.y--; break;
        case DOWN:  newHead.y++; break;
        case LEFT:  newHead.x--; break;
        case RIGHT: newHead.x++; break;
    }

    body.insert(body.begin(), newHead);

    if (!shouldGrow)
        body.pop_back();
    else
        shouldGrow = false;
}

void snake::grow() {
    shouldGrow = true;
}

void snake::changeDirection(dir newDir) {

    if ((direction == UP && newDir == DOWN) ||
        (direction == DOWN && newDir == UP) ||
        (direction == LEFT && newDir == RIGHT) ||
        (direction == RIGHT && newDir == LEFT))
        return;

    direction = newDir;
}

const std::vector<pos>& snake::getBody() const {
    return body;
}

pos snake::getHead() const {
    return body[0];
}

void snake::wrap(int width, int height, int uiHeight) {

    pos& head = body[0];  

    if (head.x < 0)
        head.x = width - 1;
    else if (head.x >= width)
        head.x = 0;

    if (head.y < uiHeight)
        head.y = height - 1;
    else if (head.y >= height)
        head.y = uiHeight;
}

bool snake::checkSelfCollision() const {
    const pos& head = body[0];

    for (int i = 1; i < body.size(); i++) {
        if (body[i].x == head.x && body[i].y == head.y) {
            return true;
        }
    }

    return false;
}