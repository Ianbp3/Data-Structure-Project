#include "programm.h"
#include "ui_programm.h"
#include "newlistdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string stringify(Node*, string = "");
Node* parseP(const string& str);
Node* parseRecursivaP(char*, char*, Node*);

ProgramM::ProgramM(QString name, ListaEnlazada listO, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgramM)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    ui->NewListB->setIcon(QIcon("C:/Users/kevin/Documents/QtProjects/VisualizadorListasEnlazadas/mas.png"));
    ui->NewListB->setIconSize(QSize(16,16));
    ui->SaveListB->setIcon(QIcon("C:/Users/kevin/Documents/QtProjects/VisualizadorListasEnlazadas/disco.png"));
    ui->SaveListB->setIconSize(QSize(16,16));
    ui->EditListB->setIcon(QIcon("C:/Users/kevin/Documents/QtProjects/VisualizadorListasEnlazadas/editar.png"));
    ui->EditListB->setIconSize(QSize(16,16));

    ui->NameListLabel->setText(name);

    this->list = listO;

    drawNodes();
    FillComboB();
}

ProgramM::~ProgramM()
{
    delete ui;
}

void ProgramM::FillComboB(){
    ui->listComboB->clear();
    Node* iteratorNode = list.head;
    while(iteratorNode != nullptr){
        ui->listComboB->addItem(QString::number(iteratorNode->value));
        iteratorNode = iteratorNode->next;
    }
}

void ProgramM::drawNodes(){
    int x = scene->width()/2;
    int y = 50;
    scene->clear();

    if(list.head != nullptr){

        Node* iteratorNode = list.head;
        const QFont* font = new QFont("Helvetica [Cronyx]", 16, QFont::Bold);

        QGraphicsRectItem* rect = scene->addRect(QRectF(x,y,100,100));
        rect->setBrush(QColor(102,255,204));

        QGraphicsTextItem* text = scene->addText(QString::number(iteratorNode->value), *font);

        QGraphicsLineItem* line = scene->addLine(QLine(x+50, y+100, x+50, y+130));
        QGraphicsLineItem* arrow1 = scene->addLine(QLine(x+50, y+130, x+55, y+130-sqrt(50)));
        QGraphicsLineItem* arrow2 = scene->addLine(QLine(x+50, y+130, x+45, y+130-sqrt(50)));

        text->setPos(x+40, y+35);
        y = y + 130;
        iteratorNode = iteratorNode->next;

        while(iteratorNode != nullptr){
            QGraphicsRectItem* rect = scene->addRect(QRectF(x,y,100,100));
            rect->setBrush(QColor(102,153,255));

            QGraphicsTextItem* text = scene->addText(QString::number(iteratorNode->value), *font);

            QGraphicsLineItem* line = scene->addLine(QLine(x+50, y+100, x+50, y+130));
            QGraphicsLineItem* arrow1 = scene->addLine(QLine(x+50, y+130, x+55, y+130-sqrt(50)));
            QGraphicsLineItem* arrow2 = scene->addLine(QLine(x+50, y+130, x+45, y+130-sqrt(50)));

            text->setPos(x+40, y+35);
            y = y + 130;
            iteratorNode = iteratorNode->next;
        }

        QGraphicsTextItem* textnull = scene->addText("nullptr", *font);
        textnull->setDefaultTextColor(Qt::red);
        textnull->setPos(x+17, y);

    }
}

void ProgramM::on_addButton_clicked()
{
    QString numberS = ui->insertEditLine->text();
    bool ok;
    int nummer = numberS.toInt(&ok);
    if(ok){
        list.insertNode(numberS.toInt());
        ui->listComboB->addItem(numberS);
        ui->insertEditLine->setText("");
        drawNodes();
    }else{
        QMessageBox::warning(this, "WARNING", "That is not an integer");
    }

}


void ProgramM::on_listComboB_currentTextChanged(const QString &arg1)
{
    ui->deleteEditLine->setText(arg1);
}


void ProgramM::on_deleteButton_clicked()
{
    QString numberS = ui->deleteEditLine->text();

    if(numberS == "")
        return;

    if(list.searchNode(numberS.toInt()) != nullptr){
        list.deleteNode(numberS.toInt());
        FillComboB();
        drawNodes();
    }else{
        QMessageBox::warning(this, "WARNING", "Node not found");
    }
}


void ProgramM::on_searchButton_clicked()
{
    QString numberS = ui->searchEditLine->text();
    if(numberS == "")
        return;

    bool ok;
    int nummer = numberS.toInt(&ok);

    if(ok){
        if(list.searchNode(numberS.toInt()) != nullptr)
            QMessageBox::about(this, "FOUND!", "There's a value like that :)");
        else
            QMessageBox::warning(this, "NOT FOUND!", "There's not a value like that :(");
    }else{
        QMessageBox::warning(this, "WARNING", "That is not an integer");
    }
}


void ProgramM::on_SaveListB_clicked()
{
    QString Qdir = ui->NameListLabel->text() + ".dat";
    string dir = Qdir.toStdString();
    ofstream fw("C:/Users/kevin/Documents/QtProjects/VisualizadorListasEnlazadas/" + dir, ofstream::out);

    if(fw.is_open()){
        fw << ui->NameListLabel->text().toStdString() << "\n";
        fw << stringify(list.head)<<"\n";

        fw.close();

         QMessageBox::about(this, "Lista Guardada", "La lista se ha guardado exitosamente!");
    }else{
        cout << "No se pudo bro...";
    }
}

string stringify(Node* next, string listS) {
    if (next != nullptr) {
        listS = listS + to_string(next->value) +  " -> ";
        return stringify(next->next, listS);
    }

    listS = listS + "nullptr";
    return listS;
}

void ProgramM::on_NewListB_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Quitting...", "Are you sure you want to close this list to create a new one?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        NewListDialog CreateListD;
        CreateListD.setWindowTitle("Creating List");
        CreateListD.setModal(true);
        this->close();
        CreateListD.exec();
    }
}


void ProgramM::on_EditListB_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Quitting...", "Are you sure you want to close this list to open another one?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QString filename = QFileDialog::getOpenFileName(this, tr("Open List"), "C:/Users/kevin/Documents/QtProjects/VisualizadorListasEnlazadas", tr("Lists (*.dat)"));
        QString newlistname = filename;

        fstream file;

        file.open(filename.toStdString(), ios::in);

        if(file.is_open()){
            string line;
            string listname;
            getline(file, listname);
            getline(file, line);
            Node* headtemp = parseP(line);

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
}

Node* parseP(const string& str) {
    char* nextToken;
    const int size = str.length();
    char* str2 = new char[size + 1];
    strcpy_s(str2, size + 1, str.c_str());
    char* tok = strtok_s(str2, " -> ", &nextToken);

    Node* node = new Node(atoi(tok));

    tok = strtok_s(NULL, " -> ", &nextToken);

    return parseRecursivaP(tok, nextToken, node);
}

Node* parseRecursivaP(char* tok, char* next, Node* head) {
    if (tok != NULL) {
        if (atoi(tok) != atoi("nullptr")) {
            Node* newNode = new Node(atoi(tok));

            Node* iteratorNode = head;
            while (iteratorNode->next != nullptr) {
                iteratorNode = iteratorNode->next;
            }
            iteratorNode->next = newNode;

            tok = strtok_s(NULL, " -> ", &next);

            return parseRecursivaP(tok, next, head);
        }

    }

    return head;
}
