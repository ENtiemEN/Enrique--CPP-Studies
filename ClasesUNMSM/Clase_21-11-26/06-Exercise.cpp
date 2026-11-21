/*
ntegrando los 5 principios en un Sistema de confirmación de pedidos:

1. Aplicar un descuento
2. Notificar la confirmación
3. Presentar el comprobante

Diseño del ejemplo:

`Receipt` --> Almacenar los datos del comprobante.
`Discount` -->  Definir el contrato de los descuentos.
`Notifier` --> Definir la capcacidad de enviar notificaciones.
`ReceiptPrinter` --> Definir la capacidad de presentar comprobantes
`OrderService` --> Coordinar la confirmación del pedido

`main()` --> Crea los objetos, conectarlos y ejecutar el ejemplo.
*/


#include <iostream>
#include <ostream>
#include <string>

#include <cmath> // -> std::isfinite()
#include <algorithm> // -> std::max() 
#include <stdexcept> // -> std::invalid_argument

// Recibo
struct Receipt{
    int id;
    double originalPrice;
    double finalPrice;
};

// === DESCUENTOS ===
/*
LSP: Todas las implementaciones de Discount deben respetar
el mismo contrato:

Precondición:
- price debe ser finito y mayor o igual a cero.

Poscondición:
- El resultado debe ser finito.
- 0 <= resultado <= price.

Cualquier implementación debe cumplir estas condiciones
para poder sustituir a otra sin romper el comportamiento.
*/

class Discount{
public:
    virtual ~Discount() = default;

    // virtual pure function
    virtual double apply(double price) const = 0;
};

class PercentageDiscount : public Discount{
public:
    double apply(double price) const override{
        return price * 0.90; // Descuento del 10%
    }
};

class FixedDiscount : public Discount{
public:
    double apply(double price) const override{
        return std::max(0.0, price - 50.0);
    }
};


// === NOTIFICACIONES ===
class Notifier{
public:
    virtual ~Notifier() = default;

    // virtual pure function
    virtual void send(std::ostream& os, const std::string& message) const = 0;
};

class EmailNotifier : public Notifier {
public:
    void send(std::ostream& os, const std::string& message) const override {
        os << "[Email] " << message << '\n';
    }
};

class SmsNotifier : public Notifier {
public:
    void send(std::ostream& os, const std::string& message) const override{
        os << "[SMS] " << message << '\n';
    }
};


// === PRESENTACIÓN DE COMPROBANTES ===
class ReceiptPrinter {
public:
    virtual ~ReceiptPrinter() = default;

    // virtual pure function
    virtual void print(std::ostream& os, const Receipt& receipt) const = 0;
};

class TextReceiptPrinter : public ReceiptPrinter{
public:
    void print(std::ostream& os, const Receipt& receipt) const override{
        os << "Order: " << receipt.id << '\n'
        << "Original: " << receipt.originalPrice << '\n'
        << "Final: " << receipt.finalPrice << '\n';
    }
};

void printReceipt(
    std::ostream& os,
    // clase abstracta - `ReceiptPrinter`
    const ReceiptPrinter& printer,
    const Receipt& receipt
){
    printer.print(os, receipt);
}

// === SERVICIO DE APLICACION

class OrderService{
private:
    const Discount& discount_;
    const Notifier& notifier_;
public:
    OrderService(
        const Discount& discount,
        const Notifier& notifier
    ) : discount_{discount}, notifier_{notifier} {}

    Receipt confirm(
        std::ostream& notificationOutput,
        int id,
        double originalPrice
    ) const {
        if(!std::isfinite(originalPrice) || originalPrice < 0.0){
            throw std::invalid_argument{"Price must be finite and non-negative"};
        };

        const Receipt receipt{
            id,
            originalPrice,
            discount_.apply(originalPrice)
        };

        notifier_.send(
            notificationOutput,
            "Order confirmed: " + std::to_string(id)
        );

        return receipt;
    }
};

// === COMPOSICIÓN Y EJECUCIÓN ===
int main(){
    const PercentageDiscount percentage;
    const FixedDiscount fixed;

    const EmailNotifier email;
    const SmsNotifier sms;

    const TextReceiptPrinter printer;

    const OrderService percentageEmailService{percentage, email};
    const OrderService fixedSmsService{fixed, sms};

    const Receipt first = percentageEmailService.confirm(std::cout,1,100.0);
    printReceipt(std::cout, printer, first);

    const Receipt second = fixedSmsService.confirm(std::cout,2,200.0);
    printReceipt(std::cout, printer, second);

    return 0;
}

/*  Recordar

SRP: ¿Cuántas responsabilidades tiene esta clase?

OCP: ¿Puedo agregar funcionalidades sin modificar código existente?

LSP: ¿Puedo sustituir una implementación por otra sin romper el contrato?

ISP: ¿Estoy obligando a una clase a depender de métodos que no necesita?

DIP: ¿Las clases de alto nivel dependen de abstracciones o de implementaciones concretas?
*/