#include "chance.h"

Chance::Chance(){

}

Chance::Chance(int code, QString description){
    codigo = code;
    descripcion = description;
}

Chance::Chance(const Chance& card){
    codigo = card.codigo;
    descripcion = card.descripcion;
}

Chance::~Chance(){

}

void Chance::setCode(int code){
    codigo = code;
}

int Chance::getCode()const{
    return codigo;
}

void Chance::setDescripcion(QString description){
    descripcion = description;
}

QString Chance::getDescripcion()const{
    return descripcion;
}
