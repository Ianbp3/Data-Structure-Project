#ifndef NEWLISTDIALOG_H
#define NEWLISTDIALOG_H

#include <QDialog>

namespace Ui {
class NewListDialog;
}

class NewListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewListDialog(QWidget *parent = nullptr);
    ~NewListDialog();

private slots:
    void on_CreateListButton_clicked();

private:
    Ui::NewListDialog *ui;
};

#endif // NEWLISTDIALOG_H
