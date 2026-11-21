/* ISP --- Interface Segregation Principle
*/

// Revisar --> SpecDriven Development

#include <iostream>
#include <ostream>

namespace before{

class Machine{
public:
    virtual ~Machine() = default;

    // virtual pure function
    virtual void print(std::ostream& os) const = 0;
    // vpf
    virtual void scan(std::ostream& os) const = 0;
};

class BasicPrinter : public Machine {
public:
    void print(std::ostream& os) const override {
        os << "Imprimiendo documento\n";
    }

    void scan(std::ostream& os) const override{
        throw std::logic_error{"El Scaneo no esta soportado"};
    }
};

// Función para imprimir
void printDocument(std::ostream& os, const Machine& machine){
    machine.print(os);
}

} // namespace before

namespace after{

class Printer{
public:
    // Destructor
    virtual ~Printer() = default;

    // vpf
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
        os << "[Basic Printer]: Imprimiendo documento\n";
    }
};

class MultifunctionPrinter : public Printer, public Scanner{
public:
    void print(std::ostream& os) const override{
        os << "[MultifunctionPrinter]: Imprimiendo documento\n";

    }

    void scan(std::ostream& os) const override{
        os << "[MultifunctionPrinter]: Scaneando documento\n";
    }   
};

class BasicScanner : public Scanner{
public:
    void scan(std::ostream& os) const override{
        os << "[BasicScanner]: Scaneando documento\n";
    }
};

// Sin implementar
void printDocument(std::ostream& os, const Printer& printer){
    printer.print(os);
};

void scanDocument(std::ostream& os, const Scanner& scanner){
    scanner.scan(os);
};

} // namespace after


int main(){
    std::cout << "--- --- --- --- BEFORE --- --- --- ---\n";

    const before::BasicPrinter original;

    before::printDocument(std::cout, original); // Imprimiendo documento

    try{
        original.scan(std::cout);
    }catch(const std::logic_error& error){
        std::cout << error.what() << '\n'; // "El Scaneo no está soportado"
    }

    std::cout << "--- --- --- --- AFTER --- --- --- ---\n";

    const after::BasicPrinter impresoraSimple;

    const after::MultifunctionPrinter impresoraAvanzada;

    const after::BasicScanner scannerSimple;

    // impresoraSimple.print(std::cout);

    // impresoraAvanzada.print(std::cout);
    // impresoraAvanzada.scan(std::cout);

    // scannerSimple.scan(std::cout);

    after::printDocument(std::cout, impresoraSimple);
    
    after::printDocument(std::cout, impresoraAvanzada);
    after::scanDocument(std::cout, impresoraAvanzada);

    after::scanDocument(std::cout, scannerSimple);

    return 0;
}