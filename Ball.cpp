#include "Ball.hpp"
#include <cmath>
#define PI 3.1415926535

void Ball::setCollidable(bool collidable) {
    this->collidable = collidable;
}

bool Ball::isCollidable() const {
    return collidable;
}

void Ball::setVelocity(const Velocity& velocity) {
    this->velocity = velocity; //Задает скорость объекта
}

Velocity Ball::getVelocity() const {
    return velocity; // скорость объекта
}

void Ball::draw(Painter& painter) const {
    painter.draw(center, radius, color);
}

void Ball::setCenter(const Point& center) {
    this->center = center;
}


Point Ball::getCenter() const {
    return center;
}

/**
 * @details обратите внимание, что метод setRadius() не требуется
 */

double Ball::getRadius() const {
    return radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return (4.0/3.0 * PI * radius * radius * radius);
}
