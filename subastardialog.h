#ifndef SUBASTARDIALOG_H
#define SUBASTARDIALOG_H

#include <QDialog>

namespace Ui {
class SubastarDialog;
}

class SubastarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SubastarDialog(QWidget *parent = 0,QString = "");
    ~SubastarDialog();
    void setNuevoPrecio(int);
    int getNuevoPrecio();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SubastarDialog *ui;
    int nuevoPrecio;
};

#endif // SUBASTARDIALOG_H
