#pragma once
#include <string>

class Position {
private:
    int x;
    int y;

public:
    Position(int x, int y);
    Position() : x(0), y(0) {}

    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);

    std::string toString();

    double distance(Position position);
    void move(int dx, int dy);
};
