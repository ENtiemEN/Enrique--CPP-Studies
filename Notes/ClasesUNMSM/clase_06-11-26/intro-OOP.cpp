#include <iostream>
#include <string>

class Electrodomestico{
private:
    std::string marca;
    int precio;
public:
    std::string getMarca(){
        return this->marca = marca;
    }

    void setMarca(std::string marca){
        this->marca = marca;
    }

    int getPrecio(){
        return this->precio = precio;
    }

    void setPrecio(int precio){
        this->precio = precio;
    }
};

class Cocina : public Electrodomestico{
private:
    int temperatura;

public:
    Cocina(int temperatura){
        setTemperatura(temperatura);
    }

    int getTemperatura(){
        return this->temperatura;
    }

    void setTemperatura(int temperatura){
        if(temperatura <= 0){
            this->temperatura = 0;
        } else if(temperatura > 100){
            this->temperatura = 100;
        } else{
            this->temperatura = temperatura;
        }
    }
};

int main(){
    Cocina cocina(10);

    std::cout << cocina.getTemperatura() << '\n';
    
    cocina.setTemperatura(1500);

    std::cout << cocina.getTemperatura() << '\n';

    cocina.setMarca("LG");
    cocina.setPrecio(400);

    std::cout << cocina.getMarca() << '\n';
    std::cout << cocina.getPrecio() << '\n';

    return 0;
}