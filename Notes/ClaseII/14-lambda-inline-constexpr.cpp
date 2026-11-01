#include <iostream>

// `inline` -> En C++ (moderno) su función semántica más importante consiste en permitir ciertas definiciones idénticas en múltiples unidades de traducción, sujetas a las reglas de la ODR (One Definition Rule)

// ODR ---> pilar de C++ para evitar ambiguedades asegurando que cada entidad del programa tenga una estructura clara y un único punto de origen para el enlazador (linker)

inline int square(int x){
    return x*x;
}
// `inline` no garantiza que el compilador elimine la llamada

constexpr int factorial(int n){
    int result = 1;

    for(int i=2; i <=n; ++i){
        result *= i;
    }
    return result;
}

int factorial_recursivo(int n){
    if(n <= 1) {
        return 1;
    }
    return n * factorial_recursivo(n-1);
}

int main(){
    int n;
    std::cout << "Number(n): ";
    std::cin >> n;

    int value = factorial(n);

    std::cout << "Factorial Iterativo -> " << value << std::endl;

    // ==== Funciones lambda ====
    /*  General Syntax

        [captures](parameters) -> return_type {
            // function body
        }
    */

    auto square = [](int x) {
        return x * x;
    };
    int result = square(5);

    std::cout << "square -> " << result << std::endl;

    // CAPTURAS POR VALOR
    int factor = 10;

    auto multiply = [factor](int x) {
        return x * factor;
    };

    factor = 20;
    // lambda captura el valor original de `factor`
    std::cout << multiply(3) << std::endl; // 30

    // --- CAPTURAS POR REFERENCIA ---
    int factor2 = 10;

    auto multiply2 = [&factor2](int x){
        return x * factor2;
    };

    factor2 = 20;

    // Ahora el lambda accede al objeto original
    std::cout << multiply2(3) << std::endl; // 60

    // --- CAPTURAS GENERALES ---
    int a = 10;
    int b = 20;

    /*
        `[=]` -> captura implícitamente por copia las variables locales utilizadas que corresponda capturar
        `[&]` -> captura implícitamente por referencia.
    */

    auto f = [=](){
        return a + b;
    };

    auto g = [&](){
        return a + b;
    };

    a = 100;
    b = 200;

    std::cout << "f() -> " << f() << std::endl;
    std::cout << "g() -> " << g() << std::endl;

    // ---- LAMBDAS GENÉRICAS ----
    auto add = [](auto a, auto b){
        return a + b;
    };

    std::cout << "Generic lambda (int) -> " << add(10, 20) << std::endl;
    std::cout << "Generic lambda (float) -> " << add(2.5, 3.5) << std::endl;

    return 0;
}