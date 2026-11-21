/*
Una tabla hash utiliza dos pasos
1. Una función hash transforma la clave en un número
2. Ese número se utiliza para elegir un bucket, donde se organiza el elemento

clave    -- valor que buscamos
hash     -- número calculado a partir de la clave
bucket   -- grupo donde se ubican los elementos
colisión -- dos claves diferentes terminan en el mismo bucket

En un `unordered_set`, el propio elemento es la clave.

En un `unordered_map`, se utiliza la parte `first`

Obs: El hash y el índice del bucle son cosas distintas. La biblioteca determina cómo convertir el hash en un índice de bucket
*/

#include <cstddef>
#include <iostream>
#include <unordered_set>

// Recap -> En C++ un struct puede contener: Variables, Funciones, Constructores, OPERADORES SOBRECARGADOS.

/*
En C++ `operator()` permite que un objeto se pueda utilizar como si fuera una función.

`operator()(T)` <--> 'operator()' es el nombre del operador que estamos sobrecargando. | '(T)' parámetro
*/
struct LastDigitHash {
    std::size_t operator()(unsigned int value) const noexcept {
        return value % 10;
    }
};
/*  Ejemplo
`LastDigitHash hashFunction;`
`std::size_t result = hashFunction(123);`

Es equivalente a:
`std::size_t result = hashFunction.operator()(123);` // output -> 3
*/

// UTILIZAMOS `std::size_t` porque las funciones hash de la biblioteca estándar de C++ devuelven ese tipo.
int main(){
    // Tiende dos parámetros de plantilla `std::unordered_set<TipoDeDato, FuncionHash>`
    std::unordered_set<unsigned int, LastDigitHash> numbers{
        12u, 22u, 32u, 15u
    };
    // hash de 12,22,32 -> 2
    // hash de 15 -> 5


    // 1. HASH Y BUCKET DE CADA ELEMENTO

    // `auto` <---> `LastDigitHash`
    const auto hash = numbers.hash_function(); // solicitamos una copia de su objeto hash // `hash(12u)` -- `hash.operator()(12u)`;

    for(const unsigned int value : numbers){
        std::cout << "Valor: " << value << " | Hash : " << hash(value) << " | Bucket : " << numbers.bucket(value) << '\n';
    }

    // 12, 22 y 32 tienen el mismo hash: estarán en el mismo bucket

    // 2. RECORRER LOS ELEMENTOS DE UN BUCKET
    const auto bucketIndex = numbers.bucket(12u);

    std::cout << "\nBucket compartido:\n";

    for(auto it = numbers.begin(bucketIndex);
    it != numbers.end(bucketIndex);
    ++it
    ){
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    std::cout << "--- --- --- --- --- ---\n";
    // 3. UNA COLISIÓN NO IMPIDE ALMACENAR CLAVES DIFERENTES

    std::cout << "Cantidad: " << numbers.size() << '\n'; // 4

    const auto [position, inserted] = numbers.insert(22u);

    std::cout << std::boolalpha;
    std::cout << "22 insertado: " << inserted << '\n'; // false

    std::cout << "Elemento existente: " << *position << '\n';

    std::cout << "--- --- --- --- --- ---\n";
    // 4. FACTOR DE CARGA
    std::cout << "\nElementos: " << numbers.size() << '\n';
    
    std::cout << "Buckets: " << numbers.bucket_count() << '\n';

    std::cout << "Factor de carga: " << numbers.load_factor() << '\n';

    std::cout << "--- --- --- --- --- ---\n";
    // 5. PREPARAR LA TABLA PARA ALMACENAR 100 ELEMENTOS
    numbers.reserve(100);

    std::cout << "\nDespues de reserve(100):\n";
    std::cout << "Elementos: " << numbers.size() << '\n'; // Sigue siendo 4

    std::cout << "Buckets: " << numbers.bucket_count() << '\n';

    std::cout << "Factor de carga: " << numbers.load_factor() << '\n';
    

}
/*  Aclaraciones:

"load factor = cantidad de elementos / cantidad de buckets"

Indica cuántos elementos hay por cada bucket en promedio; no garantiza distribución uniforme.

Cuando necesita más buckets, el contenedor puede realizar un REHASHING: Reorganizar elementos entre los buckets.
e.g.
`numbers.reserve(100);` // -> Prepara suficientes buckets para alojar al menos 100 elementos según el factor máximo de carga. NO inserta 100 elementos

CONSECUENCIAS A RECORDAR:
- Un rehash invalida los iteradores; debes ordenarlos nuevamente.
- Aumentar los buckets no corrige una mala función hash: 12,22 y 32 seguirán juntos porque producen exactamente el mismo hash.

Complejidad: con una buena distribución, buscar es O(1) en promedio; si muchas claves se acumulan en un bucket, puede llegar a O(n)
*/