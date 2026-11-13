/*  LSP -- Liskov Substitution Principle

Continuando con los descuentos

Principio   Pregunta
OCP         ¿Puedo añadir otro descuento sin modificar `finalPrice()`?

LSP         ¿Ese nuevo descuento cumple lo que `finalPrice()` y sus clientes esperan?    
*/

#include <iostream>
#include <ostream>

// Contrato (Descuento)
// 0 <= precio_resultante <= precio_original

class Discount{
public:
    virtual ~Discount() = default;

    // virtual pure function
    virtual double apply(double price) const = 0;
};

namespace before{

class FixedDiscount : public Discount {
public:
    double apply(double price) const override{
        // Incumple con el contrato. Cuando price < 50
        return price - 50.0;
    }
};

} // namespace before

namespace after{

class FixedDiscount : public Discount {
public:
    double apply(double price) const override{
        // Limitación del descuento
        return std::max(0.0, price - 50.0);
    }
};

// Poner una clase que no cumpla el contrato
class PercentageDiscount : public Discount{
public:
    double apply(double price) const override{
        // Rompo el contrato definido
        //return price * 1.20;
        return price * 0.90; // <-- evito romper LSP
    }
};

// Cliente de la interfaz Discount
double finalPrice(double price, const Discount& discount){
    return discount.apply(price);
}

void writeExample(
    std::ostream& os,
    double price,
    const Discount& discount
){
    const double result = finalPrice(price, discount);

    os << "Original: " << price << '\n';
    os << "Final: " << result << '\n';

}


} // namespace after

int main(){
    const double price = 40.00;

    // BEFORE
    before::FixedDiscount original;

    std::cout << "Before -> Fixed: " << original.apply(price) << '\n';

    // AFTER

    after::FixedDiscount fixed;
    after::PercentageDiscount percentage;
    
    after::writeExample(std::cout, price, fixed);
    after::writeExample(std::cout, price, percentage);

    return 0;
}