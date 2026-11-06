#include <iostream>

// Constructor --> special method that is automatically called when an object is instantiated useful for assigning values to attributes as arguments

class Human{
    public:
        std::string name;
        std::string occupation;
        int age;

        void eat(){
            std::cout << name << " is eating\n";
        }
        void drink(){
            std::cout << name << " is drinkin\n";
        }
        void sleep(){
            std::cout << name << " is sleeping\n";
        }
};

class Student{
    public:
        std::string name;
        int age;
        double gpa;

    Student(std::string name, int age, double gpa){
        this->name = name;
        this->age = age;
        this->gpa = gpa;
    }
};

class Car {
    public:
        std::string make;
        std::string model;
        int year;
        std::string color;

    Car(std::string make, std::string model, int year, std::string color){
        this->make = make;
        this->model = model;
        this->year = year;
        this->color = color;
    }
};

int main() {
    Human human1;
    // assing the values to the attributes manually
    human1.name = "Enrique";
    human1.occupation = "Scientist";
    human1.age = 23;

    std::cout << human1.name << std::endl;
    std::cout << human1.occupation << std::endl;
    std::cout << human1.age << std::endl;

    human1.eat();
    human1.drink();
    human1.sleep();

    std::cout << "--- --- --- --- ---" << std::endl;
    // Using a CONSTRUCTOR

    Student student1("Enrique", 23, 4.0);

    std::cout << student1.name << std::endl;
    std::cout << student1.age << std::endl;
    std::cout << student1.gpa << std::endl;

    std::cout << "--- --- --- --- ---" << std::endl;

    Car car1("Tesla","Cybertruck",2018,"silver");
    std::cout << car1.make << std::endl;
    std::cout << car1.model << std::endl;
    std::cout << car1.year << std::endl;
    std::cout << car1.color << std::endl;

    return 0;
}