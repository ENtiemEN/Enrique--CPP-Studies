// Antes de estudiar `using`, necesitamos comprender cómo encuentra C++ una declaración

#include <iostream>

constexpr int value = 10;

namespace settings{
    constexpr int value = 20;
}

namespace geometry {
    struct Point {
        double x;
        double y;
    };

    double squaredNorm(const Point& point){
        return point.x * point.x + point.y * point.y;
    }
}

namespace first {
    void process(int) {}
}

namespace second {
    void process(int) {}
}

int main(){

    // --> 1. Búsqueda no cualificada y OCULTAMIENTO <--
    
    std::cout << value << '\n'; // 10: variable global

    {
        const int value = 30;

        // La declaración local oculta la global
        std::cout << value << '\n'; // 30

        // Cualificación explícita.
        std::cout << ::value << '\n'; // 10
        std::cout << settings::value << '\n'; // 20
    }

    // la variable del bloque anterior ya no está en ámbito
    std::cout << value << '\n';

    // --> 2. Búsqueda dependiente de argumentos: ADL (Argument-Dependent Lookup, también conocido como Koening lookup) <--

    // Cómo funciona ADL? -> Cuando llamamos a una función sin namespace qualifier (such as `::`), el compilador expande su búsqueda más alla del current scope
    geometry::Point point{3.0, 4.0};

    // Búsqueda cualificada
    std::cout << "Busqueda cualificada: " << geometry::squaredNorm(point) << '\n'; // 25;

    // Búsqueda no cualificada + ADL
    std::cout << "Busqueda no cualificada + ALD: " << squaredNorm(point) << '\n'; // 25

    /*
    El argumento tiene tipo `geometry::Point`

    ADL permite buscar funciones también en los namespaces asociados a los tipos de los argumentos

    Por eso encuentra `geometry::squaredNorm` sin usar `using namespace geometry`
    */

    // --> 3. Ambiguedad <--
    {
        using namespace first;
        using namespace second;

        //process(1); // ERROR: ambas funciones son candidatas iguales

        first::process(1); // 👍
        second::process(1); // 👍
    }
}
/*  Distingue estos conceptos

CONCEPTO        QUÉ SUCEDE
Ocultamiento    Una declaración impide encontrar otra mediante una determinada búsqueda.

Sobrecarga      Varias funciones con el mismo nombre participan en la selección según sus parametros

Ambiguedad      La búsqueda o selección no permite determinar una única opción válida

ADL             La búsqueda considera namespaces asociados a los argumentos

*/