#include "newlistdialog.h"
#include "programm.h"
#include "ui_newlistdialog.h"

NewListDialog::NewListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewListDialog)
{
    ui->setupUi(this);
}

NewListDialog::~NewListDialog()
{
    delete ui;
}

void NewListDialog::on_CreateListButton_clicked()
{
    QString newlistname = ui->ListNameLineEdit->text();
    ListaEnlazada listTemp;
    ProgramM listPage(newlistname, listTemp);
    listPage.setWindowTitle(newlistname);
    listPage.setModal(true);
    this->setVisible(false);
    listPage.exec();

    this->setVisible(true);
}

