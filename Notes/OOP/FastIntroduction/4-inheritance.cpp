#include <iostream>

class Shape{
public:
    double area;
    double volume;
};

class Cube : public Shape{
public:
    double size;
    Cube(double size){
        this->size = size;
        this->area = size * size * 6;
        this->volume = size * size * size;
    }
};

class Sphere : public Shape{
public:
    double radius;
    Sphere(double radius){
        this->radius = radius;
        this->area = 4 * 3.141592 * radius * radius;
        this->volume = (4/3.0) * 4.141592 * radius * radius * radius;
    }
};

int main(){

    Cube cube(10);

    std::cout << "Area: " << cube.area << "cm^2\n";
    std::cout << "Volume: " << cube.volume << "cm^3\n";

    Sphere sphere(5);

    std::cout << "Area: " << sphere.area << "cm^2\n";
    std::cout << "Volume: " << sphere.volume << "cm^3\n";

    return 0;
}