#include <iostream>

struct Point{
    int x;
    int y;
};

// TEMPLATE
// Si no queremos definir un tipo de dato, antes de la compilación
template<typename T>
struct Point_t{
    T x;
    T y;
};

template<typename T, typename U>
struct Point_t_multiple{
    T x;
    U y;
};

struct Data{
    int* ptr;
};

// Pasar por valor
void translate_val(Point p, double dx, double dy){
    p.x += dx;
    p.y += dy;
} // Muere al acabarse el llamado de la función

//// pasar el puntero
void translate_ptr(Point* ptr_p, double dx, double dy){
    //(*ptr_p).x += dx;
    ptr_p->x += dx;
    ptr_p->y += dy;
}

// Pasar por referencia
void translate_ref(Point& p, double dx, double dy){
    p.x += dx;
    p.y += dy;
}

int main(){
    // Point point;
    // point.x = 2;
    // point.y = 3;

    Point point = {2, 3};
    Point point1 = point;

    point1.x = 0;

    std::cout << point1.x << '\n'; // 0
    std::cout << point.x << '\n'; // 2

    std::cout << "\n--- --- --- --- --- ---\n";

    Point* ptr_point = &point;

    // Desreferenciar
    std::cout << (*ptr_point).x << '\n';
    // en OOP: this->argumento
    std::cout << ptr_point->x << '\n';    

    std::cout << "\n--- --- --- --- --- ---\n";
    
    int valor = 10;

    Data m = { &valor };
    Data n = m;

    *(n.ptr) = 100;

    std::cout << "*(n.ptr) : " <<  *n.ptr << '\n'; // 100
    std::cout << "*(m.ptr) : " << *m.ptr << '\n'; // 100

    std::cout << "\n--- --- --- --- --- ---\n";
    // Pasar Structs a funciones

    Point punto = {10, 20};

    translate_val(punto,2,2);
    std::cout << "p_v.x : " << punto.x << '\n';
    std::cout << "p_v.y : " << punto.y << '\n';

    Point* ptr_punto = &punto;
    translate_ptr(ptr_punto, 2, 2);
    // std::cout << "punto.x : " << ptr_punto->x << '\n';
    // std::cout << "punto.y : " << ptr_punto->y << '\n';

    std::cout << "punto.x : " << punto.x << '\n';
    std::cout << "punto.y : " << punto.y << '\n';

    translate_ref(punto, 2, 2);

    std::cout << "punto.x : " << punto.x << '\n';
    std::cout << "punto.y : " << punto.y << '\n';

    // --> Introducción a Templates <--
    Point_t<int> punto1 = {10, 10};
    Point_t<float> punto2 = {10.4, 21.5};

    return 0;
}