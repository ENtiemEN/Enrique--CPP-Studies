/*
Integrando los 5 principios en un Sistema de confirmación de pedidos:

1. Aplicar un descuento
2. Notificar la confirmación
3. Presentar el comprobante

Cada componente tendrá una responsabilidad y colaborará mediante interfaces.

Diseño del ejemplo:

`Receipt` --> Almacenar los datos del comprobante.
`Discount` -->  Definir el contrato de los descuentos.
`Notifier` --> Definir la capcacidad de enviar notificaciones.
`ReceiptPrinter` --> Definir la capacidad de presentar comprobantes
`OrderService` --> Coordinar la confirmación del pedido

`main()` --> Crea los objetos, conectarlos y ejecutar el ejemplo.

Aclaraciones:
Las notificaciones se simulan mediante mensajes. El ejempo supone que el pedido ya existe; no incluye inventario, pagos ni persistencia
*/

#include <iostream>
#include <ostream>
#include <string>

#include <cmath> // -> std::isfinite()
#include <algorithm> // -> std::max()
#include <stdexcept> // -> std::invalid_argument

// Datos del resultado de confirmar un pedido.
struct Receipt {
    int orderId;
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


// OCP: Discount permite extender los tipos de descuentos mediante nuevas implementaciones sin modificar las clases existentes ni `OrderService`
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

// ===  NOTIFICACIONES ===

// ISP: Define exclusivamente la capacidad de enviar notificaciones. No obliga a sus implementaciones a proporcionar impresión de comprobantes

class Notifier{
public:
    virtual ~Notifier() = default;

    // virtual pure function
    virtual void send(std::ostream& os, const std::string& message) const = 0;
};

class EmailNotifier : public Notifier {
public:
    void send(std::ostream& os, const std::string& message) const override {
        os << "[Email]" << message << 'n';
    }
};

class SmsNotifier : public Notifier {
public:
    void send(std::ostream& os, const std::string& message) const override{
        os << "[SMS]" << message << '\n';
    }
};

// === PRESENTACIÓN DE COMPROBANTES ===

// ISP: Define exclusivamente la capacidad de presentar comprobantes. NO obliga a sus implementaciones a proporcionarnotificaciones

class ReceiptPrinter {
public:
    virtual ~ReceiptPrinter() = default;

    // virtual pure function
    virtual void print(std::ostream& os, const Receipt& receipt) const = 0;
};

// SRP: solamente decide cómo presentar el comprobante
class TextReceiptPrinter : public ReceiptPrinter{
public:
    void print(std::ostream& os, const Receipt& receipt) const override{
        os << "Order: " << receipt.orderId << '\n'
        << "Original: " << receipt.originalPrice << '\n'
        << "Final: " << receipt.finalPrice << '\n';
    }
};

// Cliente que solamente necesita la capacidad de imprimir 
void printReceipt(
    std::ostream& os,
    // clase abstracta - `ReceiptPrinter`
    const ReceiptPrinter& printer,
    const Receipt& receipt
){
    printer.print(os, receipt);
}

// === SERVICIO DE APLICACION ===

// SRP: coordina la confirmación
// DIP: OrderService es un módulo de alto nivel que depende de las abstracciones Discount y Notifier, no de implementaciones concretas como (e.g.) PercentageDiscount, FixedDiscount, EmailNotifier o SmsNotifier

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
        int orderId,
        double originalPrice
    ) const {
        if(!std::isfinite(originalPrice) || originalPrice < 0.0){
            throw std::invalid_argument{"Price must be finite and non-negative"};
        };

        const Receipt receipt{
            orderId,
            originalPrice,
            discount_.apply(originalPrice)
        };

        notifier_.send(
            notificationOutput,
            "Order confirmed: " + std::to_string(orderId)
        );

        return receipt;
    }
};

// === Composición y ejecución ===
int main(){
    const PercentageDiscount percentage;
    const FixedDiscount fixed;

    const EmailNotifier email;
    const SmsNotifier sms;

    const TextReceiptPrinter printer;

    // Las colaboraciones existen antes de los servicios, y permanecen vivos mientras estos los utilizan
    const OrderService percentageEmailService{percentage, email};

    const OrderService fixedSmsService{fixed, sms};

    const Receipt first = percentageEmailService.confirm(
        std::cout,
        101,
        100.0
    );

    printReceipt(std::cout, printer, first);

    std::cout << '\n';

    const Receipt second = fixedSmsService.confirm(
        std::cout, 
        102,
        30.0
    );

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