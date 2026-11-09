/*
`new` -> expresión que obtiene almacenamiento y construye un objeto en él.

`delete` -> expresión que destruye el objeto correspondiente y libera el almacenamiento conforme a las reglas aplicables
*/
#include <iostream>
#include <cstddef>

#include <new>

struct Resource{
    explicit Resource(int id) : id{id} {
        std::cout << "Contructed: " << id << '\n';
    }

    ~Resource(){
        std::cout << "Destroyec: " << id << '\n';
    }

    int id;
};

int* createValue(int value){
    return new int{value};
}

void destroyValue(int*& ptr){
    delete ptr;
    ptr = nullptr;
}

// Allocation -> Construction -> Use -> Destruction -> Deallocation
int main(){
    
    // 1. Dynamic allocation of a single object

    int* p = createValue(100);

    std::cout << *p << '\n';

    *p = 200;

    std::cout << *p << '\n';

    destroyValue(p);
    
    std::cout << std::boolalpha << (p == nullptr) << '\n';

    std::cout << "--- --- --- --- --- --- ---\n";

    // 2. Dynamic array

    constexpr std::size_t n = 5;

    int* values = new int[n]{};

    for(std::size_t i=0; i < n; ++i){
        //values[i] = static_cast<int>(i * 10);
        *(values + i) = static_cast<int>(i * 10);
    }

    for(std::size_t i=0; i < n; ++i){
        //std::cout << values[i] << ' ';
        std::cout << *(values + i) << ' ';
    }
    std::cout << '\n';

    //delete values; // -> provoca comportamiento indefinido
    delete[] values;

    std::cout << "--- --- --- --- --- --- ---\n";

    // 3. Construction and Destruction

    Resource* resource = new Resource{42};

    std::cout << resource->id << '\n';

    delete resource;
    resource = nullptr;

    std::cout << "--- --- --- --- --- --- ---\n";

    // EXCEPCIONES DE ASIGNACIÓN
    // por defecto si la asignación realizada por `new` no puede obtener memoria, normalmente lanza `std::bad_alloc`
    // Existe una versión `nothrow`

    int* ptr = new (std::nothrow) int{42};

    if(ptr == nullptr){
        return 1;
    }

    delete ptr;

    return 0;
}