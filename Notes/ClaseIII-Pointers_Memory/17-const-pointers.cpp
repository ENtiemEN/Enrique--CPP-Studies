#include <iostream>

/*  `const` aplicado a punteros
    
    Declaración          ¿Modificar *p?   ¿Reasignar p?
    ---------------------------------------------------
    int* p               Sí               Sí
    const int* p         No               Sí
    int* const p         Sí               No
    const int* const p   No               No

    Modificar *p cambia el valor del entero apuntado.
    Reasignar p cambia la dirección que guarda el puntero
*/

int main(){
    // 1. `const int*` -- puntero a un entero de solo lectura a través de p
    {
    int a = 10;
    int b = 20;

    const int* p = &a;
    // *p = 30; // Error: no se puede modificar `a` mediante `p`

    a = 15; // Válido: `a` se declaró como int, y sigue siendo modificable.
    std::cout << *p << '\n'; // 15

    p = &b; // Válido: `p` ahora guarda la dirección de b.
    std::cout << *p << '\n'; // 20
    }
    
    // 2. `int* const` -- puntero constante a un entero modificable.
    {
    int a = 10;
    int* const p = &a;

    *p = 30; // Válido: escsribe 30 en `a`
    // p = nullptr // Error -> `p` no puede guardar otra dirección.
    
    std::cout << a << '\n'; // 30
    }

    // 3. `const int* const` -- puntero constante a un entero de solo lectura. Cada `const` restringe una operación distinta.
    {
    int a = 10;
    const int* const p = &a;

    //*p = 20; // Error -> el primer `const` impide escribir mediante p.

    //p = nullptr; // Error -> el segundo `const` impide reasignar p

    std::cout << *p << '\n'; // 10;
    }


    return 0;
}