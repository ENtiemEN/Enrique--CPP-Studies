#include <iostream>
#include <unordered_map>
#include <vector>

/* e.g.
Queremos transformar:
{10,20,10,30,20,10}

Clave:número   Valor:cantidad de apariciones
10             3
20             2
30             1 
*/

using FrequencyMap = std::unordered_map<int, std::size_t>;
// cada elemento del `unordered_map` tiene `std::pair<const int, std::size_t>`

FrequencyMap countFrequencies(const std::vector<int>& values){
    FrequencyMap frequencies;

    for(const int value : values){
        ++frequencies[value];
    }

    return frequencies;
}

void writeFrequencies(std::ostream& os, const FrequencyMap& frequencies){
    // El orden del recorrido no está garantizado
    for(const auto& [value, count] : frequencies){
        os << value << " aparece " << count << " veces\n";
    }
}

int main(){
    const std::vector<int> values{10, 20, 10, 30, 20, 10};

    const FrequencyMap frequencies = countFrequencies(values);

    writeFrequencies(std::cout, frequencies);

    std::cout << "--- --- --- --- --- ---\n";

    // Consultar sin agregar claves.
    const auto it = frequencies.find(20);

    // it tiene `.first` y `.second`
    if(it != frequencies.end()){
        std::cout << "\nFrecuencia de " << it->first << ": " << it->second << '\n';
    }
    std::cout << "Valores distintos: " << frequencies.size() << "\n"; // 3

    // Podemos consultar mediante `find()` o `at()`, pero esto no compila
    // frequencies[20]
    // `operator[]` no está disponible para un mapa `const`

    return 0;
}