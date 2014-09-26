#ifndef SERVICIO_H
#define SERVICIO_H
#include "propiedad.h"
#include <QString>

class Servicio:public Propiedad{
    int renta;
public:
    Servicio();
    Servicio(const Servicio&);
    Servicio(QString,int,bool,bool,int,int,int,int,bool,bool,int);
    virtual~Servicio();
    void setRenta(int);
    int getRenta()const;
    virtual void establecerRenta();
};

#endif // SERVICIO_H
