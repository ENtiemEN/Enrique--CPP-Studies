/*
    En C, `NULL` es una macro que representa una constante de puntero nulo.
    
    En C++, (históricamente) puede definirse como `0`, `0L` u otra expresión válida de constante de puntero nulo

    ---

    El problema es que `NULL` no posee un tipo de puntero propio.
    C++11 introdujo `nullptr` para resolver esto
*/
#include <iostream>

#include <type_traits> // std::is_same_v
#include <cstddef> // std::nullptr_t

void print(int x){
    std::cout << "Integer: " << x << '\n';
}

void print(int* ptr){
    std::cout << "Pointer\n";
}

void process(int*){
    std::cout << "Pointer overload\n";
}

void process(std::nullptr_t){
    std::cout << "Null pointer overload\n";
}

int main(){
    print(0);   // `print(int)`
    //print(NULL); // puede llamar a `print(int)` o producir ambiguedad. En este caso Error: llamada ambigua en la compilación
    
    // `nullptr` es un literal cuyo tipo es `std::nullptr_t`
    print(nullptr); // print(int*)`

    int* p = nullptr;
    double* q = nullptr;

    static_assert(
        std::is_same_v<decltype(nullptr), std::nullptr_t>
    ); // -> true | compila (V)
    // Ejemplo No compila (X)
    //static_assert(std::is_same_v<decltype(nullptr),int*>);

    std::cout << std::boolalpha;
    std::cout << (p == nullptr) << '\n';
    std::cout << (q == nullptr) << '\n';

    // === === === === === === === ===
    int x = 10;

    process(&x); // Pointer overload
    process(nullptr); // Null pointer overload

    return 0;
}

/*  Propiedades:

    - Se convierte implícitamente a cualquier tipo de puntero a objeto o función.
    - No se convierte implícitamente a `int`
    - Representa un valor de puntero nulo
    - No puede desreferenciarse

    int* p = nullptr;

    *p = 10 // UNDEFINED BEHAVIOR
*/