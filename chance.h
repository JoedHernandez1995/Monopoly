#ifndef CHANCE_H
#define CHANCE_H
#include <QString>

class Chance{
private:
    int codigo;
    QString descripcion;
public:
    Chance();
    Chance(int, QString);
    Chance(const Chance&);
    ~Chance();
    void setCode(int);
    int getCode()const;
    void setDescripcion(QString);
    QString getDescripcion()const;
};

#endif // CHANCE_H
