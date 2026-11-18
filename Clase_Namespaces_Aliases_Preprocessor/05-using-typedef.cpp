#include <iostream>
#include <type_traits>

// --> 1. Sintaxis básica <--

using Score = int;
typedef int LegacyScore;

static_assert(std::is_same_v<Score, int>);

static_assert(std::is_same_v<LegacyScore, int>);

static_assert(std::is_same_v<Score, LegacyScore>);

// --> 2. Punteros y referencias <--
using IntPointer = int*; // `IntPointer` es un alias de `int*`

using IntReference = int&;

// --> 3. Arreglos <--
using Row = int[3];
typedef int LegacyRow[3];

static_assert(std::is_same_v<Row, LegacyRow>);

// --> 4. Punteros a funciones <--
using Operation = double (*)(double, double);

typedef double (*LegacyOperation)(double, double);

static_assert(std::is_same_v<Operation, LegacyOperation>);

double add(double left, double right){
    return left + right;
}

double multiply(double left, double right){
    return left * right;
}

double calculate(double left, double right, Operation operation){
    return operation(left, right);
}

// --> 5. Alias públicos de una clase <--

class PlayerScore {
public:
    using value_type = int;

    explicit PlayerScore(value_type value) : value_{value} {}

    value_type value() const{
        return value_;
    }
private:
    value_type value_;
};

int main(){
    Score score = 120;
    std::cout << score << '\n';

    // const se aplica al tipo representado por el alias
    int number = 10;

    const IntPointer pointer = &number;

    /*
    `const int*` -> el const se aplica al entero apuntado.

    `const IntPointer`, donde `IntPointer` es un alias de `int*`, el const se aplica al tipo completo representado por el alias (int*)

    ---
    `const IntPointer p = &a`
    El compilador lo interpreta como
    `int* const p = &a`

    Es decir:
    `const IntPointer` se convierte en
    `const (int*)` <-> `int* const` [Porque lo constante es el puntero no el valor]
    */

    *pointer = 20; // 👍 Podemos modificar su valor

    //pointer = nullptr; // ERROR no puede hacerse reasignaciones

    static_assert(std::is_same_v<decltype(pointer), int* const>);

    const int* readOnly = &number;

    //*readOnly = 30 // ERROR: acceso al entero como const.

    std::cout << *readOnly << '\n';

    // ALIAS DE REFERENCIA
    IntReference reference = number;
    reference = 30;

    std::cout << number << '\n'; // 30

    // ALIAS DE ARREGLO
    Row values{10,20,30};

    std::cout << values[2] << '\n'; // 30
    std::cout << sizeof(values) << '\n'; // 3 * sizeof(int)

    // ALIAS DE PUNTERO A FUNCIÓN
    std::cout << calculate(3.0, 4.0, add) << '\n'; // 7
    std::cout << calculate(3.0, 4.0, multiply) << '\n'; // 12

    // Alias de una clase


    return 0;
}
/*  Aclaraciones:

`const (int*)` es lo mismo que `int* const`

---
using IntPointer = int*;
const IntPointer p = nullptr; // int* const
---
PERO
---
using ConstIntPointer = const int*;

ConstIntPointer p = nullptr; // const int*
---
*/