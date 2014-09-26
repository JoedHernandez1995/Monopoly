#ifndef CONSTRUIRDIALOG_H
#define CONSTRUIRDIALOG_H

#include <QDialog>
#include <vector>
#include "propiedad.h"
#include "propiedadnormal.h"
using namespace std;
namespace Ui {
class ConstruirDialog;
}

class ConstruirDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConstruirDialog(int,bool,vector<Propiedad*>,QWidget *parent = 0);
    ~ConstruirDialog();
    void setDinero(int);
    int getDinero();
    void setPropiedades(vector<Propiedad*>);
    vector<Propiedad*> getPropiedades();
    void llenarComboBox();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ConstruirDialog *ui;
    int dinero;
    bool bandera;
    vector<Propiedad*> propiedades;
    vector<PropiedadNormal*> normales;
};

#endif // CONSTRUIRDIALOG_H
