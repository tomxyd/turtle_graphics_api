#ifndef TURTLE_H
#define TURTLE_H
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

    void heading()
    {
        std::cout << degree << "\n";
    }

    void left(float angle)
    {
        this->degree = degree + angle;
    }

    void right(float angle)
    {
        this->degree = 360 - (angle - degree);
    }

    void set_pos(float x, float y = 0.f) {
        this->x = x / 100.f;
        this->y = y / 100.f;
    }
private:
    void add_point(glm::vec2 point);

    const float m_PI = 3.1415926535;
};

#endif