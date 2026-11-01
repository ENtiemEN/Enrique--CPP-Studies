#include <iostream>

int square(int x){
    return x*x;
}

int& getFirst(int& a, int& b){
    return a;
}

// ERROR: devolver referencias a objetos locales
int& dangeorus(){
    int x = 10;
    return x; // Dangling reference
}
// Cuando termina la función, finaliza el tiempo de vida de `x`. Utilizar posteriormente la referencia produce un comportamiento indefinido.
// La forma correcta, para este caso, es devolver por valor:
int safe(){
    int x = 10;
    return x;
}

int main() {
    int result = square(5);

    std::cout << result << std::endl;

    int x = 10;
    int y = 20;

    // `getFirst(x,y)` es un lvalue porque la función devuelve `int&`
    getFirst(x,y) = 100;

    std::cout << x << std::endl;

    return 0;
}