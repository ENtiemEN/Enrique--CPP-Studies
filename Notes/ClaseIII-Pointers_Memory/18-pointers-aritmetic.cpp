#include <iostream>

// DECAY en parámetros de función
void process(int values[5]){
    // El parámetro tiene tipo `int*`. El [5] no comprueba la longitud.
    std::cout << values[0] << '\n';

    //std::cout << values[4] << '\n';
    // Si el arreglo tiene menos de 5 elementos, este acceso es UB.
}

void process(int* values); // Redeclara la misma función. No es una sobrecarga.

void processExactlyFive(const int (&values)[5]){
    // Referencia a un arreglo de 5 enteros. Conserva sui tamaño
    std::cout  << values[4] << '\n';
}

int main(){
    int values[]{10,20,30,40};

    int* p = values; // Conversión implícita a &values[0]
    
    // Dirección del arreglo completo
    //int (*whole)[4] = &values;
    //std::cout << (*whole)[1] << '\n', // 20

    std::cout << *p << '\n'; // 10
    std::cout << *(p + 1) << '\n'; // 20
    std::cout << *(p + 2) << '\n'; // 30
    std::cout << *(p + 3) << '\n'; // 40

    std::cout << p[2] << '\n'; // 30

    /*
        p[i] ≡ *(p + i)

        La suma `p + i` avanza `i` elementos, no `i` bytes.

        Para un puntero a `T`, el desplazamiento de direcciones entre elementos consecutivos corresponde a `sizeof(T)` bytes
    */
    
    std::cout << "\n--- --- --- --- --- ---\n";

    int* begin = values;
    int* end = values + 4;

    std::cout << *begin << '\n';
    //std::cout << end << '\n';
    //std::cout << *end << '\n'; // undefined beheavior

    for(int* p = begin; p !=end; ++p){
        std::cout << *p << ' ';
    }

    std::cout << "\n--- --- --- --- --- ---\n";

    // --> Diferencia entre punteros <--
    int numbers[]{1,2,3,4,5,6,7,8,9,10};

    int* x = &numbers[1];
    int* y = &numbers[3];

    std::cout << "*x : " << *x << '\n';
    std::cout << "*y : " << *y << '\n';

    // `std::ptrdiff_t` -> tipo entero con signo utilizado para representar diferencias entre punteros
    std::ptrdiff_t distance = y - x; // 2

    std::cout << "distance -> " << distance << '\n';

    std::cout << "\n--- --- --- --- --- ---\n";

    // --> ARREGLO vs PUNTERO <--
    int values_even[5] = {2,4,6,8,10};
    /*
        `values_even` tiene tipo `int[5]`
        En muchos contetos, la expresión `values` se convierte implícitamente en `int*`, apuntando al primer elemento. Esto se denomina "array-to-pointer conversion" o "decay".

        SIN EMBARGO, UN ARREGLO NO ES UN PUNTERO.
    */
    int* ptr = values_even;

    std::cout << "sizeof(values_even) -> " << sizeof(values_even) << '\n';
    std::cout << "sizeof(ptr) -> " << sizeof(ptr) << '\n';
    std::cout << "sizeof(*ptr) -> " << sizeof(*ptr) << '\n';

    int four[]{10, 20, 30, 40};
    int five[]{10, 20, 30, 40, 50};

    process(four);
    process(five);
    processExactlyFive(five);
    //processExactlyFive(four);


    std::cout << "\n--- --- --- --- --- ---\n";
    // --> Arreglos multidimensionales <--
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    // su tipo es `int[2][3]`
    // LA MEMORIA CONTIENE DOS ARREGLOS CONTIGUOS DE TRES ENTEROS CADA UNO.
    std::cout << matrix[1][2] << '\n'; // 6

    // En el contexto de DECAY, `matrix` se convierte en un puntero a un arreglo de 3 enteros
    
    int (*pointer)[3] = matrix; // Equivale a &matrix[0]

    std::cout << (*pointer)[2] << '\n'; // 3 | primero fila, tercera columna
    std::cout << (*(pointer + 1))[2] << '\n'; // 6 | segunda fila, tercera columna.
    std::cout << pointer[1][2] << '\n'; // 6 | lo mismo con índices

    /*
        `pointer + 1` avanza una fila completa, i.e., 3*sizeof(int) bytes.

        `int** invalid = matrix;` // ERROR: los elementos de matrix son filas de int.
    */

    return 0;
}