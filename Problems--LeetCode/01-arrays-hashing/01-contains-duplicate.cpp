/*  Problema:
Dado un `std::vector<int>` devuelve:
- `true` si algún valor aparece al menos dos veces
- `false` si todos los valores son distintos

Entrada	Resultado	Motivo

Entrada	        Resultado	Motivo
{1, 2, 3, 1}    true        Se repite 1.
{1, 2, 3, 4}    false	    Todos son distintos.
{5, 5}	        true	    Se repite 5.
{7}	            false	    Un solo elemento no puede repetirse.
{}	            false	    No hay elementos repetidos.

Buscamos si existen indices distintos tales que:
\exists i < j : values[i] = values[j]
*/

#include <vector>
#include <iostream>

#include <unordered_set>

/*
T(n) = O(n^2)
S_aux(n) = O(1)
*/
bool containsDuplicateBruteForce(const std::vector<int>& values){
    if(values.size() < 2){
        return false;
    }

    for(std::size_t i=0; i < values.size() - 1; i++){
        for(std::size_t j=i+1; j < values.size(); j++){
            if(values[i] == values[j]){
                return true;
            }
        }
    }
    return false;
}

/*
Idea de Solución

Número actual   Número que ya vimos
1                   
2               1
3               12
1               123

Encontramos el duplicado al final. Para implementar eso usaremos `std::unordered_set` (Contenedor de C++ que almacena ELEMENTOS ÚNICOS)

`.insert()` -> Devuelve un objeto de tipo `std::pair<iterator, bool>`
---
`std::pair` tipo de dato que permite almacenar dos valores juntos.
EJEMPLO:
`std::pair<int, bool> result{100, true};`

Tenemos un único objeto llamado `result`, pero dentro contiene:

`result.first` -> 100
`result.second` -> true
*/
bool containsDuplicate(const std::vector<int>& values){
    
    std::unordered_set<int> seen;

    for(const int value : values){
        // guardamos en `const auto result` para saver si la inserción tuvo éxito
        const auto result = seen.insert(value); // `std::pair<std::unordered_set<int>::iterator , bool>`

        /*
        `insert()` devuelve un `pair` con información sobre la inserción:
        `std::pair<iterator, bool>`

        `.first` -> iterador que apunta al elemento insertado
        `.second` -> booleano indica si la inserción fue exitosa
        */

        if (!result.second){
            return true;
        }
    }

    return false;
}
/*  Análisis:
Tiempo O(n^2)
Espacio O(n)
*/

int main(){

    const std::vector<int> repeated{1,2,3,1};
    const std::vector<int> unique{1,2,3,4};
    const std::vector<int> empty{};

    std::cout << std::boolalpha;

    std::cout << "Brute Force:\n";
    std::cout << containsDuplicateBruteForce(repeated) << '\n';
    std::cout << containsDuplicateBruteForce(unique) << '\n';
    std::cout << containsDuplicateBruteForce(empty) << '\n';

    std::cout << "Unordered Set:\n";

    std::cout << containsDuplicate(repeated) << '\n';
    std::cout << containsDuplicate(unique) << '\n';
    std::cout << containsDuplicate(empty) << '\n';

    return 0;
}