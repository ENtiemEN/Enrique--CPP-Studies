/* DIP -- Dependency Inversion Principle
Una clase no puede depender de cosas particulares, sino de generales (abstracciones)

Las abstracciones no deberían depender de los detalles. Los detalles deberían depender de las abstracciones
*/

#include <iostream>
#include <ostream>
#include <string>

namespace before{

// Mande notificaciones de tipo Email
class EmailNotifier{
public:
    void send(std::ostream& os, const std::string& message) const{
        os << "[Email] " << message << '\n';
    }
};

// Cordina el servicio
class OrderService{
private:
    EmailNotifier notifier_; // notifier_{notifier} <-- explicación
public:
    void confirm(std::ostream& os, int orderId) const{
        notifier_.send(os, "Orden confirmada: " + std::to_string(orderId));
    }
};

} // namespace before


namespace after{

// Abstracción -- Requerido por el servicio
class Notifier{
public:
    virtual ~Notifier() = default;

    // vpf
    virtual void send(std::ostream& os, const std::string& message) const = 0;
};

class EmailNotifier : public Notifier{
    void send(std::ostream& os, const std::string& message) const override{
        os << "[Email]: " << message << '\n';
    }

};

class SmsNotifier : public Notifier{
    void send(std::ostream& os, const std::string& message) const override{
        os << "[SMS]: " << message << '\n';
    }
};

// Cordinador de servicio
class OrderService{
private:
    // EmailNotifier notifier_; <-- No se trabaja con casos particulares
    // SmsNotifier notifier_; <-- No se trabaja con casos particulares
    const Notifier& notifier_; // <---
public:
    // `explicit` delante de OrderService(const Notifier& notifier), obligas al programador a crear el objeto OrderService de manera intencional y directa, evitando que el compilador convierta un Notifier en un OrderService por accidente.
    explicit OrderService(const Notifier& notifier) : notifier_{notifier} {}

    void confirm(std::ostream& os, int orderId) const {
        notifier_.send(os, "Orden confirmada: " + std::to_string(orderId));
    };
};


} // namespace after

int main(){
    std::cout << "--- --- --- --- BEFORE --- --- --- ---\n";

    const before::OrderService original;

    original.confirm(std::cout, 1);  // "Orden confirmada: 1"

    std::cout << "--- --- --- --- AFTER --- --- --- ---\n";

    const after::EmailNotifier email;
    const after::SmsNotifier sms;

    const after::OrderService emailService{email};
    const after::OrderService smsService{sms};

    emailService.confirm(std::cout, 2);

    smsService.confirm(std::cout, 3);

    return 0;
}

