/*
1. Storage -> región de memoria disponible para alojar objetos.

2. Storage duration -> periodo durante el cual existe ese almacenamiento.

3. Object lifetime -> periodo durante el cual un objeto está vivo y puede utilizarse conforme a las reglas de su tipo.

C++17 distingue 4 categorías

CATEGORÍA   DESCRIPCIÓN
Automatic   Almacenamiento asociado normalmente a un bloque o llamada de función

Static      Almacenamiento disponible durante la ejecución del programa

Thread      Almacenamiento separado para cada hilo

Dynamic     Almacenamiento administrado mediante mecanismos de asignación dinámica

MODELO CONCEPTUAL

Code / Text (código ejecutable)
Static Storage (Variables globales y static)
Heap / Dynamic allocations (Almacenamiento solicitado dinámicamente)
Stack (Frames de llamadas y variables automáticas habituales)
*/
#include <iostream>
#include <cstddef>

struct Tracer{
    Tracer(){
        std::cout << "Constructed\n";
    }

    ~Tracer(){
        std::cout << "Destroyed\n";
    }
};

void example(){
    Tracer a;

    {
        Tracer b;
    } // b is destroyed here
} // a is destroyed here

// Static storage duration
// Zero-initialized before main()
int globalCounter;

void inspect(){
    // Automatic storage duration
    int localCounter = 0;

    // Static storage duration.
    // Initialized only once
    static int persistentCounter = 0;

    ++localCounter;
    ++persistentCounter;

    std::cout << "Local: " << localCounter << '\n';

    std::cout << "Static: " << persistentCounter << '\n';
}

void recursive(int depth){
    int local = depth;

    std::cout << "Depth: " << depth << " | Address:" << &local << '\n';

    if(depth > 0){
        recursive(depth - 1);
    }
}

// REFERENCIAS COLGANTES ('dangling references')
int& invalidReference(){
    int x = 10;
    return x; // Reference o an automatic local object.
} // cuando termina la función, finaliza el tiempo de vida de `x`. La referencia devuelta queda colgante.

// --> ALIGNMENT <--
struct Data{
    char c;
    int x;
    double y;
};

// --> ALMACENAMIENTO DINÁMICO <--
// Un objeto dinámico puede continuar existiendo después de que termina la función donde fue creado

int* createValue(){
    return new int{42};
}

int main(){
    inspect();
    inspect();
    inspect();

    // Local: 1,1,1
    // Static: 1,2,3
    
    std::cout << "\n--- --- --- --- --- ---\n";

    recursive(3);

    std::cout << "\n--- --- --- --- --- ---\n";

    example();

    std::cout << "\n--- --- --- --- --- ---\n";

    /*
    `sizeof(T)` -> tamaño de `T` en bytes

    `alignof(T)` -> alineación requerida para objetos de tipo `T`, expresada en bytes

    ---

    Un `struct` puede contener 'padding' para ssatisfacer restricciones de alineación.

    e.g. `char` - 1 byte, `int` - 4 bytes, `double` - 8 bytes

    Distribución de `Data` (ilustrativo - 16 bytes)

    C P P P X X X X Y Y Y Y Y Y Y Y
    C - char
    P - padding
    X - int
    Y - double

    Esta es una distribución habitual, dependiente de ABI y el compilador. Cada celda representa un byte

    i.e. NO debes asumir que `sizeof(Data)` es igual a la suma de los tamaños de sus miembros.
    */

    // `alignof(Data) = max(e1,...,en)`
    std::cout << "sizeof(Data) -> " << sizeof(Data) << '\n';
    std::cout << "alignof(Data) -> " << alignof(Data) << '\n';

    std::cout << "alignof(char) -> " << alignof(char) << '\n';
    std::cout << "alignof(int) -> " << alignof(int) << '\n';
    std::cout << "alignof(double) -> " << alignof(double) << '\n';

    std::cout << "\n--- --- --- --- --- ---\n";

    int* p = createValue(); // `p` es una variable local con duración automática que almacena la dirección de ese objeto

    std::cout << *p << '\n';

    delete p;
    p = nullptr;

    return 0;
}