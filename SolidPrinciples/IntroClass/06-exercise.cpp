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

// Datos del resultado de confirmar un pedido.
struct Receipt {
    int orderId;
    double originalPrice;
    double finalPrice;
};

// === DESCUENTOS ===

/* LSP: contrato para todas las implementaciones.

Precondición:
    price finito, >=0
Poscondición:
    El resultado es finito y cumple:
    0 <= resultado <= pricec
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

// ===  NOTIFICACIONES ===

// ISP: notificar es una capacidad INDEPENDIENTE de imprimir
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
// DIP: depende de abstracciones para descuento y notificación.

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