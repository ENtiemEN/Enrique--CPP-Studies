/*
    Introduction to STL (Standard Template Library) containers in C++

    A container is an object that stores an manages a collection of elements

    // std::array -> Fixed-size array.
    // std::vector -> Dynamic CONTIGOUS array.
    // std::list -> Doubly linked list.
    // std::stack -> LIFO container adapter.
    // std::queue -> FIFO container adapter.
  
    Note:
    stack and queue are container adapters, not sequence containers
*/

#include <iostream>

#include <array>
#include <vector>
#include <list>
#include <stack>
#include <queue>

#include <string>

int main() {
    // ============================
    /*  1. `std::array<T,N>`
        - Fixed size, determined at compile time.
        - Elements are stored contiguously in memory.
        - Support random access: O(1)
        - cannot grow or shrink.
        - Unlike C arrays, it provides methods such as `size()` and `at()`

        Header: `<array>`
    */
    std::cout << "\n=== std::array ===\n";
    std::array<int, 5> numbers{10,20,30,40,50};

    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << "First element: " << numbers.front() << std::endl;
    std::cout << "Last element: " << numbers.back() << std::endl;

    // Element access
    std::cout << "numbers[2]: " << numbers[2] << std::endl;
    std::cout << "numbers.at(2): " << numbers.at(2) << std::endl;

    // Difference:
    // operator[] does not perform bounds checking.
    // `at()` checks bounds and throws `std::out_of_range`

    numbers[0] = 100;

    // Range-based for.
    for(const int value : numbers){
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Fill all elements with the same value.
    numbers.fill(7);

    for(const auto value : numbers) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // ============================
    /*  2. `std::vector<T>`
        - Dynamic-size contiguous array
        - Supports random access: O(1)
        - push_back(): amortized O(1)
        - Insertion/removal in the middle: O(n)
        - Can reallocate memory when its capacity is exceeded.

        Important:
        size()      -> Number of elements
        capacity()  -> Currently alllocated element capacity

        Header: <vector>
    */

    std::cout << "\n=== std::vector ===\n";

    std::vector<int> values{10,20,30};

    // `.push_back()` -> Recibe un objeto que ya existe o una referencia a un objeto y lo copia o mueve al vector
    values.push_back(40);
    // `.emplace_back()` -> construye directamente el elemento dentro del almacenamiento del vector utilizando los agumentos que le proporcionamos
    values.emplace_back(50);

    std::cout << "Size: " << values.size() << std::endl;
    std::cout << "Capacity: " << values.capacity() << std::endl;

    std::cout << "First: " << values.front() << std::endl;
    std::cout << "Last: " << values.back() << std::endl;

    // Element access.
    values[1] = 200;

    // Remove the last element.
    values.pop_back();

    for(const auto value : values){
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Reserve memory for at least 100 elements
    // This changes capacity, NOT size
    values.reserve(100);

    std::cout << "New capacity: " << values.capacity() << std::endl;

    // Resize to 6 elements.
    // Newly added integers are initialized to zero
    values.resize(6); // change the size of the vector to 6 elements

    for(const auto value : values){
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Remove all elements.
    values.clear();

    std::cout << "Empty? " << std::boolalpha << values.empty() << std::endl;

    // ============================
    /*  3. std::list<T>
        - Double linked list.
        - Elements are NOT necessarily contigous in memory.
        - Inserton/removal at a known position: O(1)
        - Accesing the nth element equires traversal: O(n)
        - Does NOT support operator[]
        - Useful when frequent insertions and removals are required at known positions

        Header: `<list>`
    */
    std::cout << "\n=== std::list ===\n";

    std::list<int> linkedlist{10,20,30};

    linkedlist.push_front(5);
    linkedlist.push_back(40);
    
    std::cout << "First: " << linkedlist.front() << std::endl;
    std::cout << "Last: " << linkedlist.back() << std::endl;

    // Remove first and last elements.
    linkedlist.pop_front();
    linkedlist.pop_back();

    // Insert at the beginning.
    linkedlist.insert(linkedlist.begin(), 100);

    // Remove every element equal to 20
    linkedlist.remove(20);

    for(const auto value : linkedlist){
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // `std::list` has its own `sort()` method
    linkedlist.sort();

    std::cout << "Sorted: ";
    for(const auto value : linkedlist){
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // ============================
    /*  5. std::stack<T>
        - LIFO: Last In; First Out.
        - Container adapter (default underlying container: deque)
        - push(): Insert element at the top
        - top(): Access top element
        - pop(): Remove the top element
        - push(), pop(), top(): O(1) with default container

        Important:
        `pop()` does NOT return the removed element.

        Header: `<stack>`
    */
    std::cout << "\n=== std::stack ===\n";
    std::stack<int> myStack;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    
    // 30
    // 20
    // 10

    std::cout << "Top: " << myStack.top() << std::endl;

    myStack.pop();

    std::cout << "New top: " << myStack.top() << std::endl;

    for(int i=21; i<=30; i++){
        myStack.push(i);
    }

    while(!myStack.empty()){
        std::cout << myStack.top() << std::endl;
        myStack.pop();
    }
    std::cout << std::endl;

    // ============================
    /*  6. std::queue<T>
        - FIFO: First In, First Out
        - Container adapter (default underlying container: deque)
        - push(): Insert at the back
        - front(): Access first element
        - back(): Access last element
        - pop(): Remove first element
        - These operations are O(1) with default container.

        Like stack, pop() does NOT return an element.

        Header: <queue>
    */
    std::cout << "\n=== std::queue ===\n";
    std::queue<std::string> tasks;

    tasks.push("Task A");
    tasks.push("Task B");
    tasks.push("Task C");

    std::cout << "Front: " << tasks.front() << std::endl;
    std::cout << "Back: " << tasks.back() << std::endl;

    tasks.pop(); // quit A

    std::cout << "New front: " << tasks.front() << std::endl;

    // Process tasks in arrival order
    while (!tasks.empty()) {
        std::cout << "Processing: " << tasks.front() << std::endl;

        tasks.pop();
    }

    return 0;
}