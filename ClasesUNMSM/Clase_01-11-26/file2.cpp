#include <iostream>

void increment_byvalue(int x){ // -> 4 bytes
    x++;
} // Se muere después

void increment_byrefence(int& x){
    x++;
}

int main(){
    int a = 3;
    int& ref = a;
    int b = a;

    std::cout << a << std::endl;
    std::cout << ref << std::endl;
    std::cout << b << std::endl;

    std::cout << &a << std::endl;
    std::cout << &ref << std::endl;
    std::cout << &b << std::endl;

    std::cout << "\n--- --- --- ---" << std::endl;

    int n = 10; // -> 4
    //sizeof(n) -> 4

    increment_byvalue(n);

    std::cout << n << std::endl;

    increment_byrefence(n);

    std::cout << n << std::endl;

    return 0;
}