#ifndef TURTLE_H
#define TURTLE_H
#include <iostream>
#include <glm/glm.hpp>
#include <vector>

class Turtle
{
public:
    float m_x;
    float m_y;
    float m_degree;
    std::vector<glm::vec2> m_points;

    Turtle();
    void init(float x, float y, float angle);
    void forward(float distance);  
    void backward(float distance);
    void position();
    void heading();
    void turn_left(float angle);
    void turn_right(float angle);
    void set_pos(float x, float y = 0.f);

private:
    void add_point(glm::vec2 point);
    const float m_PI = 3.1415926535;
};

#endif