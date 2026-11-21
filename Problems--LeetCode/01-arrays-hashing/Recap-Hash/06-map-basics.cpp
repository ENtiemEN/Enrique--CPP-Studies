#include <iostream>
#include <map>

using AgeMap = std::map<std::string, int>;

void writeAges(std::ostream& os, const AgeMap& ages){
    for(const auto& [name, age] : ages){
        os << name << ": " << age << '\n';
    }
}

int main(){
    AgeMap ages{
        {"Enrique", 23},
        {"Ana", 25},
        {"Diana", 24}
    };

    // 1. RECORRER EN ORDEN DE CLAVE
    writeAges(std::cout, ages);
    // Ana: 25
    // Diana: 24
    // Enrique: 23

    // 2. INSERTAR
    const auto [position, inserted] = ages.insert({"Luis", 30});

    // position -> AgeMap::iterator
    // inserted -> bool
    std::cout << std::boolalpha;
    std::cout << "Insertado: " << inserted << '\n'; // true
    std::cout << position->first << ": " << position->second << '\n'; // Luis: 30

    // Clave existente: insert() NO reemplaza el valor
    const auto result = ages.insert({"Ana", 99});

    std::cout << "Insertado: " << result.second << '\n'; // false
    
    std::cout << "Ana: " << result.first->second << '\n'; // 25

    std::cout << "--- --- --- --- --- --- ---\n";
    // 3. INSERTAR O ACTUALIZAR CON operator[]
    ages["Pedro"] = 28; // Inserta una clave nueva
    ages["Diana"] = 26; // Modifica el valor existente.

    // Si la clave no existe, [] la inserta con VALOR POR DEFECTO.
    std::cout << "Maria: " << ages["Maria"] << '\n'; // 0

    // 4. ACCEDER SIN INSERTAR
    //std::cout << "Enrique: " << ages["Enrique"] << '\n';
    std::cout << "Enrique: " << ages.at("Enrique") << '\n'; // 23

    // `at()` -> lanza `std::out_of_range` si no existe la clave.
    // ages.at("Desconocido");

    std::cout << "--- --- --- --- --- --- ---\n";
    // 5. BUSCAR Y MODIFICAR EL VALOR

    const auto it = ages.find("Diana");

    if(it != ages.end()){
        it->second = 27; // Permitido: modifica el valor.

        // it->first = "Daniela"; // ERROR -> La clave es const.

        std::cout << it->first << ": " << it->second << '\n';
    }

    // 6. COMPROBAR EXISTENCIA - C++17
    if(ages.count("Luis") != 0){
        std::cout << "Luis existe\n";
    }

    // 7. ELIMINAR POR CLAVE
    const auto removed = ages.erase("Pedro");

    std::cout << "Eliminados: " << removed << '\n'; // 1

    std::cout << "--- --- --- --- --- --- ---\n";
    // 8. INSERTAR O REEMPLAZAR EXPLÍCITAMENTE - C++17
    const auto [anaIt, anaInserted] = ages.insert_or_assign("Ana", 29);

    std::cout << "Insertado? " << anaInserted << '\n';

    std::cout << anaIt->first << ": " << anaIt->second << '\n'; // Ana: 29

    std::cout << "--- --- --- --- --- --- ---\n";
    // 9. RECORRIDO FINAL
    writeAges(std::cout, ages);
    // Ana: 29
    // Diana: 27
    // Enrique: 23
    // Luis: 30
    // Maria: 0

    std::cout << "Cantidad: " << ages.size() << "\n"; // 5

    std::cout << "--- --- --- --- --- --- ---\n";
    // 10. ORDEN DESCENDENTE POR CLAVE
    const std::map<std::string, int, std::greater<std::string>> descending{
        {"Enrique", 23},
        {"Ana", 25},
        {"Diana", 24}
    };

    for(const auto& [name, age] : descending){
        std::cout << name << ": " << age << '\n';
    }
    // Enrique: 23
    // Diana: 24
    // Ana: 25

    return 0;
}