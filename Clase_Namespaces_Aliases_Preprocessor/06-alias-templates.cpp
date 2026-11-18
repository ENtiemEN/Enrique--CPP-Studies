// Una plantilla de alias permite obtener un tipo apartir de parámetros

#include <iostream>

// --> 1. Familia de alias <--
template <typename T>
using Matrix = std::vector<std::vector<T>>;

// Matrix<int> -> std::vector<std::vector<int>>
// Matrix<double> -> std::vector<std::vector<double>>

// NO EXISTE una declaración equivalente `template typedef`

// --> 2. TIPO DEPENDIENTE <--
template <typename Container>
using Element = typename Container::value_type;