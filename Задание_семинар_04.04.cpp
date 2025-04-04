#include <iostream>
#include <string>

using namespace std;

class animal {

public:
    int age;
    double weight;
    animal(int d, int a) {
        age = d;
        weight = a;
        cout << "created" << endl;
    }
    ~animal() {
        cout << "deleted" << endl;
    }
    void print() const {
        cout << age << " " << weight << endl;
    }
    virtual void walk() const {
        cout << "animal walk" << endl;
    }
};
class elephant : public animal {
public:
    double trunk;
    string food;
    elephant(int age, double weight, double t, string f) : animal(age, weight) {
        trunk = t;
        food = f;
        cout << "elephant created" << endl;
    }
    ~elephant() {
        cout << "elephant deleted" << endl;
    }
    void walk() const override {
        cout << "The elephant stomps" << endl;
    }
};
class cat : public animal {
public:
    int children;
    string colour;
    cat(int age, double weight, int k, string c) : animal(age, weight) {
        children = k;
        colour = c;
        cout << "cat created" << endl;
    }
    ~cat() {
        cout << "cat deleted" << endl;
    }
    void walk() const override {
        cout << "The cat is rinning" << endl;
    }
};
class kangaroo : public animal {
public:
    double power;
    string place;
    kangaroo(int age, double weight, double d, string p) : animal(age, weight) {
        power = d;
        place = p;
        cout << "kangaroo created" << endl;
    }
    ~kangaroo() {
        cout << "kangaroo deleted" << endl;
    }
    void walk() const override {
        cout << "The kangaroo jumps" << endl;
    }
};
int main() {
    elephant ele{ 12, 189.9, 78.12, "apple" };
    ele.print();
    ele.walk();

    cat kit{ 6, 5.6, 3, "red" };
    kit.print();
    kit.walk();

    kangaroo kng{ 8, 79.3, 55.8, "Australia" };
    kng.print();
    kng.walk();
}