/*  
¿Un HASH es un diccionario? --> NO EXACTAMENTE
Una Hash TABLE es una estructura de datos que permite almacenar y buscar información mediante una función hash.

Puede utilizarse para implementar tanto un diccionario como un conjunto.

ejemplo:
- Hash Set (`std::unordered_set`)
--> Guarda valores únicos, sin asociarlos a otros valores

`unordered_set` -- almacena valores únicos

- Hash Map (`std::unordered_map`)
--> Guarda pares de clave-valor, como un diccionario

`unordered_mal` -- almacena pares clave valor

AMBOS UTILIZAN HASHING INTERNAMENTE

--- 
Observación: `std::set` no utiliza hashing, sino árboles balanceados
*/

/*  Estructuras de C++

`std::set`      --> Conjuntos ordenados
`std::unordered_set`    --> Hash Set
`std::map`      --> Diccionario ordenado
`std::unordered_map`    --> Hash map
*/

#include <iostream>
#include <unordered_set>

int main(){
    std::unordered_set<int> numbers{10,20,30};
    /* Conceptualmente -> 10 20 30 END
    Un `unordered_set` no garantiza el orden de los elementos

    `numbers.begin()` -> devuelve un iterador al primer elemento

    `numbers.end()` -> devuelve un interador a la posición posterior al último elemento OJO: Apunta a la posición donde no hay ningún elemento. (Por eso nunca debes hacer `*numbers.end()`)
    */

    // 1. INSERTAR
    numbers.insert(40);
    numbers.insert(20); // Ya existe: No agrega otra copia.

    std::cout << "Cantidad: " << numbers.size() << '\n'; // 4

    // 2. COMPROBAR EXISTENCIA -- c++17
    if(numbers.count(20) != 0){
        std::cout << "20 existe\n";
    }

    // 3. BUSCAR: devuelve un iterador al elemento encontrado.
    // si no existe, devuelve `numbers.end()`
    const auto it = numbers.find(30);

    if(it != numbers.end()){
        std::cout << "Encontrado " << *it << '\n';
    }

    // 4. ELIMINAR POR VALOR    
    const auto removed = numbers.erase(10);

    std::cout << "Eliminados: " << removed << '\n'; // 1

    // 5. RECORRER
    // El ORDEN de impresión NO ESTÁ GARANTIZADO
    for(const int value : numbers){
        std::cout << value << ' ';
    }
    std::cout << '\n';

    std::cout << "--- --- --- --- --- ---\n";
    // Aclaración
    std::unordered_set<float> prices{11.4, 16.5, 17.8};

    const auto iter = prices.insert(20.0);
    

    std::cout << std::boolalpha << "Insertado (" << iter.second << ")" << '\n';

    std::cout << "Valor insertado: " << *(iter.first) << '\n';

    const auto [iterador, flag] = prices.insert(10.0);

    std::cout << std::boolalpha << "Insertado (" << flag << ")" << '\n';
    
    std::cout << "Valor insertado: " << *iterador << '\n';

    return 0;
}
/*
DIFERENCIA Puntero - Iterador

Puntero -->  Variable que almacena la dirección de memoria de otra variable.

Iterador (Iterator) --> Representa una posición dentro de una estructura de datos o contenedor
*/