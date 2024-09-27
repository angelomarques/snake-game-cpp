#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>

class Shape
{
private:
    std::string name;

public:
    // Constructor
    Shape(const std::string &name);

    virtual void draw() const = 0;

    virtual ~Shape() = default;
};

class Square : public Shape
{
public:
    Square();

    void draw() const override;
};

#endif // SHAPE_HPP
