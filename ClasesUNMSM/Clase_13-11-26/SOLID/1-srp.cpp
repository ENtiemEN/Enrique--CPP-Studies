// SOLID
// S (srp) O (ocr) L (lsp) I (isp) D (dip)

// SRP -- Single Responsability Principle
// Una clase debe tener un motivo de cambio

#include <iostream>
#include <ostream>

#include <fstream>

// Llega un cambio solicitado --> Reporte ahora debe generarse como CSV (Método afectado `writeReport()`)

namespace before {

class StudentResult{
private:
    double first_;
    double second_;
public:
    StudentResult(double first, double second) : first_{first}, second_{second} {}

    double average() const {
        return (first_ + second_) / 2.0;
    }

    void writeReport(std::ostream& os){
        os << "Average: " << average() << '\n';
    }
};
} // namespace before

namespace after {

class StudentResult{
private:
    double first_;
    double second_;
public:
    StudentResult(double first, double second) : first_{first}, second_{second} {}

    double average() const {
        return (first_ + second_) / 2.0;
    }

    bool passed() const{
        return average() >= 11.0;
    }
};

// Responsabilidad -> presentar el resultado
void writeReport(std::ostream& os, const StudentResult& result){
    os << "Average: " << result.average() << '\n';
}

// nuevo pedido (No tengo que tocar la clase)
void writeCsv(std::ostream& os, const StudentResult& result){
    os << "average, status\n";
    os << result.average() << ',' <<  (result.passed() ? "Passed" : "Failed")  << '\n';
}
/* Sintaxis de una expresión ternaria
    (expresion) ? ejecutaSiEsVerdadero : ejercutaSiEsFlaso;
*/

} // namespace after

int main(){

    // BEFORE -- Antes de usar nuestro SRP
    before::StudentResult cesar{15.0, 18.0};

    cesar.writeReport(std::cout);

    // AFTER -- Usando nuestro SRP
    after::StudentResult eduardo{14.0, 18.0};

    after::writeReport(std::cout, eduardo);

    std::ofstream file{"resultados.csv"};

    if(!file){
        std::cerr << "Archivo no se creó correctamente" << '\n';
    }

    after::writeCsv(file, eduardo);

    return 0;
}