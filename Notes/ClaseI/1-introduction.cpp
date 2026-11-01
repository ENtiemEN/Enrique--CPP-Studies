#include <iostream>
#include <iomanip>  // std::boolalpha, std::setprecision

/* CLASE 1 - INTRODUCCIÓN A C++17
    
    1. Estructura básica del programa
    2. Entrada y salida estándar
    3. Variables y tipado estático
    4. Tipos de datos fundamentales
    5. Constantes: const y constexpr
    6. Conversiones implícitas y explícitas
    7. Problemas con signed y unsigned
*/

// 1. ESTRUCTURA BÁSICA DE UN PROGRAMA

/*
    #include <iostream>
        Directiva del preprocesador que incluye declaraciones
        necesarias para utilizar los flujos estándar.

    int main()
        Función de entrada de un programa alojado (hosted).

    return 0
        Indica terminación exitosa del programa.

    No utilizamos 'using namespace std;' para evitar
    introducir todos los nombres de std en el ámbito global.
*/

int main() {
    // 2. ENTRADA Y SALIDA ESTÁNDAR

    /*
        std::cout -> flujo estándar de salida.
        std::cin  -> flujo estándar de entrada.

        << -> operador de inserción en el flujo.
        >> -> operador de extracción del flujo.

        '\n'      -> salto de línea.
        std::endl -> salto de línea + flush del flujo.
    */

    std::cout << "Hello, C++17!\n";

    int number;

    std::cout << "Enter a number: ";
    std::cin >> number;

    std::cout << "Number entered: " << number << '\n';

    // 3. VARIABLES Y TIPADO ESTÁTICO

    /*
        C++ es un lenguaje de tipado estático:
        cada expresión tiene un tipo determinado en compilación.

        Declaración:
            int x;

        Inicialización:
            int x = 10;   // copy initialization
            int y(20);    // direct initialization
            int z{30};    // list initialization

        Las llaves {} ayudan a prevenir conversiones
        de estrechamiento (narrowing conversions).
    */

    int x = 10;
    double y{3.1415926535};
    bool active{true};
    char letter{'A'};

    std::cout << "\n--- Variables ---\n";

    std::cout << "x: " << x << '\n';
    std::cout << "y: " << std::setprecision(12) << y << '\n';
    std::cout << "active: " << std::boolalpha << active << '\n';
    std::cout << "letter: " << letter << '\n';

    // El tipo de x sigue siendo int.
    x = 3.75;  // double -> int: descarta la parte decimal

    std::cout << "x after conversion: " << x << '\n';

    // int invalid{3.75}; // ERROR: narrowing conversion


    // 4. TIPOS FUNDAMENTALES Y sizeof

    /*
        TIPO                 TAMAÑO HABITUAL (MinGW GCC x64)
        ---------------------------------------------------
        bool                 1 byte
        char                 1 byte
        short                2 bytes
        int                  4 bytes
        long                 4 bytes (Windows x64)
        long long            8 bytes
        float                4 bytes
        double               8 bytes
        long double          Depende de la implementación

        Los tamaños no son universales.

        sizeof(T) devuelve el tamaño de T en bytes.
        En C++, sizeof(char) == 1 por definición.
    */

    std::cout << "\n--- Fundamental Types ---\n";

    std::cout << "bool:        " << sizeof(bool) << '\n';
    std::cout << "char:        " << sizeof(char) << '\n';
    std::cout << "short:       " << sizeof(short) << '\n';
    std::cout << "int:         " << sizeof(int) << '\n';
    std::cout << "long:        " << sizeof(long) << '\n';
    std::cout << "long long:   " << sizeof(long long) << '\n';
    std::cout << "float:       " << sizeof(float) << '\n';
    std::cout << "double:      " << sizeof(double) << '\n';
    std::cout << "long double: " << sizeof(long double) << '\n';

    /*
        signed   -> tipo entero con signo.
        unsigned -> tipo entero sin signo.

        unsigned int no representa números negativos.

        También existen:
            void
            std::nullptr_t (de <cstddef>)
    */


    // 5. CONSTANTES: const Y constexpr

    /*
        const:
            Impide modificar el objeto mediante ese nombre.
            No exige evaluación en tiempo de compilación.

        constexpr:
            Exige una inicialización evaluable en
            tiempo de compilación para una variable.
    */

    const double pi = 3.141592653589793;

    constexpr int max_size = 100;
    constexpr int total_size = max_size * 2;

    std::cout << "\n--- Constants ---\n";

    std::cout << "pi: " << pi << '\n';
    std::cout << "max_size: " << max_size << '\n';
    std::cout << "total_size: " << total_size << '\n';

    // max_size = 200; // ERROR: no se puede modificar

    // Ejemplo de const conocido en ejecución:
    const int runtime_value = number;

    std::cout << "runtime_value: " << runtime_value << '\n';

    // 6. CONVERSIONES DE TIPOS

    /*
        CONVERSIÓN IMPLÍCITA:
            El compilador realiza la conversión automáticamente.

        CONVERSIÓN EXPLÍCITA:
            El programador solicita la conversión.

        static_cast<T>(expression)
            Realiza una conversión explícita permitida
            por las reglas del lenguaje.
    */

    double decimal = 9.8;

    int implicit_result = decimal;
    int explicit_result = static_cast<int>(decimal);

    std::cout << "\n--- Type Conversions ---\n";

    std::cout << "Original: " << decimal << '\n';
    std::cout << "Implicit: " << implicit_result << '\n';
    std::cout << "Explicit: " << explicit_result << '\n';

    /*
        En conversiones floating-point -> integer:
        la parte fraccionaria se descarta hacia cero,
        siempre que el valor truncado sea representable.

        Ejemplo:
            9.8  -> 9
           -9.8  -> -9

        Si el resultado no es representable, el
        comportamiento es indefinido.
    */

    // 7. PROBLEMAS CON signed Y unsigned

    /*
        Cuidado con las usual arithmetic conversions.

        En una operación entre int y unsigned int
        de igual rango, int se convierte a unsigned int.

        Ejemplo:
            -2 -> valor unsigned grande (módulo 2^N)

        Esto puede producir resultados inesperados.
    */

    int a = -2;
    unsigned int b = 1;

    std::cout << "\n--- Signed vs Unsigned ---\n";

    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';

    std::cout << "a < b: " << (a < b) << '\n';
    std::cout << "a + b: " << (a + b) << '\n';

    /*
        En una implementación con unsigned int de 32 bits:

        -2 convertido a unsigned int = 4294967294

        Entonces:
            a < b -> false
            a + b -> 4294967295

        Evitar mezclar signed y unsigned sin considerar
        las reglas de conversión.
    */

    return 0;
}
