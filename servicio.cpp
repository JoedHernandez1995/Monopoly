#include "servicio.h"

Servicio::Servicio(){

}

Servicio::Servicio(const Servicio& service): Propiedad(service){
    renta = service.renta;
}

Servicio::Servicio(QString name, int position, bool mortage, bool sale, int morVal, int price, int X, int Y, bool one, bool two, int rent):Propiedad(name,position,mortage,sale,morVal,price,X,Y,one,two){
    renta = rent;
}

Servicio::~Servicio(){

}

void Servicio::setRenta(int rent){
    renta = rent;
}

int Servicio::getRenta()const{
    return renta;
}

void Servicio::establecerRenta(){
    renta = 200;
}
