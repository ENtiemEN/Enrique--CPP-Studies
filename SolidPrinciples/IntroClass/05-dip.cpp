// SOLID
// S (single responsability) O (open/closed) L (liskov substitution) I (interface segragation) D (dependency inversion)

/* DIP -- Dependency Inversion Principle
- Los módulos de alto nivel no deberían depender de módulos de bajo nivel. Ambos deberían depdnder de abstracciones

- Las abstracciones no deberían depender de los detalles. Los detalles deberían depender de las abstracciones

Concretizando --> servicio que confirma pedidos y envía una notificación.

Concepto     En el ejemplo

Alto nivel - OrderService: coordina la confirmación del pedido.

Bajo niveL - EmailNotifier: realiza la notificación por correo.

Abstracción - Notifier: establece la operación que necesita el servicio.

*/

#include <iostream>
#include <ostream>
#include <string>

namespace before{

class EmailNotifier {
public:
    void send(
        std::ostream& os,
        const std::string& message
    ) const {
        os << "[Email] " << message << '\n';
    }
};

class OrderService {
private:
    // El servicio depende de una implementación concreta.
    EmailNotifier notifier_;

public:
    void confirm(std::ostream& os, int orderId) const {
        // En este ejemplo suponemos que el pedido ya es válido.
        notifier_.send(
            os,
            "Order confirmed: " + std::to_string(orderId)
        );
    }
};

} // namespace before

namespace after{

// Abstracción que representa la capacidad requerida por el servicio.
class Notifier {
public:
    virtual ~Notifier() = default;

    virtual void send(
        std::ostream& os,
        const std::string& message
    ) const = 0;
};

class EmailNotifier : public Notifier {
public:
    void send(
        std::ostream& os,
        const std::string& message
    ) const override {
        os << "[Email] " << message << '\n';
    }
};

class SmsNotifier : public Notifier {
public:
    void send(
        std::ostream& os,
        const std::string& message
    ) const override {
        os << "[SMS] " << message << '\n';
    }
};

class OrderService {
private:
    // Referencia no propietaria a la abstracción.
    const Notifier& notifier_;

public:
    explicit OrderService(const Notifier& notifier)
        : notifier_{notifier} {}

    void confirm(std::ostream& os, int orderId) const {
        notifier_.send(
            os,
            "Order confirmed: " + std::to_string(orderId)
        );
    }
};

} // namespace after

int main(){
    std::cout << "Before:\n";

    const before::OrderService original;
    original.confirm(std::cout, 101);

    std::cout << "\nAfter:\n";

    const after::EmailNotifier email;
    const after::SmsNotifier sms;

    const after::OrderService emailService{email};
    const after::OrderService smsService{sms};

    emailService.confirm(std::cout, 102);
    smsService.confirm(std::cout, 103);
}