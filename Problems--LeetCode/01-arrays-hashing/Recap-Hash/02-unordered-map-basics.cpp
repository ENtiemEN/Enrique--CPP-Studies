/*
`std::unordered_map<Key, Value>` almacena asociaciones entre claves ÚNICAS y valores
*/

#include <iostream>
#include <string>
#include <unordered_map>

int main(){
    std::unordered_map<std::string, int> ages{
        {"Enrique", 23},
        {"Diana", 24}
    };

    // 1. INSERTAR UNA ASOCIACIÓN
    auto result = ages.insert({"Milagros", 50});
    /*
    result -> `std::pair<iterator, bool>`
    
    `result.first` -> Iterador al elemento
    `result.second` -> bool: true si se insertó
    */

    std::cout << "1) Clave -> " << result.first->first << '\n';

    std::cout << "2) Valor -> " << result.first->second << '\n';

    std::cout << std::boolalpha << "Insertando Persona: " << result.second << '\n'; // true

    // Clave REPETIDA: `insert()` NO reemplaza el valor existente.
    result = ages.insert({"Enrique", 18});
    

    std::cout << "Insertando Persona: " << result.second << '\n';

    std::cout << "Enrique: " << ages.at("Enrique") << '\n'; // 23

    // 2. INSERTAR o ACTUALIZAR con operator[]

    ages["Mark"] = 24; // clave nueva: crea la asociación
    ages["Diana"] = 18; // clave existente: modifica su valor.

    // 3. ACCEDER SIN INSERTAR
    std::cout << "Mark: " << ages.at("Mark") << '\n';

    // `.at()` -> lanza `std::out_of_range` si la clave no existe

    // 4. BUSCAR
    const auto it = ages.find("Diana");

    if(it != ages.end()){
        std::cout << "Clave: " << it->first << '\n';
        std::cout << "Valor: " << it->second << '\n';
    }

    // 5. COMPROBAR EXISTENCIA - C++17
    if(ages.count("Minerva") != 0){
        std::cout << "Minerva existe";
    }else{
        std::cout << "Minerva no existe\n";
    }

    // 6. ELIMINAR POR CLAVE
    const auto removed = ages.erase("Mark");

    std::cout << "Eliminados: " << removed << '\n'; // 1

    // 7. RECORRER SIN COPIAR LOS ELEMENTOS
    for(const auto& [name, age] : ages){
        std::cout << name << ": " << age << '\n';
    }

    std::cout << "Cantidad: " << ages.size() << '\n'; // 3

    std::cout << "--- --- --- --- --- ---\n";

    // OBSERVACIÓN --> `operator[]`
    std::unordered_map<std::string, int> prices;

    std::cout << prices["Laptop"] << '\n';
    
    std::cout << prices.size() << '\n'; // 1
    std::cout << prices.at("Laptop") << '\n';

    const auto [iter, inserted] = prices.insert({"Iphone", 1200});
    // iter -> `std::unordered_map<std::string, int>::iterator`

    std::cout << std::boolalpha << "Insertado: " << inserted << '\n';


    std::cout << "key: " << (*iter).first << '\n'; // 

    std::cout << "value: " << iter->second << '\n';

    return 0;
}