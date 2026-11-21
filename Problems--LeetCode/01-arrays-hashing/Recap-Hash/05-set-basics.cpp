#include <iostream>
#include <set>

void writeSet(std::ostream& os, const std::set<int>& values){
    for(const int value: values){
        os << value << ' ';
    }

    os << '\n';
}

int main(){
    std::set<int> numbers{30,10,20,10};

    // 1. ELEMENTOS ÚNICOS Y ORDENADOS
    writeSet(std::cout, numbers); // 10 20 30

    std::cout << "Cantidad: " << numbers.size() << '\n'; // 3

    // 2. INSERTAR
    const auto [position, inserted] = numbers.insert(25);

    // position -> std::set<int>::iterator
    // inserted -> bool
    std::cout << std::boolalpha;
    std::cout << "Insertado: " << inserted << '\n';

    std::cout << "Elemento: " << *position << '\n';

    const auto result = numbers.insert(20);

    std::cout << "Insertado: " << result.second << '\n'; // false
    std::cout << "Existente: " << *result.first << '\n'; // 20

    writeSet(std::cout, numbers); // 10 20 25 30

    std::cout << "--- --- --- --- --- --- ---\n";
    // 3. BUSCAR
    const auto it = numbers.find(25);

    if(it != numbers.end()){
        std::cout << "Encontrado: " << *it << '\n';
    }

    // 4. COMPROBAR EXISTENCIA -- C++17
    if(numbers.count(20) != 0){
        std::cout << "20 existe\n";
    }

    // 5. ELIMINAR POR VALOR
    const auto removed = numbers.erase(10);

    std::cout << "Eliminados: " << removed << '\n'; // 1
    writeSet(std::cout, numbers); // 20 25 30

    std::cout << "--- --- --- --- --- --- ---\n";

    // 6. MÍNIMO Y MÁXIMO CON ORDEN ASCENDENTE
    // Solo podemos desreferenciar si el conjunto no está vacío
    if(!numbers.empty()){
        std::cout << "Mínimo: " << *numbers.begin() << '\n';
        std::cout << "Máximo: " << *numbers.rbegin() << '\n';
    }
    
    // `rbegin()` devuelve un iterador inverso. Al incrementarlo, se avanza en sentido contrario al recorrido normal.

    // 7. RECORRIDO INVERSO
    for(auto rit = numbers.rbegin(); rit != numbers.rend(); ++rit){
        std::cout << *rit << ' ';
    }
    std::cout << '\n'; // 30 25 20

    std::cout << "--- --- --- --- --- --- ---\n";
    // 8. ELEGIR ORDEN DESCENDENTE
    const std::set<int, std::greater<int>> descending{
        30, 10, 20, 10
    };

    for(const int value : descending){
        std::cout << value << ' ';
    }

    std::cout << '\n'; // 30 20 10

    return 0;
}