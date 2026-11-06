#include <iostream>

// T** -- puntero a puntero
void redirect(int** ptr, int* target){
    *ptr = target;
}

// T*& -- referencia a puntero
void redirect(int*& ptr, int* target){
    ptr = target;
}

int main(){
    int a = 10;
    int b = 20;
    
    int* p = &a;

    redirect(&p, &b);

    std::cout << *p << '\n'; // 20

    // === === === === === === === === ===

    int m = 10;
    int n = 20;

    int* puntero = &m;

    redirect(puntero, &n);

    std::cout << *puntero << '\n'; // 20
    // `int*&` significa referencia a un objeto de tipo int*
    // No necesitamos utilizar `&p` al llamar a la función, porque el parámetro ya es una referencia

    return 0;
}