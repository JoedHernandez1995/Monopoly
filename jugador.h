#ifndef JUGADOR_H
#define JUGADOR_H
#include "propiedad.h"
#include <QString>
#include <vector>
using namespace std;

class Jugador{
private:
    QString nombre;
    vector <Propiedad> propiedades;
    int dinero;
    int posicion;
    int ferrocarriles;
    int servicios;
    bool enCarcel;
    bool JailFree;
public:
    Jugador();
    Jugador(const Jugador&);
    Jugador(QString,int);
    ~Jugador();
    void setNombre(QString);
    QString getNombre()const;
    void setDinero(int);
    int getDinero();
    void setPosicion(int);
    int getPosicion()const;
    void setEnCarcel(bool);
    bool isEnCarcel()const;
    void setFerrocarriles(int);
    int getFerrocarriles()const;
    void setServicios(int);
    int getServicios()const;
    void setJailFree(bool);
    bool isJailFree();
    void comprar(int);
    void pagar(int);
    void recolectar(int);
    void avanzar(int);
};

#endif // JUGADOR_H
