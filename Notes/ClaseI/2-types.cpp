
#include <iostream>
#include <climits>      // CHAR_BIT
#include <limits>       // std::numeric_limits
#include <typeinfo>     // typeid
#include <type_traits>  // std::is_same_v

/* CLASE 2 - SISTEMA DE TIPOS EN C++17

    1. Tipos fundamentales
    2. Tamaños y representación
    3. Rangos numéricos
    4. Literales y sufijos
    5. Deducción de tipos con auto
    6. Constantes: const y constexpr
    7. Comprobación de tipos en compilación
*/

// Declaración de función constexpr.
//constexpr int square(int x);

// DEFINICIÓN DE FUNCIÓN constexpr

constexpr int square(int x) {
    return x * x;
}

int main() {
    // 1. TIPOS FUNDAMENTALES

    /*
        Tipos fundamentales más utilizados:

        BOOLEANOS:
            bool

        CARACTERES:
            char, signed char, unsigned char
            wchar_t, char16_t, char32_t

        ENTEROS:
            short, int, long, long long
            Versiones signed y unsigned

        PUNTO FLOTANTE:
            float, double, long double

        OTROS:
            void, std::nullptr_t

        IMPORTANTE:
        El tamaño de cada tipo depende de la implementación,
        sujeto a los mínimos establecidos por el estándar.
    */

    bool active = true;
    char letter = 'A';

    int integer = 42;
    unsigned int positive = 100u;

    float decimal_f = 3.14f;
    double decimal_d = 3.14;
    long double decimal_ld = 3.14L;

    std::cout << "--- Fundamental Types ---\n";

    std::cout << "bool: " << active << '\n';
    std::cout << "char: " << letter << '\n';
    std::cout << "int: " << integer << '\n';
    std::cout << "unsigned int: " << positive << '\n';

    std::cout << "float: " << decimal_f << '\n';
    std::cout << "double: " << decimal_d << '\n';
    std::cout << "long double: " << decimal_ld << '\n';

    // 2. TAMAÑOS Y REPRESENTACIÓN

    /*
        sizeof(T):
            Devuelve el tamaño de T en bytes.

        CHAR_BIT:
            Número de bits por byte.

        En arquitecturas comunes:
            CHAR_BIT = 8

        No todos los sistemas utilizan necesariamente
        bytes de 8 bits.
    */

    std::cout << "\n--- Type Sizes ---\n";

    std::cout << "CHAR_BIT: " << CHAR_BIT << '\n';

    std::cout << "char:        " << sizeof(char) << '\n';
    std::cout << "short:       " << sizeof(short) << '\n';
    std::cout << "int:         " << sizeof(int) << '\n';
    std::cout << "long:        " << sizeof(long) << '\n';
    std::cout << "long long:   " << sizeof(long long) << '\n';

    std::cout << "float:       " << sizeof(float) << '\n';
    std::cout << "double:      " << sizeof(double) << '\n';
    std::cout << "long double: " << sizeof(long double) << '\n';

    std::cout << "Bits in int: "
              << sizeof(int) * CHAR_BIT << '\n';


    // 3. RANGOS NUMÉRICOS

    /*
        std::numeric_limits<T>:
            Proporciona propiedades del tipo T.

        Para enteros:
            min() -> valor mínimo representable.
            max() -> valor máximo representable.

        Para flotantes:
            lowest() -> valor finito más negativo.
            min()    -> menor valor positivo normalizado.
            max()    -> mayor valor finito representable.

        epsilon():
            Diferencia entre 1 y el siguiente valor
            representable mayor que 1.
    */

    std::cout << "\n--- Numeric Limits ---\n";

    std::cout << "int min: "
              << std::numeric_limits<int>::min() << '\n';

    std::cout << "int max: "
              << std::numeric_limits<int>::max() << '\n';

    std::cout << "unsigned int max: "
              << std::numeric_limits<unsigned int>::max()
              << '\n';

    std::cout << "double lowest: "
              << std::numeric_limits<double>::lowest()
              << '\n';

    std::cout << "double min: "
              << std::numeric_limits<double>::min()
              << '\n';

    std::cout << "double max: "
              << std::numeric_limits<double>::max()
              << '\n';

    std::cout << "double epsilon: "
              << std::numeric_limits<double>::epsilon()
              << '\n';

    // 4. LITERALES Y SUFIJOS

    /*
        LITERALES ENTEROS:
            10       -> int
            10u      -> unsigned int
            10L      -> long
            10LL     -> long long

        LITERALES FLOTANTES:
            3.14f    -> float
            3.14     -> double
            3.14L    -> long double

        BASES NUMÉRICAS:
            42       -> decimal
            0b101010 -> binario (C++14)
            052      -> octal
            0x2A     -> hexadecimal

        SEPARADORES:
            1'000'000 -> válido desde C++14
    */

    int decimal = 42;
    int binary = 0b101010;
    int hexadecimal = 0x2A;
    int octal = 052;

    int million = 1'000'000;

    std::cout << "\n--- Literals ---\n";

    std::cout << "Decimal: " << decimal << '\n';
    std::cout << "Binary: " << binary << '\n';
    std::cout << "Hexadecimal: " << hexadecimal << '\n';
    std::cout << "Octal: " << octal << '\n';
    std::cout << "Million: " << million << '\n';

    // 5. DEDUCCIÓN DE TIPOS CON auto

    /*
        auto:
            Permite deducir un tipo durante la compilación.

        IMPORTANTE:
            auto NO convierte C++ en un lenguaje
            de tipado dinámico.

        El tipo deducido permanece fijo.

        En declaraciones simples por valor, auto
        normalmente descarta referencias y const
        de nivel superior del inicializador.
    */

    auto a = 10;       // int
    auto b = 3.14;     // double
    auto c = true;     // bool
    auto d = 'A';      // char
    auto e = 3.14f;    // float

    std::cout << "\n--- Type Deduction ---\n";

    /*
        typeid(expression).name():
            Devuelve un nombre de tipo dependiente
            de la implementación.

        No existe garantía sobre su formato.
    */

    std::cout << "Type a: " << typeid(a).name() << '\n';
    std::cout << "Type b: " << typeid(b).name() << '\n';
    std::cout << "Type c: " << typeid(c).name() << '\n';
    std::cout << "Type d: " << typeid(d).name() << '\n';
    std::cout << "Type e: " << typeid(e).name() << '\n';

    auto x = 10;

    x = 3.75;  // Conversión double -> int.

    std::cout << "x: " << x << '\n'; // 3

    /*
        auto requiere un inicializador:

            auto value; // ERROR

        Deducción con llaves:

            auto p{10};      -> int
            auto q = {10};   -> std::initializer_list<int>

        La segunda forma requiere <initializer_list>.
    */


    // 6. const Y constexpr

    /*
        const:
            Impide modificar el objeto mediante ese nombre.
            Puede inicializarse en tiempo de ejecución.

        constexpr:
            Para variables, exige una inicialización
            evaluable como expresión constante.

        Para funciones:
            constexpr permite evaluación en compilación
            cuando se cumplen los requisitos, pero
            no obliga a que todas las llamadas lo sean.
    */

    const int age = 23;

    constexpr int limit = 100;
    constexpr int square_result = square(5);

    int runtime_input = 7;
    const int runtime_constant = runtime_input;

    int runtime_result = square(runtime_input);

    std::cout << "\n--- Constants ---\n";

    std::cout << "age: " << age << '\n';
    std::cout << "limit: " << limit << '\n';
    std::cout << "square(5): " << square_result << '\n';
    std::cout << "runtime_constant: "
              << runtime_constant << '\n';
    std::cout << "runtime_result: " << runtime_result << '\n';

    // 7. COMPROBACIÓN DE TIPOS EN COMPILACIÓN

    /*
        static_assert(condition):
            Comprueba una condición constante
            durante la compilación.

        std::is_same_v<T, U>:
            Indica si T y U son exactamente el mismo tipo.

        Disponible desde C++17.
    */

    static_assert(std::is_same_v<decltype(a), int>);
    static_assert(std::is_same_v<decltype(b), double>);
    static_assert(std::is_same_v<decltype(e), float>);

    static_assert(square_result == 25);

    /*
        decltype(expression):
            Obtiene el tipo de una expresión
            sin evaluarla.

        Ejemplo:
            decltype(a) -> int

        Su comportamiento con referencias y expresiones
        entre paréntesis se estudiará posteriormente.
    */

    std::cout << "\nAll compile-time checks passed.\n";

    return 0;
}



