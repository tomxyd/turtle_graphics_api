#include "Turtle.hpp"

Turtle::Turtle()
{
	init(0.f, 0.f, 0.f);
}

void Turtle::init(float x, float y, float angle) {
    m_x = x;
    m_y = y;
    m_degree = angle;

    //add_point(glm::vec2(m_x, m_y));
}

void Turtle::add_point(glm::vec2 point) {
    m_points.push_back(point);
    
}

void Turtle::forward(float distance) {

    if (m_points.size() < 1)
    {
        add_point(glm::vec2(m_x, m_y));
    }
    distance = distance / m_MAX_LENGTH;
    m_x += distance * std::cos(m_degree * (m_PI / 180));
    m_y += distance * std::sin(m_degree * (m_PI / 180));

    glm::vec2 vec(m_x, m_y);
    add_point(vec);
}

void Turtle::backward(float distance) {
    forward(-distance);
}

void Turtle::position() {
    std::cout << "(" << m_x * m_MAX_LENGTH << "," << m_y * m_MAX_LENGTH << ")\n";
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
    m_x = x / m_MAX_LENGTH;
    m_y = y / m_MAX_LENGTH;
}

void Turtle::set_x(float x) {
    m_x = x / m_MAX_LENGTH;
}

void Turtle::set_y(float y) {
    m_y = y / m_MAX_LENGTH;
}
void Turtle::set_heading(float degree) {
    m_degree = degree;
}

void Turtle::home()
{
    m_x = 0.f;
    m_y = 0.f;
    m_degree = 0.f;
}

void Turtle::square() {
    for (int i = 0; i < 4; i++)
    {
        forward(50);
        turn_right(90);
    }
}

void Turtle::square(float size_length) {
    for (int i = 0; i < 4; ++i) {
        forward(size_length);
        turn_right(90);
    }
}

void Turtle::triangle() {

    forward(25);
    turn_left(120);
    forward(25);
    turn_left(120);
    forward(25);
}

void Turtle::triangle(float size_length) {

    forward(size_length);
    turn_left(120);
    forward(size_length);
    turn_left(120);
    forward(size_length);
}

void Turtle::fill_color(int r, int g, int b) {

}