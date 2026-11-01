
#include <iostream>

/* CLASE 4 - SCOPE, STORAGE DURATION & LINKAGE (C++17)

    1. Ámbito global (namespace scope)
    2. Ámbito local (block scope)
    3. Ocultamiento de variables (shadowing)
    4. Operador de resolución de ámbito (::)
    5. Variables locales static
    6. Duración de almacenamiento
    7. Linkage: external, internal y no linkage

    IMPORTANTE:
        Scope          -> Dónde es visible un nombre.
        Storage duration -> Cuánto tiempo existe un objeto.
        Linkage        -> Si declaraciones en distintos
                          ámbitos pueden referirse a la
                          misma entidad.
*/

// 1. ÁMBITO GLOBAL (NAMESPACE SCOPE)

/*
    Los nombres declarados fuera de funciones y clases
    pertenecen al ámbito del namespace correspondiente.

    En este caso, al namespace global.

    ::variable -> permite acceder a un nombre del
                  namespace global.
*/

int global_value = 100;


// 2. FUNCIONES PARA DEMOSTRAR static

void counter() {

    /*
        static local:
            - Ámbito local a la función.
            - Duración de almacenamiento estática.
            - Se inicializa una sola vez.
            - Conserva su valor entre llamadas.
    */

    static int count = 0;

    ++count;

    std::cout << "Static counter: " << count << '\n';
}


void counter2() {

    /*
        Variable local automática:
            - Se inicializa en cada llamada.
            - Su duración de almacenamiento es automática.
            - No conserva su valor entre llamadas.
    */

    int count = 0;

    ++count;

    std::cout << "Automatic counter: " << count << '\n';
}


// 3. INTERNAL LINKAGE

/*
    En namespace scope, static proporciona vinculación
    interna (internal linkage).

    Esto significa que el nombre de la entidad está
    vinculado únicamente dentro de esta unidad
    de traducción.

    En C++ moderno suele preferirse un namespace anónimo
    para entidades privadas de un archivo.
*/

static int internal_value = 50;

int main() {
    // 4. ÁMBITO LOCAL (BLOCK SCOPE)

    /*
        Una variable declarada en un bloque {}
        tiene ámbito de bloque.

        Su nombre solamente puede utilizarse dentro
        de su ámbito, desde su punto de declaración,
        salvo reglas especiales de búsqueda de nombres.
    */

    int x = 10;

    std::cout << "--- Local Scope ---\n";
    std::cout << "Outer x: " << x << '\n';

    {
        int y = 20;

        std::cout << "Inner x: " << x << '\n';
        std::cout << "Inner y: " << y << '\n';
    }

    // std::cout << y; // ERROR: y fuera de su ámbito.

    // 5. SHADOWING (OCULTAMIENTO DE VARIABLES)

    /*
        Un nombre declarado en un ámbito interno
        puede ocultar otro nombre del ámbito externo.

        Esto se conoce como shadowing.

        El objeto externo continúa existiendo;
        simplemente queda oculto para la búsqueda
        habitual de nombres.
    */

    int value = 100;

    std::cout << "\n--- Shadowing ---\n";

    std::cout << "Outer value: " << value << '\n';

    {
        int value = 200;

        std::cout << "Inner value: " << value << '\n';

        value = 300;
    }

    std::cout << "Outer value again: " << value << '\n';


    // ========================================================
    // 6. SCOPE RESOLUTION OPERATOR (::)
    // ========================================================

    /*
        El operador :: permite realizar búsquedas
        de nombres en un ámbito específico.

        ::global_value -> variable del namespace global.

        Sin ::, una variable local con el mismo nombre
        puede ocultar la variable global.
    */

    int global_value = 999;

    std::cout << "\n--- Scope Resolution ---\n";

    std::cout << "Local global_value: "
              << global_value << '\n';

    std::cout << "Global global_value: "
              << ::global_value << '\n';

    ::global_value = 500;

    std::cout << "Modified global value: "
              << ::global_value << '\n';

    // 7. VARIABLES LOCALES static

    /*
        Una variable local static conserva su estado
        durante toda la ejecución del programa.

        En cambio, una variable automática local
        se crea nuevamente en cada llamada.
    */

    std::cout << "\n--- Static Local Variables ---\n";

    counter();  // 1
    counter();  // 2
    counter();  // 3

    std::cout << '\n';

    counter2(); // 1
    counter2(); // 1
    counter2(); // 1

    // 8. STORAGE DURATION

    /*
        Storage duration = duración de almacenamiento.

        C++17 reconoce cuatro categorías:

        1. Automatic storage duration
            Variables locales normales.

        2. Static storage duration
            Variables globales y locales static.

        3. Thread storage duration
            Variables declaradas thread_local.

        4. Dynamic storage duration
            Objetos creados mediante asignación dinámica.

        No confundir scope con storage duration.
    */

    std::cout << "\n--- Storage Duration ---\n";

    int automatic_variable = 10;
    static int static_variable = 20;

    std::cout << "Automatic: "
              << automatic_variable << '\n';

    std::cout << "Static: "
              << static_variable << '\n';

    /*
        Ejemplo de almacenamiento dinámico:

            int* ptr = new int{30};
            delete ptr;

        Se estudiará posteriormente en memoria dinámica.

        Ejemplo de thread storage duration:

            thread_local int thread_counter = 0;

        Cada hilo tiene su propia instancia.
    */

    // 9. LINKAGE

    /*
        LINKAGE:
            Determina si declaraciones de un mismo nombre
            pueden referirse a la misma entidad.

        External linkage:
            El nombre puede referirse a la misma entidad
            desde distintas unidades de traducción.

        Internal linkage:
            El nombre queda asociado a una entidad
            dentro de una sola unidad de traducción.

        No linkage:
            El nombre no enlaza con declaraciones
            del mismo nombre en otros ámbitos.

        Ejemplos típicos:

            global_value  -> external linkage
            internal_value -> internal linkage
            x             -> no linkage
    */

    std::cout << "\n--- Linkage ---\n";

    std::cout << "Internal value: "
              << internal_value << '\n';

    std::cout << "Global value: "
              << ::global_value << '\n';

    return 0;
}
