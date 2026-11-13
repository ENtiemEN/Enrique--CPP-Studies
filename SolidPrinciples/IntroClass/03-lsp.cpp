/* Idea central
    LSP -- Liskov Substitution Principle: un objeto derivado debe poder sustituir a uno de su clase base sin romper el comportamiento esperado por el cliente.

    Heredar y usar `override` garantiza compatibilidad de tipos y firmas. TAMBIÉN DEBEMOS RESPETAR EL CONTRATO DE COMPORTAMIENTO.

Continuando con los descuentos
Principio   Pregunta
OCP         ¿Puedo añadir otro descuento sin modificar `finalPrice()`?

LSP         ¿Ese nuevo descuento cumple lo que `finalPrice()` y sus clientes esperan?
*/

#include <iostream>
#include <ostream>

// Contrato:
// Entrada: precio finito >= 0
// Salida: precio finito entre 0 y el precio original

// El contrato es 0 <= precio_final <= precio_original

class Discount{
public:
    virtual ~Discount() = default;

    virtual double apply(double price) const = 0;
};

namespace before{

class FixedDiscount : public Discount{
public:
    double apply(double price) const override{
        //Incumple el contrato cuando price < 50
        return price - 50.0;
    }
};

} // namespace before

namespace after{

class FixedDiscount : public Discount{
public:
    double apply(double price) const override{
        // El descuento queda limitado al precio disponible
        return std::max(0.0, price - 50.0);
    }
};

// PREGUNTA: ¿Respeta LSP aunque compile y utilice correctamente `override`?
// NO: para precios positivos aumenta el precio y viola la poscondición. 
class PercentageDiscount : public Discount {
public:
    double apply(double price) const override {
        return price * 1.10;
        //return price * 0.90; // CORRECCIÓN (e.g. Descuento de 10%)
    }
};

} // namespace after

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

int main(){
    const before::FixedDiscount broken;

    const after::FixedDiscount corrected;

    std::cout << "Before:\n";
    writeExample(std::cout, 30.0, broken);

    std::cout << "\nAfter:\n";
    writeExample(std::cout, 30.0, corrected);

    return 0;
}

/*  Observaciones:
Reglas prácticas:
Una clase derivada no debe exigir más de lo que exige la base.

Si `Discount` acepta cualquier precio finito no negativo, una implementación no puede introducir unilateralmente este requisito

Una clase derivada DEBE GARANTIZAR LO QUE PROMETE LA BASE.

Si la interfaz garantiza un resultado entre `0` y precio original, devolver un precio negativo o superior al original rompe esa garantía.

Estas reglas se conocen como:
- No reforzar precondiciones.
- No debilitar poscondiciones.
*/