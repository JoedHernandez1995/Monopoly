#ifndef PROPIEDADESDIALOG_H
#define PROPIEDADESDIALOG_H
#include "propiedad.h"
#include <vector>
#include <QDialog>
using namespace std;
namespace Ui {
class PropiedadesDialog;
}

class PropiedadesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropiedadesDialog(vector<Propiedad*>,QWidget *parent = 0,QString = "");
    ~PropiedadesDialog();
    void setProperties(vector<Propiedad*>);
    vector<Propiedad*> getProperties();
    void llenarTabla();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PropiedadesDialog *ui;
    vector<Propiedad*> properties;
};

#endif // PROPIEDADESDIALOG_H
