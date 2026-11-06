#include <iostream>

// Pass by Value
void dayOfWeek(int num){
    switch(num){
        case 1: 
            std::cout << "Lunes" << std::endl;
            break;
        case 2:
            std::cout << "Martes" << std::endl;
            break;
        case 3:
            std::cout << "Miercoles" << std::endl;
            break;
        case 4:
            std::cout << "Jueves" << std::endl;
            break;
        case 5:
            std::cout << "Viernes" << std::endl;
            break;
        case 6:
            std::cout << "Sábado" << std::endl;
            break;
        case 7:
            std::cout << "Doming" << std::endl;
            break;
        default:
        std::cout << "Numero invalido" << std::endl;
    }
}

int main(){    
    int arrayTest[] = {1,3,5,7,8,6,2,10,30,12,56,78,10,20};

    std::cout << sizeof(arrayTest) << std::endl;
    std::cout << sizeof(arrayTest[0]) << std::endl;


    for(int i=0; i < sizeof(arrayTest)/sizeof(arrayTest[0]); i++){
        std::cout << arrayTest[i] << " ";
    }
    std::cout << std::endl;

    int number;
    std::cout << "Ingrese un numero: ";
    std::cin >> number;

    dayOfWeek(number);

    return 0;
}