#include <iostream>
#include <string>

#include <ostream>
#include <fstream>
#include <sstream>

using Score = int;

void writeScore(std::ostream& os, Score score){
    os << "Puntaje: " << score << '\n';
}

void print(std::ostream& os, std::string text){
    os << text << '\n';
}

int main(){
    const Score score = 300;

    // 1. Consola
    writeScore(std::cout, score);

    // sdt::cout << "Puntaje: " << score << '\n';

    // 2. Escribir un archivo
    std::ofstream file{"test.txt"};
    if(!file){
        return 1;
    }

    writeScore(file, score);

    // 3. Escribir en el buffer y recuperar
    std::ostringstream buff;

    writeScore(buff, score); // "Puntaje: 300" en el buffer

    std::string textoBuffer = buff.str();
    
    print(std::cout, textoBuffer);

    return 0;
}