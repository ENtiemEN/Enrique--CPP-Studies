#include <iostream>
#include <string>

int main(){
    const char* s = "Hello";
    
    std::string first = "Ada";
    std::string last = "Lovelace";

    // --> Concatenación de Strings <--
    std::string full = first + " " + last;

    std::cout << full << std::endl;
    std::cout << full.size() << std::endl;
    std::cout << full.substr(0, 3) << std::endl;

    // --> Comparación de Strings <--
    std::string a = "Python";
    std::string b = "PYthon";

    bool same = (a == b); // False

    std::cout << same << std::endl;

    // --> Entrada de Strings <--
    std::string name;
    std::string full_name;

    std::cout << "Ingrese su primer nombre: ";
    std::cin >> name;
    // Cuando escribimos "Enrique" y presionamos Enter, en el 'Flujo de entrada queda conceptualmente' ->
    // Enrique\n
    // `std::cin >> name` lee Enrique. Pero no consume el salto de línea \n (Permanece pendiente en el flujo de entrada)

    std::cin.ignore(); // Consume el salto de línea -- Función que descarta caracteres del flujo de entrada. Forma general:
    // `std::cin.ignore(cantidad, delimitador)`

    std::cout << name << std::endl;
    
    // Si es que sigue pendiente un salto de línea. `getline()` lo encuentra.
    std::cout << "Ingrese su nombre completo: ";
    std::getline(std::cin, full_name);

    std::cout << full_name << std::endl;

    return 0;
}