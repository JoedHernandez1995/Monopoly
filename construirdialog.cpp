#include "construirdialog.h"
#include "ui_construirdialog.h"
#include "propiedadnormal.h"
#include "propiedad.h"
#include <QMessageBox>
#include <vector>
#include <typeinfo>
using namespace std;
ConstruirDialog::ConstruirDialog(int money,bool flag, vector<Propiedad*> properties,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConstruirDialog)
{
    ui->setupUi(this);
    ui->comboPropiedades->clear();
    ui->comboPropiedadesHotel->clear();
    normales.clear();
    dinero = money;
    ui->labelDinero->setText(QString::number(money));
    bandera = flag;
    propiedades = properties;
    llenarComboBox();
}

ConstruirDialog::~ConstruirDialog()
{
    delete ui;
}

void ConstruirDialog::setDinero(int money){
    dinero = money;
}

int ConstruirDialog::getDinero(){
    return dinero;
}

void ConstruirDialog::setPropiedades(vector<Propiedad*> properties){
    propiedades = properties;
}

vector<Propiedad*> ConstruirDialog::getPropiedades(){
    return propiedades;
}

void ConstruirDialog::llenarComboBox(){
    if(bandera){
        for(int i = 0; i < propiedades.size(); i++){
            if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                PropiedadNormal* prop = dynamic_cast<PropiedadNormal*>(propiedades[i]);
                if(prop->isPlayerOneOwner()){
                    ui->comboPropiedades->addItem(prop->getNombre());
                    normales.push_back(prop);
                }
            }
        }
    } else {
        for(int i = 0; i < propiedades.size(); i++){
            if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                PropiedadNormal* prop = dynamic_cast<PropiedadNormal*>(propiedades[i]);
                if(prop->isPlayerTwoOwner()){
                    ui->comboPropiedades->addItem(prop->getNombre());
                    normales.push_back(prop);
                }
            }
        }
    }
}

void ConstruirDialog::on_pushButton_clicked()
{
    for(int i = 0; i < normales.size(); i++){
        if(ui->comboPropiedades->itemText(ui->comboPropiedades->currentIndex()) == normales[i]->getNombre()){
            int a = 0;
            a = ui->casitas->text().toInt();
            if(a > 4){
                QMessageBox m;
                m.setText("Solo puede comprar un maximo de 4 casitas");
                m.exec();
                break;
            } else {
                int b = a * normales[i]->getValorCasas();
                if(b > dinero){
                    QMessageBox m1;
                    m1.setText("No tiene suficiente dinero para comprar, compre menos casas");
                    m1.exec();
                    break;
                }else{
                    QMessageBox m2;
                    m2.setText("Gracias por su compra!");
                    m2.exec();
                    dinero -= b;
                    ui->labelDinero->setText(QString::number(dinero));
                    if(a == 4){
                        ui->comboPropiedadesHotel->addItem(normales[i]->getNombre());
                        ui->comboPropiedades->removeItem(ui->comboPropiedades->currentIndex());
                    }
                }
            }
        }
    }
}

void ConstruirDialog::on_pushButton_3_clicked()
{
    this->setVisible(false);
    this->setModal(false);
    this->close();
}
