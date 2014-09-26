#include "railroad.h"
Railroad::Railroad(){

}

Railroad::Railroad(QString name,int position,bool mortage,bool sale,int morVal,int price,int X,int Y,bool one,bool two,int rent):Propiedad(name,position,mortage,sale,morVal,price,X,Y,one,two){
    renta = rent;
}

Railroad::Railroad(const Railroad& ferrocarril):Propiedad(ferrocarril){
    renta = ferrocarril.renta;
}

Railroad::~Railroad(){

}

void Railroad::setRenta(int rent){
    renta = rent;
}

int Railroad::getRenta()const{
    return renta;
}

void Railroad::establecerRenta(){
    renta = 100;
}
