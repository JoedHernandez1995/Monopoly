#include "subastardialog.h"
#include "ui_subastardialog.h"
#include <QMessageBox>

SubastarDialog::SubastarDialog(QWidget *parent, QString price) :
    QDialog(parent),
    ui(new Ui::SubastarDialog)
{
    ui->setupUi(this);
    ui->original_Price->setText(price);
}

SubastarDialog::~SubastarDialog()
{
    delete ui;
}

void SubastarDialog::setNuevoPrecio(int price){
    nuevoPrecio = price;
}

int SubastarDialog::getNuevoPrecio(){
    return nuevoPrecio;
}

void SubastarDialog::on_pushButton_clicked()
{
    nuevoPrecio = ui->newPrice->text().toInt();
    int oldPrice = ui->original_Price->text().toInt();
    if(nuevoPrecio < oldPrice){
        QMessageBox m;
        m.setText("El valor nuevo tiene que ser mayor o igual al original");
        m.exec();
    }else{
        this->close();
        this->setModal(false);
        this->setVisible(false);
    }
}
