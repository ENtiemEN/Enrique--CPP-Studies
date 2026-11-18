/*  Problema:
Dado un `std::vector<int>` devuelve:
- `true` si algún valor aparece al menos dos veces
- `false` si todos los valores son distintos

Entrada	Resultado	Motivo

Entrada	        Resultado	Motivo
{1, 2, 3, 1}    true        Se repite 1.
{1, 2, 3, 4}    false	    Todos son distintos.
{5, 5}	        true	    Se repite 5.
{7}	            false	    Un solo elemento no puede repetirse.
{}	            false	    No hay elementos repetidos.

Buscamos si existen indices distintos tales que:
\exists i < j : values[i] = values[j]
*/

#include <vector>
#include <iostream>

/*
T(n) = O(n^2)
S_aux(n) = O(1)
*/
bool containsDuplicateBruteForce(const std::vector<int>& values){
    if(values.size() < 2){
        return false;
    }

    for(std::size_t i=0; i < values.size() - 1; i++){
        for(std::size_t j=i+1; j < values.size(); j++){
            if(values[i] == values[j]){
                return true;
            }
        }
    }
    return false;
}

int main(){

    const std::vector<int> repeated{1,2,3,1};
    const std::vector<int> unique{1,2,3,4};
    const std::vector<int> empty{};

    std::cout << std::boolalpha;

    std::cout << "Brute Force\n";
    std::cout << containsDuplicateBruteForce(repeated) << '\n';
    std::cout << containsDuplicateBruteForce(unique) << '\n';
    std::cout << containsDuplicateBruteForce(empty) << '\n';

    return 0;
}