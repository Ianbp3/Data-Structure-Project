#include "mainwindow.h"
#include "programm.h"
#include "newlistdialog.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Node* parse(const string& str);
Node* parseRecursiva(char*, char*, Node*);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QMessageBox::about(this, "Message", "No");
}


void MainWindow::on_NewListB_clicked()
{
    NewListDialog CreateListD;
    CreateListD.setWindowTitle("Creating List");
    CreateListD.setModal(true);
    CreateListD.exec();
}

void MainWindow::on_ExitB_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Quiting...", "Are you sure you want to close this program?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QApplication::quit();
    }
}

void MainWindow::on_OpenListB_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open List"), "C:/Users/kevin/Documents/QtProjects/VisualizadorListasEnlazadas", tr("Lists (*.dat)"));
    QString newlistname = filename;

    fstream file;

    file.open(filename.toStdString(), ios::in);

    if(file.is_open()){
        string line;
        string listname;
        getline(file, listname);
        getline(file, line);
        Node* headtemp = parse(line);

        file.close();

        ListaEnlazada listTemp;
        listTemp.head = headtemp;

        ProgramM listPage(QString::fromStdString(listname), listTemp);
        listPage.setWindowTitle(QString::fromStdString(listname));
        listPage.setModal(true);
        this->setVisible(false);
        listPage.exec();

        this->setVisible(true);

    }

}

Node* parse(const string& str) {
    char* nextToken;
    const int size = str.length();
    char* str2 = new char[size + 1];
    strcpy_s(str2, size + 1, str.c_str());
    char* tok = strtok_s(str2, " -> ", &nextToken);

    Node* node = new Node(atoi(tok));

    tok = strtok_s(NULL, " -> ", &nextToken);

    return parseRecursiva(tok, nextToken, node);
}

Node* parseRecursiva(char* tok, char* next, Node* head) {
    if (tok != NULL) {
        if (atoi(tok) != atoi("nullptr")) {
            Node* newNode = new Node(atoi(tok));

            Node* iteratorNode = head;
            while (iteratorNode->next != nullptr) {
                iteratorNode = iteratorNode->next;
            }
            iteratorNode->next = newNode;

            tok = strtok_s(NULL, " -> ", &next);

            return parseRecursiva(tok, next, head);
        }

    }

    return head;
}
