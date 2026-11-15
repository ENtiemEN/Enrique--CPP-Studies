#include <iostream>
#include <string>

namespace reporting {
    void write(std::ostream& os, int value){
        os << "Integer: " << value << '\n';
    }

    void write(std::ostream& os, const std::string& value){
        os << "Text: " << value << '\n';
    }

    constexpr int width = 80;
}

// `using` dentro de una clase derivada

class Base{
public:
    void write(std::ostream& os, int value) const {
        os << "Base integer: " << value << '\n';
    }
};

class Derived : public Base {
public:
    // Incorpora las sobrecargas de Base::write
    using Base::write;

    void write(std::ostream& os, const std::string& value) const {
        os << "Derived text: " << value << '\n';
    }
};

/*
Sin `using Base::write`, la declaración `Derived::write` ocultaría `Base::write` en la búsqueda mediante Derived.

No importa que sus parámetros sean diferentes
*/

// Herencia de constructores
class Counter{
private:
    int value_;
public:
    explicit Counter(int value) : value_{value}{}

    int value() const{
        return value_;
    }
};

class TaggedCounter : public Counter {
public:
    using Counter::Counter;
};

int main(){
    // --> 1. Using-declaration: nombre concreto <--
    {
        using reporting::write;

        // Las dos sobrecargas declaradas están disponibles
        write(std::cout, 42);
        write(std::cout, std::string{"C++17"});

        // width no fue introducido
        //std::cout << width; // ERROR

        std::cout << reporting::width << '\n';
    }

    // La declaración using anterior era local al bloque
    //write(std::cout, 42); // Error

    // --> 2. Using-directive: namespace <--
    {
        using namespace reporting;

        write(std::cout, 42);
        write(std::cout, "Enrique");
        std::cout << width << '\n';
    }

    // --> 3. Using en clases <--
    Derived object;

    object.write(std::cout, 42);
    object.write(std::cout, std::string{"Hello"});

    TaggedCounter counter{10};
    std::cout << counter.value() << '\n';
    return 0;
}
/*  Diferencias

    `using reporting::write;`       // Introduce un nombre concreto

    `using namespace reporting;`    // Influte en la búsqueda de nombres
*/
