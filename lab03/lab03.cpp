#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Point {
public:
    virtual ~Point() = default;
    virtual double getX() const = 0;
    virtual double getY() const = 0;
    virtual void setXY(double x, double y) = 0;
};

class BasePoint : public Point {
public:
    BasePoint(double x, double y) : x_(x), y_(y) {}
    virtual ~BasePoint() = default;

    double getX() const override { return x_; }
    double getY() const override { return y_; }

    void setXY(double x, double y) override {
        x_ = x;
        y_ = y;
    }

protected:
    double x_, y_;
};

class Shape {
public:
    Shape(double x, double y) : x_(x), y_(y) {}
    virtual ~Shape() = default;

    virtual void draw() const = 0;
    virtual void erase() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
protected:
    double x_, y_;
};

class Parallelogram : public Shape {
public:
    BasePoint v1, v2, v3, v4;

    Parallelogram(double x1, double y1, double x2, double y2,
        double x3, double y3, double x4, double y4)
        : Shape(0, 0),
        v1(x1, y1), v2(x2, y2), v3(x3, y3), v4(x4, y4) {}

    void draw() const override {
        cout << "Parallelogram vertices:\n";
        cout << "(" << v1.getX() << ", " << v1.getY() << ")" << endl;
        cout << "(" << v2.getX() << ", " << v2.getY() << ")" << endl;
        cout << "(" << v3.getX() << ", " << v3.getY() << ")" << endl;
        cout << "(" << v4.getX() << ", " << v4.getY() << ")" << endl;
    }

    void erase() const override {
        cout << "Erasing Parallelogram\n";
    }

    void move(double dx, double dy) override {
        v1.setXY(v1.getX() + dx, v1.getY() + dy);
        v2.setXY(v2.getX() + dx, v2.getY() + dy);
        v3.setXY(v3.getX() + dx, v3.getY() + dy);
        v4.setXY(v4.getX() + dx, v4.getY() + dy);
    }

    void rotate(double angleDeg) override {
        double rad = angleDeg * M_PI / 180.0;
        double cx = (v1.getX() + v2.getX() + v3.getX() + v4.getX()) / 4;
        double cy = (v1.getY() + v2.getY() + v3.getY() + v4.getY()) / 4;
        rotatePoint(v1, rad, cx, cy);
        rotatePoint(v2, rad, cx, cy);
        rotatePoint(v3, rad, cx, cy);
        rotatePoint(v4, rad, cx, cy);
    }

protected:

    void rotatePoint(BasePoint& p, double rad, double cx, double cy) {
        double dx = p.getX() - cx;
        double dy = p.getY() - cy;
        double newX = cx + dx * cos(rad) - dy * sin(rad);
        double newY = cy + dx * sin(rad) + dy * cos(rad);
        p.setXY(newX, newY);
    }
};

class Rectangle : public Parallelogram {
public:
    Rectangle(double x, double y, double w, double h)
        : Parallelogram(x - w / 2, y - h / 2, x + w / 2, y - h / 2,
            x + w / 2, y + h / 2, x - w / 2, y + h / 2) {}

    void draw() const override {
        cout << "Rectangle vertices:\n";
        Parallelogram::draw();
    }

    void erase() const override {
        cout << "Erasing Rectangle\n";
    }
};

class Square : public Parallelogram {
public:
    Square(double x, double y, double side)
        : Parallelogram(x - side / 2, y - side / 2, x + side / 2, y - side / 2,
            x + side / 2, y + side / 2, x - side / 2, y + side / 2) {}

    void draw() const override {
        cout << "Square vertices:\n";
        Parallelogram::draw();
    }

    void erase() const override {
        cout << "Erasing Square\n";
    }
};

class Rhombus : public Parallelogram {
public:
    Rhombus(double x, double y, double side, double angleDeg)
        : Parallelogram(
            x, y - side / 2,
            x + side / 2 * cos(angleDeg * M_PI / 180.0), y,
            x, y + side / 2,
            x - side / 2 * cos(angleDeg * M_PI / 180.0), y) {}

    void draw() const override {
        cout << "Rhombus vertices:\n";
        Parallelogram::draw();
    }

    void erase() const override {
        cout << "Erasing Rhombus\n";
    }
};

class Line : public Shape {
public:
    BasePoint v1, v2;
    Line(double x1, double y1, double x2, double y2)
        : Shape(0, 0), v1(x1, y1), v2(x2, y2) {}

    void draw() const override {
        cout << "Line from (" << v1.getX() << ", " << v1.getY() << ") to (" << v2.getX() << ", " << v2.getY() << ")\n";
    }

    void erase() const override {
        cout << "Erasing Line\n";
    }

    void move(double dx, double dy) override {
        v1.setXY(v1.getX() + dx, v1.getY() + dy);
        v2.setXY(v2.getX() + dx, v2.getY() + dy);
    }

    void rotate(double angleDeg) override {
        double rad = angleDeg * M_PI / 180.0;
        double cx = (v1.getX() + v2.getX()) / 2, cy = (v1.getY() + v2.getY()) / 2;
        rotatePoint(v1, rad, cx, cy);
        rotatePoint(v2, rad, cx, cy);
    }
protected:
    void rotatePoint(BasePoint& p, double rad, double cx, double cy) {
        double dx = p.getX() - cx;
        double dy = p.getY() - cy;
        double newX = cx + dx * cos(rad) - dy * sin(rad);
        double newY = cy + dx * sin(rad) + dy * cos(rad);
        p.setXY(newX, newY);
    }
};

int main() {
    vector<unique_ptr<Shape>> shapes;

    shapes.emplace_back(make_unique<Parallelogram>(0, 0, 5, 0, 5, 3, 0, 3));
    shapes.emplace_back(make_unique<Line>(0, 0, 10, 10));
    shapes.emplace_back(make_unique<Rectangle>(0, 0, 20, 10));
    shapes.emplace_back(make_unique<Square>(5, 5, 15));
    shapes.emplace_back(make_unique<Rhombus>(2, 2, 10, 60));

    for (const auto& shape : shapes) {
        shape->draw();
        shape->move(1, 1);
        shape->rotate(15);
        shape->draw();
        shape->erase();
    }

    return 0;
}