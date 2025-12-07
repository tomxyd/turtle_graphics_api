#include "Turtle.hpp"

Turtle::Turtle()
{
	init(0.f, 0.f, 0.f);
}

void Turtle::init(float x, float y, float angle) {
    m_x = x;
    m_y = y;
    m_degree = angle;

    add_point(glm::vec2(m_x, m_y));
}

void Turtle::add_point(glm::vec2 point) {
    m_points.push_back(point);
    
}

void Turtle::forward(float distance) {
    distance = distance / 100.f;
    m_x += distance * std::cos(m_degree * (m_PI / 180));
    m_y += distance * std::sin(m_degree * (m_PI / 180));

    glm::vec2 vec(m_x, m_y);
    add_point(vec);
}

void Turtle::backward(float distance) {
    forward(-distance);
}

void Turtle::position() {
    std::cout << "(" << m_x * 100.f << "," << m_y * 100.f << ")\n";
}

void Turtle::heading()
{
    std::cout << m_degree << "\n";
}

void Turtle::turn_left(float angle)
{
    m_degree = m_degree + angle;
}

void Turtle::turn_right(float angle)
{
    m_degree = 360 - (angle - m_degree);
}

void Turtle::set_pos(float x, float y) {
    m_x = x / 100.f;
    m_y = y / 100.f;
}