#ifndef PROGRAMM_H
#define PROGRAMM_H

#include <QDialog>
#include "listaenlazada.h"
#include "QGraphicsView"

namespace Ui {
class ProgramM;
}

class ProgramM : public QDialog
{
    Q_OBJECT

public:
    explicit ProgramM(QString name, ListaEnlazada listO, QWidget *parent = nullptr);
    ListaEnlazada list;
    QString Nname;
    QGraphicsScene* scene;
    ~ProgramM();

    void drawNodes();
    void FillComboB();

private slots:
    void on_addButton_clicked();

    void on_listComboB_currentTextChanged(const QString &arg1);

    void on_deleteButton_clicked();

    void on_searchButton_clicked();

    void on_SaveListB_clicked();

    void on_NewListB_clicked();

    void on_EditListB_clicked();

private:
    Ui::ProgramM *ui;
};

#endif // PROGRAMM_H
