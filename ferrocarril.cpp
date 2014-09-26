#include "ferrocarril.h"

Ferrocarril::Ferrocarril(){

}

Ferrocarril::Ferrocarril(const QString type,const QString propertyType,const QString name,const int mortage,const int renta,bool two,bool three,bool four):TarjetaPropiedad(type,propertyType,name,mortage){
    valorRenta = renta;
    ownerOf2 = two;
    ownerOf3 = three;
    ownerOf4 = four;
}

Ferrocarril::Ferrocarril(const Ferrocarril& railroad):TarjetaPropiedad(railroad){
    valorRenta = railroad.valorRenta;
    ownerOf2 = railroad.ownerOf2;
    ownerOf3 = railroad.ownerOf3;
    ownerOf4 = railroad.ownerOf4;
}

Ferrocarril::~Ferrocarril(){

}

/*Metodos Mutadores*/
void Ferrocarril::setValorRenta(int rent){
    valorRenta = rent;
}

int Ferrocarril::getValorRenta()const{
    return valorRenta;
}

void Ferrocarril::setOwnerOf2(bool two){
    ownerOf2 = two;
}

bool Ferrocarril::isOwnerOf2(){
    return ownerOf2;
}

void Ferrocarril::setOwnerOf3(bool three){
    ownerOf3 = three;
}

bool Ferrocarril::isOwnerOf3(){
    return ownerOf3;
}

void Ferrocarril::setOwnerOf4(bool four){
    ownerOf4 = four;
}

bool Ferrocarril::isOwnerOf4(){
    return ownerOf4;
}

QString Ferrocarril::getNombre()const{
    return nombre;
}

int Ferrocarril::getValorHipoteca()const{
    return valorHipotecta;
}
