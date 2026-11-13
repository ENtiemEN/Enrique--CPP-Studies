/* Idea central
OCP (Open/Closed Principle) --> Un componente debería estar abierto a extensión y cerrado a modificación.

Para una variación prevista, deberíamos poder añadir un comportamiento sin modificar la lógica que lo utiliza.

e.g. -> incorporar nuevos descuentos sin editar continuamente el cálculo del precio final
*/

#include <iostream>
#include <stdexcept>

namespace before{

enum class CustomerType{
    Regular,
    Student
};

double finalPrice(double price, CustomerType type){
    switch(type){
        case CustomerType::Regular:
            return price;
        case CustomerType::Student:
        return price * 0.90;
    }

    throw std::invalid_argument{"Unkown customer type"};
}

} // namespace before

/* Si añadimos clientes VIP, modificamos:
1. El `enum`
2. La función `finalPrice()`
3. Cualquier otra función que tome decisiones sobre esos tipos de cliente.

SOLUCIÓN -> representar la variación mediante una INTERFAZ

"La parte variable es como se aplica el descuento"
*/

namespace after{

// Definimos una interfaz
// Interfaz --> Representa una política de descuento.

// Discount es una clase abstracta porque contiene al menos una función virtual pura. Esto significa que no podemos crear directamente objetos de esa clase. PERO sí puedes utilizarla como referencia o puntero y PUEDES crear objetos de sus clases derivadas.
class Discount{
public:
    virtual ~Discount() = default;

    virtual double apply(double price) const = 0;
};

/* Distinción
Discount: clase abstracta
StudentDiscount: clase concreta
NoDiscount: clase concreta
*/

class NoDiscount : public Discount{
public:
    double apply(double price) const override {
        return price;
    }
    // `override` indica que estamos sobreescribiendo una función virtual heredada de una clase base.
    // Ventaja (override en C++) --> el compilador verifica que realmente estás sobreesbiendo una función de la clase base [si no ponemos `const` saldría error]
};

class StudentDiscount : public Discount{
public:
    double apply(double price) const override{
        return price * 0.90;
    }
};

class VipDiscount : public Discount {
public:
    double apply(double price) const override{
        return price * 0.80;
    }
};

// función que deconoce los descuentos concretos
double finalPrice(double price, const Discount& discount){
    return discount.apply(price);
}

} // namespace after

int main(){
    const double price = 100.0;

    std::cout << "Befor - Student: " << before::finalPrice(
        price,
        before::CustomerType::Student
    ) << '\n';

    const after::NoDiscount regular;

    const after::StudentDiscount student;

    std::cout << "After - Regular: " << after::finalPrice(price, regular) << '\n';

    std::cout << "After - Student: " << after::finalPrice(price, student) << '\n';

    /*  Observación:
        En `after::finalPrice(price, student);` El parámetro tiene tipo `const Discount&`, pero se refiere a un objeto `StudentDicount` (argumento)

        Por ser virtual, esta operación
        discount.apply(price);
        ejecuta `StudentDiscount::apply()`
    */

    const after::VipDiscount vip;

    std::cout << "After - Vip: " << after::finalPrice(price, vip) << '\n';
}

// Disclaimer --> En este ejemplo usamos `double` para simplificar la demostración; el tratamiento monetario precisa queda fuera del ejemplo

/*  Aclaraciones Sintacticas

`enum class`

enum (tradicional):
---
enum CustomerType {
    Regular,
    Student
};

CustomerType customer = Student;
---

enum class (enumeración con ámbito)

Ahora se debe acceder a sus valores utilizando el nombre de la numeración
---
enum class CustomerType{
    Regular,
    Student
}
CustomerType customer = CustomerType::Student
---
Ventajas:
    - Evita conflictos de nombres.
    - Es más seguro con los tipos: no se convierte implícitamente a un entero como sucede con los `enum` tradicionales

--------------------------------
`virtual` -> permite utilizar "polimorfismo dinámico"

`virtual` permite seleccionar la implementación según el tipo real del objeto.

--------------------------------
Ejemplo `virtual ~Discount() = default`;

`~Discount()` -> destructor de la clase `Discount`

En C++, un destructor es una función especial que se ejecuta cuando un objeto se destruye.
El destructor permite realizar tareas de limpieza, como liberar recursos.

¿Por qué `virtual ~Class()`?
---
class Discount{
public:
    ~Discount(){}
};

class StudentDiscount : public Discount{
public:
    ~StudentDiscount(){}
};

Discount* discount = new StudentDiscount();

delete discount
---
Si el destructor de Discount no es virtual, eliminar un objeto derivado mediante un puntero a la clase base provoca comportamiento indefinido.

Por eso, cuando una clase está diseñada para utilizarse polimórficamente, su destructor normalmente debe ser virtual

e.g. `virtual ~Class() = default;`
`= default` Significa --> Compilador, genera automáticamente la implementación predeterminada de este destructor.

i.e. NO QUEREMOS escribir MANUALMENTE el destructor porque NO NECESITAMOS NINGUNA LÓGICA PERSONALIZADA.

Podríamos escribir:
---
virtual ~Discount() {
}
---
Pero `= default` expresa mejor nuestra intención.

Significa
""Declara un destructor virtual y utiliza su implementación predeterminada generada por el compilador""

--------------------------------

`virtual T1 func(T2 _) const = 0;`

`const` -> la función no puede modificar el estado del objeto.

`= 0` -> Declara una función virtual pura. (pure virtual function)

Significa que la clase base establece que esta función debe existir, pero no proporciona una implementación obligatoria.

Ejemplo
---
class Discount(){
public:
    virtual double apply(double price) const = 0;
}
---
i.e.
""Cualquier clase concreta que herede de Discount debe proporcionar su propia implementación de apply.""

--------------------------------
Observa:
`double apply(double price) const`

El const no pertenece al parámetro price. Tampoco al valor devuelto (return)
Significa
""Esta función promete NO MODIFICAR EL ESTADO OBSERVABLE DEL OBJETO sobre el que se invoca.""
*/