// Un alias proporciona otro nombre para el mimso namespace

#include <iostream>

namespace company::simulation::geometry {
    struct Point {
        double x;
        double y;
    };

    void write(std::ostream& os, const Point& point){
        os << '(' << point.x << ", " << point.y << ")\n";
    }
}

// ALIAS en ámbito de namespace.
namespace geo = company::simulation::geometry;

// Reabrimos el namespace original (Recordamos que no crea un nuevo namespace, solo lo expande)
namespace company::simulation::geometry {
    constexpr int dimensions = 2;
}

int main(){
    geo::Point point{3.0, 4.0};

    geo::write(std::cout, point);

    // El alias también permite acceder a declaraciones añadidas después
    std::cout << geo::dimensions << '\n';

    // ALIAS LOCAL
    namespace local_geo = company::simulation::geometry;

    local_geo::write(std::cout, point);

    // geo y local_geo designan el mismo namespace.
}
/*  Observación

    No es válido reabrir el alias:

    namespace geo { ... }

    Para añadir declaraciones DEBES ABRIR EL namespace ORIGINAL.
*/