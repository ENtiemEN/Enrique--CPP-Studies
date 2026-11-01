#include <iostream>

void print(int value){
    std::cout << "int: " << value << std::endl;
}

void print(double value){
    std::cout << "double: " << value << std::endl;
}

void print(const char* value){
    std::cout << "string: " << value << std::endl;
}

int main(){
    print(10);
    print(3.14159265358979);
    print(2.718281828459045);
    print("Hellow");

    // ---> Aritmética de Punteros <---
    const char* ptr_s = "Diana";

    // En memoria tenemos (Representa "Diana" en memoria)
    // D i a n a \0 -> donde `\0` es un caracter especial llamado carácter nulo
    // ptr_s es un puntero que almacena la dirección en memoria del primer caracter de la cadena.

    /*
        `*ptr_s`
        equivale a 
        `ptr_s[0]`
    */

    std::cout << *ptr_s << std::endl;
    std::cout << *(ptr_s + 1) << std::endl;

    // C++ sobrecarga del operador `<<` para los punteros a caracteres
    std::cout << ptr_s << std::endl; // No me imprime la dirección de memoria del 'string'

    // Si quisieramos imprimir la dirección de memoria. Hacemos:
    std::cout << static_cast<const void*>(ptr_s) << std::endl;

    
    std::cout << sizeof(ptr_s) << std::endl; // 8 <-- tamaño en bytes del punto (En arquitectura 64bits) es 8 bytes
    // El puntero `const char* ptr_s`

    // Si queremos ver el tamaño de -> "Diana"
    std::cout << sizeof("Diana") << std::endl;

    // Mismo resultado.
    std::cout << sizeof(*ptr_s) << std::endl;
    std::cout << sizeof(ptr_s[0]) << std::endl;
}