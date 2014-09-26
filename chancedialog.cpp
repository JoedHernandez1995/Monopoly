#include "chancedialog.h"
#include "ui_chancedialog.h"

ChanceDialog::ChanceDialog(QWidget *parent, QString info) :
    QDialog(parent),
    ui(new Ui::ChanceDialog)
{
    ui->setupUi(this);
    ui->information_2->setText(info);
}

ChanceDialog::~ChanceDialog()
{
    delete ui;
}

void ChanceDialog::on_pushButton_clicked()
{
    this->close();
    this->setVisible(false);
    this->setModal(false);
}
