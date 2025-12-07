#include "Turtle.hpp"

Turtle::Turtle()
{
	init(0.f, 0.f, 0.f);
}

void Turtle::init(float x, float y, float angle) {
    m_x = x;
    m_y = y;
    m_degree = angle;

    add_point(glm::vec2(x, y));
}

void Turtle::add_point(glm::vec2 point) {
    points.push_back(point);
    
}

void Turtle::forward(float distance) {
    distance = distance / 100.f;
    x += distance * std::cos(degree * (m_PI / 180));
    y += distance * std::sin(degree * (m_PI / 180));

    glm::vec2 vec(x, y);
    add_point(vec);
}

void Turtle::backward(float distance) {
    forward(-distance);
}

void Turtle::position() {
    std::cout << "(" << x * 100.f << "," << y * 100.f << ")\n";
}