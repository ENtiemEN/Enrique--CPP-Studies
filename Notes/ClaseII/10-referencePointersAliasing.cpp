#include <iostream>

void increment(int* ptr){
    if(ptr != nullptr){
        ++(*ptr);
    }
}

int main() {
    int a = 10;

    int& ref = a;
    int* ptr = &a;

    /*
        `ref` es una referencia a `a`
        `ptr` contiene la direcci´n de memoria de `a`
        `*ptr` permite acceder al objeto apuntado
    */

    std::cout << *ptr << std::endl;

    std::cout << "\n--- --- --- ---" << std::endl;

    int x = 10;
    int *y = nullptr;

    int* ptr_x = &x;

    increment(&x);
    increment(y);

    std::cout << x << std::endl;
    std::cout << y << std::endl;

    increment(ptr_x);

    std::cout << x << std::endl;

    return 0;
}