#ifndef PROPIEDAD_H
#define PROPIEDAD_H
#include <vector>
#include <QPixmap>
#include <QString>

class Propiedad{
protected:

    QString nombre;
    QPixmap foto;
    int posicion;
    bool hipotecado;
    bool EnVenta;
    int valorHipoteca;
    int precio;
    int x;
    int y;
    bool playerOneOwner;
    bool playerTwoOwner;

public:
    Propiedad();
    Propiedad(QString,int,bool,bool,int,int,int,int,bool,bool);
    Propiedad(const Propiedad&);
    virtual~Propiedad();

    void setFoto(QPixmap);
    QPixmap getFoto()const;
    void setNombre(QString);
    QString getNombre()const;
    void setPosicion(int);
    int getPosicion()const;
    void setHipotecado(bool);
    bool isHipotectado()const;
    void setEnVenta(bool);
    bool isEnVenta()const;
    void setValorHipoteca(int);
    int getValorHipoteca()const;
    void setPrecio(int);
    int getPrecio()const;
    void setX(int);
    int getX()const;
    void setY(int);
    int getY()const;
    void setPlayerOneOwner(bool);
    bool isPlayerOneOwner()const;
    void setPlayerTwoOwner(bool);
    bool isPlayerTwoOwner()const;
    virtual void establecerRenta();
};

#endif // PROPIEDAD_H
