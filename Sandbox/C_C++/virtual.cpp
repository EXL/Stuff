#include <iostream>

using namespace std;

class Animal {
public:
    void move() {
        cout << "Animal moves" << endl;
    }
    virtual void eat() {
        cout << "Animal eats" << endl;
    }
    virtual ~Animal() {
        cout << "Animal frees" << endl;
    }
};

class Wolf : public Animal {
public:
    void move() {
        cout << "Wolf moves" << endl;
    }
    void eat() {
        cout << "Wolf eats" << endl;
    }
    ~Wolf() {
        cout << "Wolf frees" << endl;
    }
};

class SmallWolf : public Wolf {
public:
    void move() {
        cout << "Smallwolf moves" << endl;
    }
    void eat() {
        cout << "Smallwolf eats" << endl;
    }
    ~SmallWolf() {
        cout << "Smallwolf frees" << endl;
    }
};

int main() {
    Animal *w = new SmallWolf();
    w->move();
    w->eat();
    delete w;

    return 0;
}
