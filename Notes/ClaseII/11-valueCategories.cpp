/*  Categorías de expresiones

    expression -> glvalue , rvalue

    glvalue -> lvalue, xvalue
    rvalue -> xvalue, prvalue

    `xvalue` pertenece tanto a `glvalue` como a `rvalue`
*/
#include <iostream>

#include <utility>

int main(){

    int x = 10;

    // lvalue -> es una expresión cuya evaluación determina la identidad de un objeto o función
    x;
    ++x;

    // prvalue -> Se utiliza principalmente para calcular un valor o inicializar un objeto
    42;
    x+1;

    // xvalue -> Es una expresión glvalue que designa un objeto cuyos recursos pueden reutilizarse, típicamente en operaciones de movimiento
    std::move(x);

    //

    return 0;
}