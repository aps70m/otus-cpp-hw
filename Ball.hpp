#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
private:
    Velocity velocity;
    Point center;
    double radius;
    Color color;
    bool collidable;

public:
    void setVelocity(const Velocity& velocity);
    void setCollidable(bool collidable);
    void setCenter(const Point& center);
    void setRadius(double r) { radius = r; }
    void setColor(const Color& c) { color = c; }
    bool isCollidable() const;

    Velocity getVelocity() const;
    Point getCenter() const;
    Color getColor() const { return color; }
    double getRadius() const;
    double getMass() const;
    void draw(Painter& painter) const;
};
