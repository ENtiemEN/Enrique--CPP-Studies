#include <iostream>

#include <memory>
#include <utility>

struct Resource{
    explicit Resource(int id) : id{id}{
        std::cout << "Constructed: " << id << '\n';
    }

    ~Resource(){
        std::cout << "\nDestroyed: " << id << '\n';
    }

    int id;
};

// Ownership transfer
std::unique_ptr<Resource> createResource(int id){
    return std::make_unique<Resource>(id);
}

// Non-Owning access
void inspect(const Resource& resource){
    std::cout << "Resource ID: " << resource.id << '\n';
}

int main(){
    // === 1. Exclusive ownership ===
    auto owner = createResource(1);

    inspect(*owner);

    // Move ownership
    auto newOwner = std::move(owner);

    std::cout << std::boolalpha;
    std::cout << "Old owner empty: " << (owner == nullptr) << '\n';

    inspect(*newOwner);

    std::cout << "\n--- --- --- --- --- ---\n";
    // === 2. Shared ownership ===

    auto shared1 = std::make_shared<Resource>(2); // creates a `Resource` object with ID 2. `shared1` becomes the owner of that object. The object has one owner
    // One shared pointer owns the resource

    {
        auto shared2 = shared1;

        std::cout << "Owners: " << shared1.use_count() << '\n'; // 2

        // `use_count()` -> tells you how many `shared_ptr` objects currently share ownership of the resource.
    
    } // variable `share2` is destroyed automatically. Since `shared2` is a `shared_ptr` its ownership is released.

    // The `Resource` is not destroyed because the `shared1` still owns it.
    std::cout << "Owners: " << shared1.use_count() << '\n'; // 1

    std::cout << "\n--- --- --- --- --- ---\n";
    // === 3. Non-owning observation ===
    std::weak_ptr<Resource> observer = shared1;
    // `std::weak_ptr` -> observes the object but does not own it.

    /* Observation:
        Imagine you have two objects that reference each other.
        If both use `shared_ptr` they can keep each other alive forever, even when nobody else needs them. This is a CIRCULAR REFERENCE.

        Usin `weak_ptr` for one of thoso references can prevent this problem

        A `weak_ptr` does NOT increas the `use_count()`
    */

    /* .lock() -> attemps to obtain a `shared_ptr` from the `weak_ptr`
    
    case1  -> returns a valid `shared_ptr` | case2 -> returns an empty `shared_ptr` (`nullptr`)

    When `.lock()` succeeds, the new `shared_ptr` TEMPORARILY increases the ownership count
    */
    // SMART POINTERS can be implicitly coverted to `bool`
    if(auto locked = observer.lock()){
        // `locked` is a `std::shared_ptr<Resource>`
        inspect(*locked);
    }

    shared1.reset(); // 0 owners

    std::cout << "Expired: " << observer.expired() << '\n';



    return 0;
}