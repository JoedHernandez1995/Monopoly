#ifndef PROPIEDADNORMAL_H
#define PROPIEDADNORMAL_H
#include "propiedad.h"
#include "QString"

class PropiedadNormal:public Propiedad{
private:
    QString color;
    int renta;
    int rentaUnaCasa;
    int rentaDosCasas;
    int rentaTresCasas;
    int rentaCuatroCasas;
    int rentaHotel;
    int valorCasas;
    int valorHotel;
    int totalCasitas;
    bool hotel;
public:
    PropiedadNormal();
    PropiedadNormal(QString,int,bool,bool,int,int,int,int,bool,bool,QString,int,int,int,int,int,int,int,int,int,bool);
    PropiedadNormal(const PropiedadNormal&);
    virtual~PropiedadNormal();
    void setColor(QString);
    QString getColor()const;
    void setRenta(int);
    int getRenta()const;
    void setValorCasas(int);
    int getValorCasas()const;
    void setValorHotel(int);
    int getValorHotel();
    void setTotalCasitas(int);
    int getTotalCasitas()const;
    void setHotel(bool);
    bool hasHotel()const;
    virtual void establecerRenta();
};

#endif // PROPIEDADNORMAL_H
