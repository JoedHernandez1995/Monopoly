#include "propiedadnormal.h"
#include <QString>

PropiedadNormal::PropiedadNormal(){

}

PropiedadNormal::PropiedadNormal(QString name,int pos,bool mor,bool sale,int morVal,int price,int x,int y,bool one,bool two,QString colour,int rent,int rentone,int renttwo,int rentthree,int rentfour,int renthot,int house,int hotel,int houses,bool hasHotel):Propiedad(name,pos,mor,sale,morVal,price,x,y,one,two){
        color = colour;
        renta = rent;
        rentaUnaCasa = rentone;
        rentaDosCasas = renttwo;
        rentaTresCasas = rentthree;
        rentaCuatroCasas = rentfour;
        rentaHotel = renthot;
        valorCasas = house;
        valorHotel = hotel;
        totalCasitas = houses;
        hotel = hasHotel;
}

PropiedadNormal::PropiedadNormal(const PropiedadNormal& normal):Propiedad(normal){
    color = normal.color;
    renta = normal.renta;
    rentaUnaCasa = normal.rentaUnaCasa;
    rentaDosCasas = normal.rentaDosCasas;
    rentaTresCasas = normal.rentaTresCasas;
    rentaCuatroCasas = normal.rentaCuatroCasas;
    rentaHotel = normal.rentaHotel;
    valorCasas = normal.valorCasas;
    valorHotel = normal.valorHotel;
    totalCasitas = normal.totalCasitas;
    hotel = normal.hotel;
}

PropiedadNormal::~PropiedadNormal(){

}

void PropiedadNormal::setColor(QString colour){
    color = colour;
}

QString PropiedadNormal::getColor()const{
    return color;
}
void PropiedadNormal::setRenta(int rent){
    renta = rent;
}

int PropiedadNormal::getRenta()const{
    return renta;
}
void PropiedadNormal::setValorCasas(int house){
    valorCasas = house;
}

int PropiedadNormal::getValorCasas()const{
    return valorCasas;
}

void PropiedadNormal::setValorHotel(int hotel){
    valorHotel = hotel;
}

int PropiedadNormal::getValorHotel(){
    return valorHotel;
}

void PropiedadNormal::setTotalCasitas(int casas){
    totalCasitas = casas;
}

int PropiedadNormal::getTotalCasitas()const{
    return totalCasitas;
}

void PropiedadNormal::setHotel(bool hotel1){
    hotel = hotel1;
}

bool PropiedadNormal::hasHotel()const{
    return hotel;
}

