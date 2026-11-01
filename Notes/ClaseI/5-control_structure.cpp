#include <iostream>

#include <vector>

void number_to_dayOfWeek(int number);

template <typename T>
void print_vector(const std::vector<T>& vector){
    for(const T& e : vector){
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

int main(){
    int number = 5;
    number_to_dayOfWeek(number);
    
    // --> Array <--
    int numbers_array[3] = {10,20,30};

    for(int i=0; i<sizeof(numbers_array)/sizeof(numbers_array[0]); ++i){
        std::cout << numbers_array[i] << " ";
    }
    std::cout << std::endl;

    // ---> Range-based `for` <---
    std::vector<int> numbers{10,20,30};

    std::cout << numbers.size() << std::endl;

    // for(int i=0; i<numbers.size(); ++i){
    //     std::cout << numbers[i] << " ";
    // }
    // std::cout << std::endl;

    for(int number : numbers){
        std::cout << number << " ";
    }
    std::cout << std::endl;

    // EJEMPLO IMPORTANTE ACERCA DE MEMORIA
    std::vector<char> letters{'a','b','c'};

    // `for` creando una copia
    for(char value : letters){
        value = toupper(value);
    }

    print_vector(letters);

    // `for` modificando el valor de cada elemento
    for(char &value : letters){
        value = toupper(value); // casteo implícito a `int` y luego a `char`
    }

    print_vector(letters);

    return 0;
}

void number_to_dayOfWeek(int number){
    switch(number){
        case 1:
            std::cout << "Monday" << std::endl;
            break;
        case 2:
            std::cout << "Tuesday" << std::endl;
            break;
        case 3:
            std::cout << "Wednesday" << std::endl;
            break;
        case 4:
            std::cout << "Thursday" << std::endl;
            break;
        case 5:
            std::cout << "Friday" << std::endl;
            break;
        case 6:
            std::cout << "Saturday" << std::endl;
            break;
        case 7:
            std::cout << "Sunday" << std::endl;
            break;
        default:
            std::cout << "Invalid option" << std::endl;
            break;
    }
}