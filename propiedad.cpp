#include "propiedad.h"
#include <QString>
#include <QPixmap>

Propiedad::Propiedad(){

}

Propiedad::Propiedad(QString name,int position,bool mortage,bool sale,int mortageValue,int price,int X,int Y,bool one,bool two){
    nombre = name;
    posicion = position;
    hipotecado = mortage;
    EnVenta = sale;
    valorHipoteca = mortageValue;
    precio = price;
    x = X;
    y = Y;
    playerOneOwner = one;
    playerTwoOwner = two;
}

Propiedad::Propiedad(const Propiedad& property){
    nombre = property.nombre;
    posicion = property.posicion;
    hipotecado = property.hipotecado;
    EnVenta = property.EnVenta;
    valorHipoteca = property.valorHipoteca;
    precio = property.precio;
    x = property.x;
    y = property.y;
    playerOneOwner = property.playerOneOwner;
    playerTwoOwner = property.playerTwoOwner;
}

Propiedad::~Propiedad(){

}

void Propiedad::setNombre(QString name){
    nombre = name;
}

QString Propiedad::getNombre()const{
    return nombre;
}
void Propiedad::setPosicion(int position){
    posicion = position;
}

int Propiedad::getPosicion()const{
    return posicion;
}

void Propiedad::setHipotecado(bool mortage){
    hipotecado = mortage;
}

bool Propiedad::isHipotectado()const{
    return hipotecado;
}

void Propiedad::setEnVenta(bool onsale){
    EnVenta = onsale;
}

bool Propiedad::isEnVenta()const{
    return EnVenta;
}
void Propiedad::setValorHipoteca(int mortage){
    valorHipoteca = mortage;
}

int Propiedad::getValorHipoteca()const{
    return valorHipoteca;
}

void Propiedad::setPrecio(int price){
    precio = price;
}

int Propiedad::getPrecio()const{
    return precio;
}

void Propiedad::setX(int X){
    x = X;
}

int Propiedad::getX()const{
    return x;
}

void Propiedad::setY(int Y){
    y = Y;
}

int Propiedad::getY()const{
    return y;
}

void Propiedad::setPlayerOneOwner(bool one){
    playerOneOwner = one;
}

bool Propiedad::isPlayerOneOwner()const{
    return playerOneOwner;
}

void Propiedad::setPlayerTwoOwner(bool two){
    playerTwoOwner = two;
}

bool Propiedad::isPlayerTwoOwner()const{
    return playerTwoOwner;
}

void Propiedad::setFoto(QPixmap foto1){
    foto = foto1;
}

QPixmap Propiedad::getFoto()const{
    return foto;
}

void Propiedad::establecerRenta(){

}
