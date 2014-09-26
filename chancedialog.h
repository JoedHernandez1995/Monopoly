#ifndef CHANCEDIALOG_H
#define CHANCEDIALOG_H
#include <QString>
#include <QDialog>

namespace Ui {
class ChanceDialog;
}

class ChanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChanceDialog(QWidget *parent = 0,QString = "");
    ~ChanceDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChanceDialog *ui;
};

#endif // CHANCEDIALOG_H
