/*  Ejercicio de integración
    Implementar un programa que procese calificaciones de estudiantes.

    Requisitos:
    1. Solicitar al usuario el número de calificaciones `n`, validando que sea positivo.
    2. Almacenar las calificaciones en un `std::vector<double>`.
    3. Validar cada calificación en el intervalo [0,20].
    4. Calcular la media aritmética, máximo, mínimo y cantidad de aprobados.
    5. Mostrar las calificaciones ordenadas de mayor a menor.
    6. Utilizar `const` y `auto` cuando corresponda, evitando conversiones innecesarias.
*/


#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm> // -> `std::minmax_element`, `std::count_if`, `std::sort`
//#include <functional> // -> `std::greater<double>`

int main(){
    int n;

    std::cout << "Number of students: ";

    if(!(std::cin >> n) || n <= 0){
        std::cerr << "Invalid number of students.\n";
        return 1;
    }

    std::vector<double> grades;
    // `size_t` es un tipo de dato entero sin signo (unsigned) que se utiliza en C++ para representar tamaños y cantidades de elementos
    grades.reserve(static_cast<std::size_t>(n));

    for(int i=0; i<n; ++i){
        double grade;
        std::cout << "Grade " << i+1 << ": ";

        if(!(std::cin >> grade) || !(grade >= 0.0 && grade <= 20.0)){
            std::cerr << "Invalid grade.\n";
            return 1;
        }

        // método que permite agregar un elemento al final del contenedor
        /*
            container -> Objeto que permite almacenar y organizar varios elementos en memoria

            En la biblioteca estándar de C++ (STL) proporciona:
            - `std::array`
            - `std::vector`
            - `std::list`
            - `std::stack`
            - `std::queue`
        
        */
        grades.push_back(grade);
    }

    const double sum = std::accumulate(
        grades.begin(),
        grades.end(),
        0.0
    );

    const double mean = sum / static_cast<double>(grades.size());

    const auto [minimum, maximum] = std::minmax_element(
        grades.begin(),
        grades.end()
    );

    const auto approved = std::count_if(
        grades.begin(),
        grades.end(),
        [](double grade){
            return grade >= 10.0;
        }
    );

    std::sort(
        grades.begin(),
        grades.end(),
        std::greater<double>{}
    );

    std::cout << "\nMean: " << mean << std::endl;
    std::cout << "Minimum: " << *minimum << std::endl;
    std::cout << "Maximum: " << *maximum << std::endl;
    std::cout << "Approved: " << approved << std::endl;

    std::cout << "Sorted grades: ";
    
    for(const double grade : grades){
        std::cout << grade << " ";
    }

    std::cout << std::endl;

    return 0;
}