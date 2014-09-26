#include "communitychestdialog.h"
#include "ui_communitychestdialog.h"

CommunityChestDialog::CommunityChestDialog(QWidget *parent,QString info) :
    QDialog(parent),
    ui(new Ui::CommunityChestDialog)
{
    ui->setupUi(this);
    ui->infoArea->setText(info);
}

CommunityChestDialog::~CommunityChestDialog()
{
    delete ui;
}

void CommunityChestDialog::on_pushButton_clicked()
{
    this->close();
    this->setVisible(false);
    this->setModal(false);
}
