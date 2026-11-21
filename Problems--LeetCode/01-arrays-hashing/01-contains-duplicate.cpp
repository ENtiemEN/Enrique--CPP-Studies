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
#include <set>

/*  ANALISIS DE ALGORITMOS - Teoría
Big O --> O(f(n)), describe cómo crece el costo de un algoritmo a medida que aumente el tamaño de la entrada.

Se utiliza para analizar dos dimensiones:
Tipo de complejidad     ¿Qué mide?

'Time Complexity'       cómo crece el tiempo de ejecución

'Space Complexity'      cómo crece el espacio de memoria utilizada

e.g.
- 'O(n) temporal' i.e. el trabajo del algoritmo crece linealmente respecto al tamaño de la entrada.
- 'O(n) espacial' i.e. la memoria adicional utilizada crece linealmente respecto al tamaño de la entrada

IMPORTANTE: 
Big O expresa una cota asintótica superior, no necesariamente el tiempo o memoria exactos
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
/*  Análisis del algoritmo
Complejidad temporal:
- O(n^2) -- tiene dos bucles anidados
- En el peor caso, comparas una cantidad cuadrática de pares de elementos

Complejidad espacial auxiliar:
- O(1) -- utilizas únicamente unas pocas variables (i, j), independientemente del tamaño de la entrada

---

Time Complexity: O(n^2)
Auxiliary Space Complexity: O(1)
*/


/*
OTRA de Solución

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
/*  Análisis del algoritmo

Complejidad Temporal:
- O(n) promedio: recorres el vector una vez y cada inserción en `unordered_set` tiene un costo de O(1)
- O(n^2) peor caso: las operaciones de inserción pueden degradarse por colisiones hash.

Complejidad espacial auxiliar:
- O(n): en el peor caso, el `unordered_set` almacena los n elmentos porque todos son distintos.

---
Time Complexity:
- Average: O(n)
- Worst: O(n^2)

Auxiliary Space Complexity: O(n)
*/

bool containsDuplicate_set(const std::vector<int>& values){
    std::set <int> seen;

    for(const int value : values){
        const auto [it, inserted] = seen.insert(value);

        if(!inserted){
            return true;
        }
    }
    
    return false;
}
/*  Análisis del algoritmo
Complejidad temporal:
`std::set` garantiza inserciones de costo O(log(k+1)), donde k es la cantidad de elementos almacenados antes de insertar.

0
1
2
...
n-1

Si lo n valores son distintos
T(n) = O(∑_{k=0}^{n-1} log(k+1)) = O(log(n!))
Donde n! <= n^n
-> log(n!) <= log(n^n)

T(n) = O(nlogn)
i.e T(n) ∈ O(nlogn)

Complejidad espacial auxiliar:
Si todos son distintos, `seen` almacena los n elementos:
S_aux(n) = O(n)
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

    std::cout << "\nUnordered Set:\n";

    std::cout << containsDuplicate(repeated) << '\n';
    std::cout << containsDuplicate(unique) << '\n';
    std::cout << containsDuplicate(empty) << '\n';

    std::cout << "\nOrdered Set:\n";
    std::cout << containsDuplicate_set(repeated) << '\n';
    std::cout << containsDuplicate_set(unique) << '\n';
    std::cout << containsDuplicate_set(empty) << '\n';


    return 0;
}

/*  NOTACIONES ASINTÓTICAS (Asymptotic Notations)

O   Big O       Cota superior asintótica
Ω   Big Omega   Cota inferior asintótica
Θ   Big Theta   Cota ajustada sintética

o   Little O        Cota superior asintótica estricta
ω   Litlle Omega    Cota ingerior asintótica estricta
*/