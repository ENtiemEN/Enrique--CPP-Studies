/*
OCP (Open/Closed Principle) --> Un componente debería estar abierto a extensión y cerrado a modificación.

e.g. -> incorporar nuevos descuentos sin editar continuamente el cálculo del precio final
*/
#include <iostream>

namespace before{

enum class CustomerType{
    Regular,
    Student,
};

double finalPrice(double price, CustomerType type){
    switch (type){
        case CustomerType::Regular:
            return price;
        case CustomerType::Student:
            return price * 0.80;
    }

    throw std::invalid_argument{
        "Customer Type Desconocido"
    };
}

} // namespace before

/* Si añadimos Clientes VIP
(cliente VIP necista otro descuento)

Tendríamos que modificar
1. enum
2. función `finalPrice()`
3. Cualquier otra función que use eso

SOLUCION --> INTERFAZ
*/

namespace after{

// Discount es una clase abstracta porque contiene al menos una función virtual pura. Esto significa que no podemos crear directamente objetos de esa clase. PERO sí puedes utilizarla como referencia o puntero y PUEDES crear objetos de sus clases derivadas.
class Discount{
public:
    virtual ~Discount() = default;

    // virtual pure function
    virtual double apply(double price) const = 0;

};

// Discount: clase abstracta
// StudentDiscount: clase concreta
// NoDiscount: clase concreta
// Vip: clase concreta // <- Open to extend / closed to modify

class StudentDiscount : public Discount{
    double apply(double price) const override{
        return price * 0.8;
    }
};

class NoDiscount : public Discount{
    double apply(double price) const override{
        return price;
    }
};

class Vip : public Discount{
    double apply(double price) const override{
        return price * 0.50;
    }
};

// Función que desconoce los descuentos internos
double finalPrice(double price, const Discount& discount){
    return discount.apply(price);
}

} // namespace after

int main(){
    
    const double price = 200.0;

    // BEFORE

    std::cout << "Before -> Student: " << before::finalPrice(price, before::CustomerType::Student) << '\n';

    std::cout << "Before -> No Discount: " << before::finalPrice(price, before::CustomerType::Regular) << '\n';

    // AFTER

    const after::NoDiscount regular;
    const after::StudentDiscount student;
    const after::Vip vip;

    std::cout << "After -> No discount: " << after::finalPrice(price, regular) << '\n';

    std::cout << "After -> Student: " << after::finalPrice(price, student) << '\n';

    std::cout << "After -> Vip: " << after::finalPrice(price, vip) << '\n';

    return 0;
}