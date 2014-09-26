#ifndef HIPOTECARDIALOG_H
#define HIPOTECARDIALOG_H
#include <vector>
#include "propiedad.h"
#include <QDialog>
using namespace std;

namespace Ui {
class HipotecarDialog;
}

class HipotecarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HipotecarDialog(int,bool,vector<Propiedad*>,QWidget *parent = 0);
    void setPropiedades(vector<Propiedad*>);
    vector<Propiedad*> getPropiedades();
    void setDinero(int);
    int getDinero();
    ~HipotecarDialog();
    void llenarComboBox();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::HipotecarDialog *ui;
    vector<Propiedad*> propiedades;
    bool bandera;
    int dinero;
};

#endif // HIPOTECARDIALOG_H
