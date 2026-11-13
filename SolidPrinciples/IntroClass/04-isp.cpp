/*  ISP -- Interface Segregation Principle: un cliente no debería depender de operaciones que no necesita.

Diseñamos interfaces que representen capacidades coherentes, según las necesidades de sus clientes.

PROBLEMA: una interfaz exige demasiado
*/

#include <iostream>
#include <ostream>

namespace before {

class Machine{
public:
    virtual ~Machine() = default;

    virtual void print(std::ostream& os) const = 0;

    virtual void scan(std::ostream& os) const = 0;
};
// Una multifuncional puede implementar ambas operaciones. Pero una impresora básica solamente imprime..
// Para heredar de `Machine`, la impresora básica queda obligada a implementar `scan()`

class BasicPrinter : public Machine {
public:
    void print(std::ostream& os) const override {
        os << "Printing document\n";
    }

    // Obligado a implementar una capacidad que no tiene
    void scan(std::ostream&) const override{
        throw std::logic_error{"Scanning is not supported"};
    }
};

// Este cliente solamente necesita imprimir.
void printDocument(std::ostream& os, const Machine& machine){
    machine.print(os);
}

} // namespace before

namespace after{

class Printer{
public:
    virtual ~Printer() = default;

    virtual void print(std::ostream& os) const = 0;
};

class Scanner{
public:
    virtual ~Scanner() = default;

    virtual void scan(std::ostream& os) const = 0;
};

class BasicPrinter : public Printer{
public:
    void print(std::ostream& os) const override{
        os << "Basic printer: printing document\n";
    }
};

class MultifunctionPrinter: public Printer, public Scanner{
public:
    void print(std::ostream& os) const override {
        os << "Multifunction printer: printing document\n";
    }

    void scan(std::ostream& os) const override {
        os << "Multifunction printer: scanning document\n";
    }
};

// excercise
class BasicScanner : public Scanner{
};

// Cada cliente depende de la capacidad que utiliza.
void printDocument(std::ostream& os, const Printer& printer){
    printer.print(os);
}

void scanDocument(std::ostream& os, const Scanner& scanner){
    scanner.scan(os);
}


} // namespace after

int main(){
    const before::BasicPrinter original;

    std::cout << "Before:\n";
    before::printDocument(std::cout, original);

    try{
        original.scan(std::cout);
    }catch(const std::logic_error& error){
        std::cout << error.what() << '\n';
    }

    std::cout << "\nAfter:\n";

    const after::BasicPrinter basic;
    const after::MultifunctionPrinter multifunction;

    after::printDocument(std::cout, basic);
    after::printDocument(std::cout, multifunction);
    after::scanDocument(std::cout, multifunction);

    // NO COMPILA
    //after::scanDocument(std::cout, basic);

    return 0;
}

/*
Relación con LSP

Principio   Pregunta
ISP         ¿El cliente depende de operaciones que no necesita?

LSP         ¿La implementación cumple el contrato de la interfaz?
*/