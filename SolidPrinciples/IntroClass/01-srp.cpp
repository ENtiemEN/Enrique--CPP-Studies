/* Idea -> Una clase debería tener un único motivo de cambio

Un motivo de cambio corresponde a una responsabilidad frente a quien define sus reglas. 

e.g.
- El área académica define cómo se calcula el promedio
- Quien diseña los reportes define cómo se presenta el resultado

SRP no significa "una clase debe tener un solo método". Una responsabilidad puede requerir varios métodos
*/
#include <iostream>
#include <ostream>

#include <fstream>

// Código con responsabilidades mezcladas. Funciona, pero tiene dos motivos de cambio

/*
Cambio solicitado: El promedio ahora será ponderado --> Método afectado: `average()`

Cambio solicitado: El reporte ahora debe generarse como CSV --> Método afectado: `writeReport()`
*/

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

    void writeReport(std::ostream& os) const{
        os << "Average: " << average() << '\n';
    }
};
    
} // namespace before

namespace after{

// Responsabilidad: representar las 'notas' y calcular el 'resultado'
class StudentResult{
private:
    double first_;
    double second_;
public:
    StudentResult(double first, double second) : first_{first}, second_{second} {
    }

    double average() const {
        return (first_ + second_) / 2.0;
    }

    bool passed() const {
        return average() >= 11.0;
    }
};

// Responsabilidad: presentar el resultado
void writeReport(std::ostream& os, const StudentResult& result){
    os << "Average: " << result.average() << '\n';

    os << "Status: " << (result.passed() ? "Passed" : "Failed") << '\n';
}

// Ahora podemos cambiar la presentación sin modificar `StudentResult`
void writeCsv(std::ostream& os, const StudentResult& result){
    os << "average,status\n";
    os << result.average() << ',' << (result.passed() ? "Passed" : "Failed") << '\n';
}

} // namespace after

int main(){
    const before::StudentResult original{14.0, 18.0};

    original.writeReport(std::cout);


    const after::StudentResult refactored{14.0, 18.0};

    after::writeReport(std::cout, refactored);

    std::ofstream file{"result.csv"};

    if(!file){
        std::cerr << "No se pudo abrir result.csv\n";
        return 1;
    }

    after::writeCsv(file, refactored);

    return 0;
}