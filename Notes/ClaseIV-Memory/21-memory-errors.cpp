/*
1. Aliasing -> Two or more pointers refer to the same object.

2. Dangling pointer -> A pointer refers to an object that no longer exists.

3. Use-after-free -> Accessing an object after its memory has been released.

4. Memory leak -> Allocated memory is never properly released.

5. Double free -> Releasing the same memory allocation twice.

6. Buffer overflow -> Accessing memory outside the permitted boundaries.

7. Uninitialized read -> Reading a variable before it has been initialized.
*/
#include <iostream>
#include <vector>

#include <memory> // -> std::make_unique

// 1. ALIASING AND DANGLING POINTERS
void demostrateAliasing(){
    int* owner = new int{42};
    // both pointers refer to the same memory location
    int* observer = owner;

    std::cout << *owner << '\n'; //42
    std::cout << *observer << '\n'; //42

    // Release the allocated memory
    delete owner;

    // observer still contains the old memory address. It's now a DANGLING POINTER

    owner = nullptr;
    observer = nullptr;
}

// 2. SAFE VECTOR ACCESS
void safeVector(){
    std::vector<int> values{10,20,30};

    
    try{
        // at() checks whether the index is valid
        std::cout << values.at(5) << '\n';
    }catch(const std::out_of_range& e) {
        std::cerr << e.what() << '\n';
    }
}


// 3. SAFE MEMORY OWNERSHIP
void safeOwnership(){

    // `unique_ptr` automatically manages allocated memory.
    auto value = std::make_unique<int>(42);

    std::cout << *value << '\n';

    // No delete is necessary. Memory is automatically released when value goes out of scope
}

int main(){
    std::cout << "\n--- ALIASING ---\n";
    demostrateAliasing();

    std::cout << "\n--- SAFE VECTOR ---\n";
    safeVector();

    std::cout << "\n--- SAFE OWNERSHIP ---\n";
    safeOwnership();

    return 0;
}

/*
`new` -> Dynamically allocates memory.

`delete` -> Releases dynamically allocated memory.

`nullptr` -> Represents a null pointer.

`std::unique_ptr` -> Automatically manages exclusive ownership

`std::make_unique` -> Creates a `unique_ptr` safely and conveniently.

`.at()` -> Accesses an element with bound checking

`.at()` throws `std::out_of_range`. Using [] with an invalid index causes undefined behavior
*/