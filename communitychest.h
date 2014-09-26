#ifndef COMMUNITYCHEST_H
#define COMMUNITYCHEST_H
#include <QString>

class CommunityChest{
    char codigo;
    QString descripcion;
public:
    CommunityChest();
    CommunityChest(char,QString);
    CommunityChest(const CommunityChest&);
    ~CommunityChest();
    void setCodigo(char);
    char getCodigo()const;
    void setDescripcion(QString);
    QString getDescripcion();
};

#endif // COMMUNITYCHEST_H
