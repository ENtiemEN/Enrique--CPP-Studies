/*
`namespace app { ... }` -> Define o amplía el espacio de nombres.

`using app::write;` -> Introduce un nombre completo

`using namespace app;` -> Permite considerar los nombres de un namespace en la búsqueda no cualificada

`namespace short_name = long_name;` -> Define un alias de namespace

`using Score = int;` -> Define un alias de tipo

`typedef int Score;` -> También define un alias de tipo

`#define NAME replacement` -> Define una sustitución de tokens del preprocesador
*/

#include <iostream>

// --> 1. Espacio de nombres global <--

// esta variable pertenece al namespace global
constexpr int version = 1;

// --> 2. Namespaces con nombres <--
namespace academic {
    struct Student {
        int score;
    };

    // Declaración. La definición aparecerá fuera del bloque
    void write(std::ostream& os, const Student& student);

    constexpr int version = 2;
}

namespace game {
    struct Player {
        int score;
    };

    void write(std::ostream& os, const Player& player){
        os << "Player score: " << player.score << '\n';
    }
}

// `academic::write` y `game::write` son funciones distintas
// Sus nombres completos incluyen el namespace al que pertenecen

// --> 3. Definición fuera del bloque del namespace <--

// La función ya fue declarada dentro de academic
void academic::write(std::ostream& os, const Student& student){
    os << "Student score: " << student.score << '\n';
}
// En esta definición, Student se encuentra en academic -> `void academic::write`

// --> 4. Reapertura <--

namespace academic {
    // AMPLÍA el mismo namespace; NO CREA OTRO
    bool passed(const Student& student){
        return student.score >= 11;
    }
}

// --> 5. NAMESPACES ANIDADOS: Sintaxis C++17

namespace app::reporting {
    void writeTitle(std::ostream& os){
        os << "Report\n";
    }
}
/* Equivale a

namespace app {
    namespace reporting {
        ...
    }
}
*/

// --> 6. Namespace Sin Nombre <--
namespace {
    // Estos nombres tienen enlace interno.
    // Son propios de esta unidad de traducción
    int reportsWritten = 0;
    
    void registerReport(){
        ++reportsWritten;
    }
}

/* Uso habitual: funciones auxiliares y estado interno de un .cpp

No es un mecanismo de privacidad de clases.
Evita colocarlo en headers salvo que busques deliberadamente entidades independientes en cada unidad de traducción
*/

// --> 7. Inline namespace <--
namespace library {
    inline namespace v2 {
        constexpr int apiVersion = 2;
    }

    namespace v1 {
        constexpr int apiVersion = 1;
    }
}
/* Los miembres de v2 pueden encontrarse mediante library

`library::apiVersion`       --> versión predeterminada
`library::v2::apiVersion`   --> acceso explícito
`library::v1::apiVersion`   --> versión anterior

inline namespace sirve, entre otros usos, para versionar interfaces.
No está relacionado con intentar insertar el cuerpo de una función.
*/

int main(){
    academic::Student student{17};
    game::Player player{120};

    academic::write(std::cout, student);
    game::write(std::cout, player);

    std::cout << std::boolalpha << "Passed: " << academic::passed(student) << '\n';

    // `::version` especifica el namespace global
    std::cout << "Global version: " << ::version << '\n';
    std::cout << "Academic version: " << academic::version << '\n';

    app::reporting::writeTitle(std::cout); // Namespace anidado

    registerReport(); // namespace sin nombre
    std::cout << "Reports: " << reportsWritten << '\n';

    std::cout << "Default API: " << library::apiVersion << '\n';
    std::cout << "Previous API: " << library::v1::apiVersion << '\n';

    return 0;
}
/*  Observaciones:
    - `academic::Student` y `game::Player` pertenecen a componentes diferentes.
    
    - Puedes abrir varias veces el mismo namespace.

    - Un namespace NO SE INSTANCIA y no tiene `public` o `private`.

    - Las definiciones de namespaces se colocan en ámbito de namespace; NO PUEDES DEFINIR UNO DENTRO DE UNA FUNCIÓN
*/