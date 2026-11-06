#include <iostream>

void increment(int* ptr){
    if(ptr != nullptr){
        ++(*ptr);
    }
}

// Aunque lo declaremos `int arreglo[]`
// C++ lo interpreta `int* arreglo`
void elevar_cuadrado(int arreglo[], int size_total){

    for(int i=0; i < size_total; i++){
        arreglo[i] *= arreglo[i];
    }
}


int main(){
    int a = 10;
    // Dirección de memoria -> &
    int* ptr_a = &a;

    std::cout << &a << std::endl;
    std::cout << ptr_a << std::endl;

    std::cout << *ptr_a << std::endl;

    std::cout << "\n--- --- --- --- ---" << std::endl;

    int m = 20;
    int* ptr_m = &m;

    for(int i=0; i < 5; i++){
        increment(ptr_m);
    }

    std::cout << "m -> " << m << std::endl;

    std::cout << "\n--- --- --- --- ---" << std::endl;

    int arreglo[3] = {2,4,6};

    int size_total = sizeof(arreglo) / sizeof(arreglo[0]);

    elevar_cuadrado(arreglo, size_total);

    for(int i=0; i<3; i++){
        std::cout << arreglo[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "\n--- --- --- --- ---" << std::endl;

    const char* ptr_s = "Diana";

    // D i a n a \0
    std::cout << ptr_s << std::endl;

    // Aritmetica de punteros
    std::cout << *ptr_s << std::endl;
    std::cout << *(ptr_s + 1) << std::endl;

    std::cout << ptr_s[0] << std::endl;
    std::cout << ptr_s[1] << std::endl;

}