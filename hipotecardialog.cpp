#include "hipotecardialog.h"
#include "ui_hipotecardialog.h"
#include <vector>
#include "propiedad.h"
#include <QMessageBox>

using namespace std;

HipotecarDialog::HipotecarDialog(int money,bool flag, vector<Propiedad*> properties,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HipotecarDialog)
{
    ui->setupUi(this);
    ui->comboPropiedades->clear();
    bandera = flag;
    dinero = money;
    ui->dineroJugador->setText(QString::number(dinero));
    propiedades = properties;
    llenarComboBox();
}

HipotecarDialog::~HipotecarDialog()
{
    delete ui;
}

void HipotecarDialog::llenarComboBox(){
    if(bandera){
        for(int i = 0; i < propiedades.size(); i++){
            if(!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner() && !propiedades[i]->isHipotectado()){
                ui->comboPropiedades->addItem(propiedades[i]->getNombre());
            }
        }
    } else {
        for(int i = 0; i < propiedades.size(); i++){
            if(!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner() && !propiedades[i]->isHipotectado()){
                ui->comboPropiedades->addItem(propiedades[i]->getNombre());
            }
        }
    }

    if(bandera){
        for(int i = 0; i < propiedades.size(); i++){
            if(!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner() && propiedades[i]->isHipotectado()){
                ui->comboHipotecadas->addItem(propiedades[i]->getNombre());
            }
        }
    } else {
        for(int i = 0; i < propiedades.size(); i++){
            if(!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner() && propiedades[i]->isHipotectado()){
                ui->comboHipotecadas->addItem(propiedades[i]->getNombre());
            }
        }
    }
}

void HipotecarDialog::on_pushButton_clicked()
{
    for(int i = 0; i < propiedades.size(); i++){
        if(propiedades[i]->getNombre() == ui->comboPropiedades->itemText(ui->comboPropiedades->currentIndex())){
            propiedades[i]->setHipotecado(true);
            ui->comboPropiedades->removeItem(ui->comboPropiedades->currentIndex());
            ui->comboHipotecadas->addItem(propiedades[i]->getNombre());
            QMessageBox m;
            m.setText("Ha Hipotecado la propiedad exitosamente");
            m.exec();
            dinero += propiedades[i]->getValorHipoteca();
            ui->dineroJugador->setText(QString::number(dinero));
        }
    }
}

void HipotecarDialog::setDinero(int money){
    dinero = money;
}

int HipotecarDialog::getDinero(){
    return dinero;
}

void HipotecarDialog::setPropiedades(vector<Propiedad*> properties){
    propiedades = properties;
}

vector<Propiedad*> HipotecarDialog::getPropiedades(){
    return propiedades;
}

void HipotecarDialog::on_pushButton_3_clicked()
{
    this->setVisible(false);
    this->setModal(false);
    this->close();
}

void HipotecarDialog::on_pushButton_2_clicked()
{
    for(int i = 0; i < propiedades.size(); i++){
        if(propiedades[i]->getNombre() == ui->comboHipotecadas->itemText(ui->comboHipotecadas->currentIndex())){
            propiedades[i]->setHipotecado(false);
            int price = propiedades[i]->getValorHipoteca();
            int isv = price * 0.10;
            int total = price + isv;
            dinero -= total;
            ui->dineroJugador->setText(QString::number(dinero));
            ui->comboPropiedades->addItem(propiedades[i]->getNombre());
            ui->comboHipotecadas->removeItem(ui->comboHipotecadas->currentIndex());
            QMessageBox m;
            m.setText("Ha Deshipotecado la Propiedad!");
            m.exec();
        }
    }
}
