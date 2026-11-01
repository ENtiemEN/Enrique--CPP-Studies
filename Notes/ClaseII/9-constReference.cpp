/*  USOS RECOMENDADOS DE CADA MECANISMO

    Parametro           Uso Recomendado
    `T value`           Tipos pequeños o cuando necesitamos una copia

    `T& value`          Cuando la función debe modificar el objeto original

    `const T& value`    Objetos grandes que solamente necesitamos consultar

    `T&& value`         Referencias rvalue, útiles en movimiento y otras técnicas avanzadas

    `T* ptr`            Acceso mediante punteros, especialmente cuando puede ser nulo
*/

#include <iostream>
#include <vector>

// Paso por referencia constante: `const T&`
/*  Ventajas
    - Evita copiar el vector
    - Impide modificarlo mediante el parametro
    - Acepta objetos modificables, constantes y temporales compatibles
*/
void printVector(const std::vector<int>& values) {
    for(const int& value : values){
        std::cout << value << ' ';
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> a{1,2,3};

    const std::vector<int> b{4,5,6};

    return 0;
}