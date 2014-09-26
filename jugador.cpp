#include "jugador.h"
#include <QMessageBox>

Jugador::Jugador(){

}

Jugador::Jugador(const Jugador& player){
    nombre = player.nombre;
    propiedades = player.propiedades;
    dinero = player.dinero;
    posicion = player.posicion;
    enCarcel = player.enCarcel;
    ferrocarriles = player.ferrocarriles;
    servicios = player.servicios;
}

Jugador::Jugador(QString name,int position){
    nombre = name;
    dinero = 1500;
    posicion = position;
    enCarcel = false;
    JailFree = false;
    ferrocarriles = 0;
    servicios = 0;
}

Jugador::~Jugador(){

}

void Jugador::setNombre(QString name){
    nombre = name;
}

QString Jugador::getNombre()const{
    return nombre;
}

void Jugador::setDinero(int money){
    dinero = money;
}

int Jugador::getDinero(){
    return dinero;
}

void Jugador::setPosicion(int position){
    posicion = position;
}

int Jugador::getPosicion()const{
    return posicion;
}
void Jugador::setEnCarcel(bool jail){
    enCarcel = jail;
}

bool Jugador::isEnCarcel()const{
    return enCarcel;
}

void Jugador::comprar(int money){
    if(dinero <= 0){
        dinero = 0;
    } else {
        dinero -= money;
    }
}
void Jugador::pagar(int money){
    if(dinero <= 0){
        dinero = 0;
    } else {
        dinero -= money;
    }
}

void Jugador::recolectar(int money){
    dinero += money;
}

void Jugador::avanzar(int spaces){
    if((posicion + spaces) > 40){
        QMessageBox m;
        m.setText("Ha Pasado por la Salida, el banco le da 200$!");
        m.exec();
        dinero += 200;
        int a = (posicion+spaces)-40;
        posicion = a;
    } else {
        posicion += spaces;
    }
}

void Jugador::setJailFree(bool card){
    JailFree = card;
}

bool Jugador::isJailFree(){
    return JailFree;
}

void Jugador::setFerrocarriles(int railroads){
    ferrocarriles = railroads;
}

int Jugador::getFerrocarriles()const{
    return ferrocarriles;
}
void Jugador::setServicios(int services){
    servicios = services;
}

int Jugador::getServicios()const{
    return servicios;
}
