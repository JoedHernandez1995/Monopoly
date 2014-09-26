#ifndef COMMUNITYCHESTDIALOG_H
#define COMMUNITYCHESTDIALOG_H

#include <QDialog>

namespace Ui {
class CommunityChestDialog;
}

class CommunityChestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommunityChestDialog(QWidget *parent = 0,QString = "");
    ~CommunityChestDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CommunityChestDialog *ui;
};

#endif // COMMUNITYCHESTDIALOG_H
