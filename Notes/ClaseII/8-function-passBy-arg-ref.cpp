/*
    Diferencia entre REFERENCIA y PUNTERO
    
    Característica      Referencia(`int&`)  Puntero(`int*`)

    Representa          Un alias            Una variable que almacena una dirección

    Acceso al valor     `ref`               `*ptr`
    Obtener dirección   `&ref`              `ptr`
    Puede de objeto     NO                  Sí
    asociado

    Puede ser nulo      No                  Sí
*/
#include <iostream>

void increment_byValue(int x){
    ++x;
}

void increment_byReference(int& x){
    ++x;
}

int main(){
    int a = 10;
    int b = 10;

    increment_byValue(a);
    increment_byReference(b);

    std::cout << a << std::endl;
    std::cout << b << std::endl;

    // En C++ una referencia (`int&`) no es una posición de memoria que se imprime automáticamente, sino un alias (otro nombre) de una variable existente
    int& ref = a; // `ref` y `a` representan el mismo objeto en memoria
    ref = 20;

    std::cout << ref << std::endl; // 20
    std::cout << a << std::endl; // 20

    std::cout << "Obtengamos la posicion en memoria de la 'referencia' y 'a'" << std::endl;

    std::cout << &ref << std::endl;
    std::cout << &a << std::endl;

    std::cout << "\n--- --- --- ---" << std::endl;

    int x = 10;
    int y = 20;

    int& ref1 = x; // `ref1` y `x` representan el mismo objeto en memoria
    ref1 = y;

    std::cout << x << std::endl; // 20

    ref1 = 30;
    
    std::cout << y << std::endl; // 20
    std::cout << x << std::endl; // 30


    return 0;
}