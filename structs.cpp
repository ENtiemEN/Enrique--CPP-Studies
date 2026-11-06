#include <iostream>

// En C: struct Point p;
// En C++: Point p; (No necesitamos escribir "struct")

struct Point{
    double x;
    double y;
};

//  === USING TEMPLATES ===

// 1. Struct Genérico
// T representa un tipo que se especifica al instanciar.
// typename y class son equivalentes en este contexto
template<typename T>
struct Point_t{
    T x;
    T y;
};

// 2. Struct con VARIOS parámetros de tipo
// T y U pueden representar tipos diferentes
template<typename T, typename U>
struct Pair{
    T first;
    U second;
};

// 3. Structs con MÉTODOS GENÉTICOS
template<typename T>
struct Vector2{
    T x;
    T y;

    void translate(T dx, T dy){
        x += dx;
        y += dy;
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }
};

// 4. FUNCIÓN TEMPLATE QUE RECIBE UN STRUCT GENÉRICO
// Recibe una referencia constante para evitar copias
template<typename T>
void print_generic_point(const Point_t<T>& p) {
    std::cout << "(" << p.x << ", " << p.y << ")\n";
}

// 5. Función TEMPLATE que devuelve un Struct genérico
template<typename T>
Point_t<T> add_points(
    const Point_t<T>& a,
    const Point_t<T>& b
){

    return Point_t<T>{
        a.x + b.x,
        a.y + b.y
    };
}


// --- --- --- --- --- ---

struct Data{
    int* ptr;
};

// Paso de Structs a funciones
//// cambios no afectan al objeto original
void translate_val(Point p, double dx, double dy){
    p.x += dx;
    p.y += dy;
}

//// cambios SÍ afectan al objeto original
void translate_ptr(Point* p, double dx, double dy){
    //(*p).x += dx; // Equivalente
    p->x += dx;
    p->y += dy;
}

// Paso por referencia C++: Point&
//// No necesitamos usar -> ni pasar &p al llamar
void translate_ref(Point& p, double dx, double dy){
    p.x += dx;
    p.y += dy;
}

// Referencia constante (C++) --> const Point&
// Permite solo lectura, no se puede copiar la estructura
void print_point(const Point& p){
    std::cout << "(" << p.x << ", " << p.y << ")\n";

    // p.x = 100.0; // Error: no se puede modificar p
}

int main() 
{
    //  --> Inicialización de STRUCTS <--
    // 1. Inicialización posicional (igual que C)
    Point p1 = {10.0, 20.0};

    // 2. Inicialización uniforme (C++11+)
    // Recomendado para structs simples
    Point p2{5.0, 8.0};

    // 3. Inicialización parcial
    Point p3{10.0}; // p3.y = 0.0

    // 4. Inicialización a cero
    Point p4{}; // x = 0.0, y = 0.0

    // 5. Asignación después de declarar
    Point p5;
    p5.x = 3.0;
    p5.y = 4.0;

    // --> DESIGNATED INITIALIZERS <--
    /*  En C99 sí existen:
        struct Point p = {.x=5.0, .y=8.0}

        En C++17 NO están soportados por el estándar.
        En C++20 se puede escribir
        Point p{.x = 5.0, .y = 8.0}
    */

    // --> OBJETOS TEMPORALES (C++) <--
    // Equivalente conceptual de los compound literals de C99
    // En C
    // struct Point p = (struct Point){10.0, 20.0};

    // En C++117
    Point p{10.0, 20.0};

    // podemos asignar un nuevo objeto TEMPORALES
    p = Point{30.0, 40.0};

    // --> Copia de STRUCTS: Semántica de valor <--
    Point a{10.0, 20.0};
    Point b = a;

    b.x = 100.0;

    std::cout << "a.x = " << a.x << '\n'; // 10
    std::cout << "b.x = " << b.x << '\n'; // 100

    // --> Copia superficial (SHALLOW COPY) <--
    // Si un miembro es un puntero, se copia su dirección, NO el objeto al que apunta

    int value = 10;

    Data m{&value};
    Data n = m;

    *n.ptr = 100;

    std::cout << *m.ptr << '\n'; // 100
    std::cout << *n.ptr << '\n'; // 100

    // m.ptr y n.ptr apuntan al mismo objeto

    // --> PUNTEROS A STRUCTS <--

    Point punto{10.0, 20.0};

    Point* ptr_p = &punto;

    std::cout << punto.x << '\n';
    std::cout << (*ptr_p).x << '\n';
    std::cout << ptr_p->x << '\n';

    // PASO DE STRUCTS A funciones

    // --> Paso por valor
    Point p_v{10.0, 20.0};
    translate_val(p_v, 5.0, 5.0);

    // El objeto original NO cambia.
    std::cout << "p_v.x -> " << p_v.x << '\n'; // 10
    std::cout << "p_v.y -> " << p_v.y << '\n'; // 20

    // --> Paso por puntero
    Point p_ptr{10.0, 20.0};

    translate_ptr(&p_ptr,5.0,5.0);

    // El objeto original SÍ cambia
    std::cout << "p_ptr.x -> " << p_ptr.x << '\n'; // 15.0
    std::cout << "p_ptr.y -> " << p_ptr.y << '\n'; // 25.0

    // --> Paso por referencia (C++17);
    Point p_r{10.0, 20.0};

    translate_ref(p_r, 5.0, 5.0);

    // La referencia actúa como alias del ojeto original
    std::cout << "p_r.x" << p_r.x << '\n'; // 15.0
    std::cout << "p_r.y" << p_r.y << '\n'; // 25.0

    // Referencia como alias

    Point original{10.0, 20.0};
    Point& ref = original;

    std::cout << original.x << '\n';
    std::cout << ref.x << '\n';

    // Una referencia debe inicializarse al DECLARARSE
    // Point& ref2; // Error

    // Referencia constante
    print_point(original);

    std::cout << "\n--- --- ---\n";

    // --> USANDO TEMPLATES <--
    Point_t<int> point1{10, 20};
    Point_t<double> point2{10.5, 20.8};
    Point_t<float> point3{3.5f, 4.5f};
    /* El compilador genera las especializaciones necesarias para los tipos utilizados
        IMPORTANTE:
        `template<typename T>` NO significa que `T` sea un tipo dinámico.
        C++ determina los tipos concretos durante compilación
    */

    print_generic_point(point1);
    print_generic_point(point2);

    // --> 2. VARIOS PARÁMETROS DE TIPO <--
    Pair<int, double> pair1{10, 3.14};
    Pair<double, int> pair2{3.14, 10};

    std::cout << pair1.first << '\n';
    std::cout << pair1.second << '\n';

    // --> 3. STRUCT GENÉRICO CON MÉTODOS <--

    Vector2<double> v{10.0, 20.0};

    v.translate(5.0, 5.0);
    v.print(); // (15, 25)

    // --> 3. STRUCT GENÉRICO CON MÉTODOS <--

    Vector2<double> v_1{10.0, 20.0};

    v_1.translate(5.0, 5.0);
    v_1.print(); // (15, 25)

    // --> 4. FUNCIÓN TEMPLATE CON STRUCTS <--

    Point_t<int> a1{10, 20};
    Point_t<int> b1{30, 40};

    // T se deduce automáticamente como int.
    Point_t<int> result = add_points(a1, b1);

    print_generic_point(result); // (40, 60)

    // También podemos indicar T explícitamente.
    auto result2 = add_points<int>(a1, b1);

    print_generic_point(result2); // (40, 60)


    return 0;
}