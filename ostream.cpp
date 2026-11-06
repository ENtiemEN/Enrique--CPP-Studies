#include <string> // `std::string` tipo del texto que devuelve buffer.str()
#include <iostream> // `std::cout`: flujo de salida estándar | Ya incluye '<<'
#include <fstream> // `std::ofstream` -> flujo para ecribir en un archivo
#include <sstream> // `std::ostringstream` -> flujo para escribir texto en memoria.

using Score = int;

void writeScore(std::ostream& os, Score score){
    os << "Puntaje: " << score << '\n';
}

int main(){
    const Score score = 120;
    
    // 1. Escribe en consola
    writeScore(std::cout, 120); // `os` se refiere a la salida estándar

    // 2. Escribe en el archivo `scores.txt`
    std::ofstream file{"scores.txt"};
    if(!file) {
        return 1;
    }

    writeScore(file, 120); // `os` se refiere al flujo del archivo

    // 3. Escribe en memoria y recupera el resultado como texto.
    std::ostringstream buffer;
    writeScore(buffer, score);

    writeScore(buffer, 120); // `os` se refiere al flujo en memoria

    const std::string text = buffer.str();

    // Comprobando el texto generado
    return text == "Puntaje: 120\n" ? 0 : 1;
}