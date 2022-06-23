// Circle.h

#ifndef CIRCLE_INCLUDED
#define CIRCLE_INCLUDED

class Circle
{
public:
    Circle(double x, double y, double r);
    void draw() const;
    bool scale(double factor);
    double radius() const;
private:
    double m_x;
    double m_y;
    double m_r;
    // Class invariant:  m_r > 0
};

double area(const Circle& circ);

#endif  // CIRCLE_INCLUDED