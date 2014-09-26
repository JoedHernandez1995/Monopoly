#include "propiedadesdialog.h"
#include "ui_propiedadesdialog.h"
#include "propiedadnormal.h"
#include "railroad.h"
#include "servicio.h"

PropiedadesDialog::PropiedadesDialog(vector<Propiedad*> propiedades,QWidget *parent,QString name) :
    QDialog(parent),
    ui(new Ui::PropiedadesDialog)
{
    ui->setupUi(this);
    ui->player->setText(name);
    properties = propiedades;
    llenarTabla();
}

PropiedadesDialog::~PropiedadesDialog()
{
    delete ui;
}

void PropiedadesDialog::setProperties(vector<Propiedad*> prop){
    properties = prop;
}

vector<Propiedad*> PropiedadesDialog::getProperties(){
    return properties;
}

void PropiedadesDialog::llenarTabla(){
    ui->tabla->setColumnCount(6);
    ui->tabla->setHorizontalHeaderItem(0,new QTableWidgetItem("Nombre"));
    ui->tabla->setHorizontalHeaderItem(1,new QTableWidgetItem("Tipo"));
    ui->tabla->setHorizontalHeaderItem(2,new QTableWidgetItem("Renta"));
    ui->tabla->setHorizontalHeaderItem(3,new QTableWidgetItem("Precio"));
    ui->tabla->setHorizontalHeaderItem(4,new QTableWidgetItem("Hipoteca"));
    ui->tabla->setHorizontalHeaderItem(5,new QTableWidgetItem("Hipotecada"));
    while(ui->tabla->rowCount() != 0){
        ui->tabla->removeRow(0);
    }
    ui->tabla->setRowCount(properties.size());
    for(int i = 0; i < properties.size();i++){
        ui->tabla->setItem(i,0,new QTableWidgetItem(properties[i]->getNombre()));
        if(typeid(*properties[i]) == typeid(PropiedadNormal)){
            ui->tabla->setItem(i,1,new QTableWidgetItem("Propiedad Normal"));
            PropiedadNormal* prop;
            prop = dynamic_cast<PropiedadNormal*>(properties[i]);
            ui->tabla->setItem(i,2,new QTableWidgetItem(QString::number(prop->getRenta())));
        }
        if(typeid(*properties[i]) == typeid(Railroad)){
            Railroad* rail;
            rail = dynamic_cast<Railroad*>(properties[i]);
            ui->tabla->setItem(i,1,new QTableWidgetItem("Ferrocarril"));
            ui->tabla->setItem(i,2,new QTableWidgetItem(QString::number(rail->getRenta())));
        }
        if(typeid(*properties[i]) == typeid(Servicio)){
            Servicio* serv;
            serv = dynamic_cast<Servicio*>(properties[i]);
            ui->tabla->setItem(i,1,new QTableWidgetItem("Servicio"));
            ui->tabla->setItem(i,2,new QTableWidgetItem(QString::number(serv->getRenta())));
        }
        ui->tabla->setItem(i,3,new QTableWidgetItem(QString::number(properties[i]->getPrecio())));
        ui->tabla->setItem(i,4,new QTableWidgetItem(QString::number(properties[i]->getValorHipoteca())));
        if(properties[i]->isHipotectado()){
            ui->tabla->setItem(i,5,new QTableWidgetItem("Si"));
        } else {
            ui->tabla->setItem(i,5,new QTableWidgetItem("No"));
        }
    }
}

void PropiedadesDialog::on_pushButton_clicked()
{
    this->close();
    this->setModal(false);
    this->setVisible(false);
}
