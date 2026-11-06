#include <string> // `std::string` tipo del texto que devuelve buffer.str()
#include <iostream> // `std::cout`: flujo de salida estándar | Ya incluye '<<'
#include <ostream> // `std::ostream` y las operaciones de escritura con <<
#include <fstream> // `std::ofstream` -> flujo para ecribir en un archivo
#include <sstream> // `std::ostringstream` -> flujo para escribir texto en memoria.

using Score = int;

class PlayerScore{
private:
    Score score_;
public:
    // `: score_{score}` -> introduce la lista de inicialización donde `score_` es el atributo privado y `score` es el parámetro recibido.
    explicit PlayerScore(Score score) : score_{score} {}
    // `explicit` -> quien quiera crear un `PlayerScore` a partir de un número lo tenga que expresar directamente con `PlayerScore{120}`

    // El método lee el puntaje del objeto y escribe el flujo recibido
    void write(std::ostream& os) const {
        os << "Puntaje: " << score_ << '\n';
    }
};

// void writeScore(std::ostream& os, Score score){
//     os << "Puntaje: " << score << '\n';
// }

int main(){
    const PlayerScore playerScore{120};
    
    // 1. Escribe en la salida estándar (normalmente es la consola)
    playerScore.write(std::cout);

    // 2. Abre un archivo para escritura y comprueba que se puedo abrir
    std::ofstream file{"scores.txt"};
    if(!file){
        return 1;
    }
    playerScore.write(file);

    // 3. Escribe en memoria y recupera el texto acumulado.
    std::ostringstream buffer;
    playerScore.write(buffer);
    const std::string text = buffer.str();

    return text == "Puntaje: 120\n" ? 0 : 1;
}