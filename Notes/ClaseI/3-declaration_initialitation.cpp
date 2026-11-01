
#include <iostream>

/* CLASE 3 - DECLARACIÓN E INICIALIZACIÓN EN C++17

    1. Declaración y definición
    2. Formas de inicialización
    3. Variables no inicializadas
    4. Inicialización vs asignación
    5. Operadores de incremento y decremento
    6. Ámbito y ocultamiento de variables
*/

// 1. DECLARACIÓN Y DEFINICIÓN

/*
    DECLARACIÓN:
        Introduce un nombre y sus propiedades en un ámbito.

    DEFINICIÓN:
        Es una declaración que define la entidad.

    Ejemplo:

        extern int global_value; // Solo declaración
        int global_value = 10;   // Definición

    Toda definición es una declaración, pero
    no toda declaración es una definición.
*/

extern int global_value;

int main() {
    // 2. FORMAS DE INICIALIZACIÓN

    /*
        Copy-initialization:
            int a = 10;

        Direct-initialization:
            int b(10);

        Direct-list-initialization:
            int c{10};

        Copy-list-initialization:
            int d = {10};

        Value-initialization:
            int e{};

        Para un int, e{} produce el valor 0.
    */

    int a = 10;
    int b(10);
    int c{10};
    int d = {10};
    int e{};

    std::cout << "--- Initialization ---\n";

    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';
    std::cout << "c: " << c << '\n';
    std::cout << "d: " << d << '\n';
    std::cout << "e: " << e << '\n';

    // 3. NARROWING CONVERSIONS

    /*
        La inicialización con llaves {} rechaza
        ciertas conversiones de estrechamiento.

        Por ejemplo:
            double -> int

        Las formas con = y () pueden permitirlas.
    */

    int x = 3.75;    // Permitido: x = 3
    int y(3.75);     // Permitido: y = 3

    // int z{3.75};     // ERROR: narrowing
    // int w = {3.75};  // ERROR: narrowing

    std::cout << "\n--- Narrowing ---\n";

    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';

    // 4. VARIABLES NO INICIALIZADAS

    /*
        Una variable automática de tipo int declarada
        sin inicializador tiene un valor indeterminado.

        Leer ese valor puede provocar comportamiento
        indefinido en C++17.

        RECOMENDACIÓN:
            Inicializar siempre las variables antes
            de utilizar sus valores.
    */

    int uninitialized;  // No leer antes de asignar.

    uninitialized = 50; // Ahora tiene un valor válido.

    int initialized{};  // Inicializado a 0.

    std::cout << "\n--- Initialization Safety ---\n";

    std::cout << "uninitialized after assignment: "
              << uninitialized << '\n';

    std::cout << "initialized: " << initialized << '\n';

    // 5. INICIALIZACIÓN VS ASIGNACIÓN

    /*
        INICIALIZACIÓN:
            Proporciona el valor inicial de un objeto.

            int n = 10;

        ASIGNACIÓN:
            Modifica un objeto que ya existe.

            n = 20;

        En tipos de clase, la diferencia puede afectar
        a los constructores y operadores utilizados.
    */

    int n = 10;  // Inicialización.

    n = 20;      // Asignación.

    std::cout << "\n--- Assignment ---\n";

    std::cout << "n: " << n << '\n';

    // 6. OPERADORES DE INCREMENTO Y DECREMENTO

    /*
        PREINCREMENTO:
            ++n

        Incrementa el objeto y devuelve una expresión
        lvalue referida al objeto incrementado.

        POSTINCREMENTO:
            n++

        Incrementa el objeto, pero produce el valor
        anterior al incremento.

        Para los enteros, la diferencia se observa
        al utilizar el resultado de la expresión.
    */

    int counter = 5;

    int before = counter++;  // before = 5, counter = 6
    int after = ++counter;   // after = 7, counter = 7

    std::cout << "\n--- Increment Operators ---\n";

    std::cout << "before: " << before << '\n';
    std::cout << "after: " << after << '\n';
    std::cout << "counter: " << counter << '\n';

    /*
        DECREMENTO:
            --counter -> predecremento
            counter-- -> postdecremento
    */

    int p = --counter;  // counter = 6, p = 6
    int q = counter--;  // q = 6, counter = 5

    std::cout << "p: " << p << '\n';
    std::cout << "q: " << q << '\n';
    std::cout << "counter: " << counter << '\n';

    // 7. ÁMBITO Y OCULTAMIENTO DE VARIABLES

    /*
        Una variable declarada dentro de un bloque {}
        pertenece a ese ámbito.

        Un ámbito interno puede declarar una variable
        con el mismo nombre que otra externa.

        La variable interna oculta a la externa
        mientras estamos dentro de ese bloque.
    */

    int value = 100;

    std::cout << "\n--- Variable Scope ---\n";

    std::cout << "Outer value: " << value << '\n';

    {
        int value = 200;

        std::cout << "Inner value: " << value << '\n';
    }

    std::cout << "Outer value again: " << value << '\n';

    // 8. VARIABLE GLOBAL

    std::cout << "\n--- Global Variable ---\n";

    std::cout << "global_value: " << global_value << '\n';

    return 0;
}

// DEFINICIÓN DE VARIABLE GLOBAL

int global_value = 42;