void PropiedadNormal::establecerRenta(){
    if(nombre == "Avenida Mediterraneo"){
        if(totalCasitas == 0){
            renta = 2;
        }else if(totalCasitas == 1){
            renta = 10;
        }else if(totalCasitas == 2){
            renta = 30;
        }else if(totalCasitas == 3){
            renta = 90;
        }else if(totalCasitas == 4){
            renta = 250;
        }else if(totalCasitas == 0 && hotel){
            renta = 250;
        }
    }
    if(nombre == "Avenida Baltica"){
        if(totalCasitas == 0){
            renta = 4;
        }else if(totalCasitas == 1){
            renta = 20;
        }else if(totalCasitas == 2){
            renta = 60;
        }else if(totalCasitas == 3){
            renta = 180;
        }else if(totalCasitas == 4){
            renta = 320;
        }else if(totalCasitas == 0 && hotel){
            renta = 450;
        }
    }
    if(nombre == "Avenida Oriental"){
        if(totalCasitas == 0){
            renta = 6;
        }else if(totalCasitas == 1){
            renta = 30;
        }else if(totalCasitas == 2){
            renta = 90;
        }else if(totalCasitas == 3){
            renta = 270;
        }else if(totalCasitas == 4){
            renta = 400;
        }else if(totalCasitas == 0 && hotel){
            renta = 550;
        }
    }
    if(nombre == "Avenida Vermont"){
        if(totalCasitas == 0){
            renta = 6;
        }else if(totalCasitas == 1){
            renta = 30;
        }else if(totalCasitas == 2){
            renta = 90;
        }else if(totalCasitas == 3){
            renta = 270;
        }else if(totalCasitas == 4){
            renta = 400;
        }else if(totalCasitas == 0 && hotel){
            renta = 550;
        }
    }
    if(nombre == "Avenida Connecticut"){
        if(totalCasitas == 0){
            renta = 8;
        }else if(totalCasitas == 1){
            renta = 40;
        }else if(totalCasitas == 2){
            renta = 100;
        }else if(totalCasitas == 3){
            renta = 300;
        }else if(totalCasitas == 4){
            renta = 450;
        }else if(totalCasitas == 0 && hotel){
            renta = 600;
        }
    }
    if(nombre == "Plaza San Carlos"){
        if(totalCasitas == 0){
            renta = 10;
        }else if(totalCasitas == 1){
            renta = 50;
        }else if(totalCasitas == 2){
            renta = 150;
        }else if(totalCasitas == 3){
            renta = 450;
        }else if(totalCasitas == 4){
            renta = 625;
        }else if(totalCasitas == 0 && hotel){
            renta = 700;
        }
    }
    if(nombre == "Avenida Status"){
        if(totalCasitas == 0){
            renta = 10;
        }else if(totalCasitas == 1){
            renta = 50;
        }else if(totalCasitas == 2){
            renta = 150;
        }else if(totalCasitas == 3){
            renta = 450;
        }else if(totalCasitas == 4){
            renta = 625;
        }else if(totalCasitas == 0 && hotel){
            renta = 750;
        }
    }
    if(nombre == "Avenida Virginia"){
        if(totalCasitas == 0){
            renta = 12;
        }else if(totalCasitas == 1){
            renta = 60;
        }else if(totalCasitas == 2){
            renta = 180;
        }else if(totalCasitas == 3){
            renta = 500;
        }else if(totalCasitas == 4){
            renta = 700;
        }else if(totalCasitas == 0 && hotel){
            renta = 900;
        }
    }
    if(nombre == "Plaza St. James"){
        if(totalCasitas == 0){
            renta = 14;
        }else if(totalCasitas == 1){
            renta = 70;
        }else if(totalCasitas == 2){
            renta = 200;
        }else if(totalCasitas == 3){
            renta = 550;
        }else if(totalCasitas == 4){
            renta = 750;
        }else if(totalCasitas == 0 && hotel){
            renta = 950;
        }
    }
    if(nombre == "Avenida Tennessee"){
        if(totalCasitas == 0){
            renta = 14;
        }else if(totalCasitas == 1){
            renta = 70;
        }else if(totalCasitas == 2){
            renta = 200;
        }else if(totalCasitas == 3){
            renta = 550;
        }else if(totalCasitas == 4){
            renta = 750;
        }else if(totalCasitas == 0 && hotel){
            renta = 950;
        }
    }
    if(nombre == "Avenida Nueva York"){
        if(totalCasitas == 0){
            renta = 16;
        }else if(totalCasitas == 1){
            renta = 80;
        }else if(totalCasitas == 2){
            renta = 220;
        }else if(totalCasitas == 3){
            renta = 600;
        }else if(totalCasitas == 4){
            renta = 800;
        }else if(totalCasitas == 0 && hotel){
            renta = 1000;
        }
    }
    if(nombre == "Avenida Kentucky"){
        if(totalCasitas == 0){
            renta = 18;
        }else if(totalCasitas == 1){
            renta = 90;
        }else if(totalCasitas == 2){
            renta = 250;
        }else if(totalCasitas == 3){
            renta = 700;
        }else if(totalCasitas == 4){
            renta = 875;
        }else if(totalCasitas == 0 && hotel){
            renta = 1050;
        }
    }
    if(nombre == "Avenida Indiana"){
        if(totalCasitas == 0){
            renta = 18;
        }else if(totalCasitas == 1){
            renta = 90;
        }else if(totalCasitas == 2){
            renta = 250;
        }else if(totalCasitas == 3){
            renta = 700;
        }else if(totalCasitas == 4){
            renta = 875;
        }else if(totalCasitas == 0 && hotel){
            renta = 1050;
        }
    }
    if(nombre == "Avenida Illinois"){
        if(totalCasitas == 0){
            renta = 20;
        }else if(totalCasitas == 1){
            renta = 100;
        }else if(totalCasitas == 2){
            renta = 300;
        }else if(totalCasitas == 3){
            renta = 750;
        }else if(totalCasitas == 4){
            renta = 925;
        }else if(totalCasitas == 0 && hotel){
            renta = 1100;
        }
    }
    if(nombre == "Avenida Atlantico"){
        if(totalCasitas == 0){
            renta = 22;
        }else if(totalCasitas == 1){
            renta = 110;
        }else if(totalCasitas == 2){
            renta = 330;
        }else if(totalCasitas == 3){
            renta = 800;
        }else if(totalCasitas == 4){
            renta = 975;
        }else if(totalCasitas == 0 && hotel){
            renta = 1150;
        }
    }
    if(nombre == "Avenida Ventnor"){
        if(totalCasitas == 0){
            renta = 22;
        }else if(totalCasitas == 1){
            renta = 110;
        }else if(totalCasitas == 2){
            renta = 330;
        }else if(totalCasitas == 3){
            renta = 800;
        }else if(totalCasitas == 4){
            renta = 975;
        }else if(totalCasitas == 0 && hotel){
            renta = 1150;
        }
    }
    if(nombre == "Jardines Marvin"){
        if(totalCasitas == 0){
            renta = 24;
        }else if(totalCasitas == 1){
            renta = 120;
        }else if(totalCasitas == 2){
            renta = 360;
        }else if(totalCasitas == 3){
            renta = 850;
        }else if(totalCasitas == 4){
            renta = 1025;
        }else if(totalCasitas == 0 && hotel){
            renta = 1200;
        }
    }
    if(nombre == "Avenida Pacifico"){
        if(totalCasitas == 0){
            renta = 26;
        }else if(totalCasitas == 1){
            renta = 130;
        }else if(totalCasitas == 2){
            renta = 390;
        }else if(totalCasitas == 3){
            renta = 900;
        }else if(totalCasitas == 4){
            renta = 1100;
        }else if(totalCasitas == 0 && hotel){
            renta = 1275;
        }
    }
    if(nombre == "Avenida Carolina del Norte"){
        if(totalCasitas == 0){
            renta = 26;
        }else if(totalCasitas == 1){
            renta = 130;
        }else if(totalCasitas == 2){
            renta = 390;
        }else if(totalCasitas == 3){
            renta = 900;
        }else if(totalCasitas == 4){
            renta = 1100;
        }else if(totalCasitas == 0 && hotel){
            renta = 1275;
        }
    }
    if(nombre == "Avenida Pennsylvania"){
        if(totalCasitas == 0){
            renta = 28;
        }else if(totalCasitas == 1){
            renta = 150;
        }else if(totalCasitas == 2){
            renta = 450;
        }else if(totalCasitas == 3){
            renta = 1000;
        }else if(totalCasitas == 4){
            renta = 1200;
        }else if(totalCasitas == 0 && hotel){
            renta = 1400;
        }
    }
    if(nombre == "Plaza Park"){
        if(totalCasitas == 0){
            renta = 35;
        }else if(totalCasitas == 1){
            renta = 175;
        }else if(totalCasitas == 2){
            renta = 500;
        }else if(totalCasitas == 3){
            renta = 1100;
        }else if(totalCasitas == 4){
            renta = 1300;
        }else if(totalCasitas == 0 && hotel){
            renta = 1500;
        }
    }
    if(nombre == "El Muelle"){
        if(totalCasitas == 0){
            renta = 50;
        }else if(totalCasitas == 1){
            renta = 200;
        }else if(totalCasitas == 2){
            renta = 600;
        }else if(totalCasitas == 3){
            renta = 1400;
        }else if(totalCasitas == 4){
            renta = 1700;
        }else if(totalCasitas == 0 && hotel){
            renta = 2000;
        }
    }
}
