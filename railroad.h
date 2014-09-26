#ifndef RAILROAD_H
#define RAILROAD_H
#include "propiedad.h"
#include <QString>

class Railroad: public Propiedad{
private:
    int renta;
public:
    Railroad();
    Railroad(QString,int,bool,bool,int,int,int,int,bool,bool,int);
    Railroad(const Railroad&);
    virtual~Railroad();
    void setRenta(int);
    int getRenta()const;
    virtual void establecerRenta();
};

#endif // RAILROAD_H
