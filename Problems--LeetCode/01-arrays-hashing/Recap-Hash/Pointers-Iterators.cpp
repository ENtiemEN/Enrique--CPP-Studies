#include <iostream>
#include <vector>

int main(){
    // ¿Puedo hacer un puntero que apunte a un iterador?
    std::vector<int> numbers{10,20,30};

    auto it = numbers.begin();

    std::cout << "numbers[0]: " << *it << '\n';

    auto* ptr = &it;

    std::cout << **ptr << '\n'; // 10

    std::cout << "--- --- --- --- --- --- --- ---\n";

    // ¿Puedo tener un contenedor de punteros y hacer que un iterador apunte a un puntero?

    int a = 10;
    int b = 20;
    int c = 30;

    // Contenedor de punteros
    std::vector<int*> numbers_ptr{&a,&b,&c};

    // Iterador al primer puntero
    auto iter = numbers_ptr.begin();

    std::cout << "Test *(&c) -> " << *(&c) << '\n';

    std::cout << *iter << '\n'; // &a (como el contendor es un vector hay un orden)

    std::cout << **iter << '\n'; // a

    return 0;
}