#include <QColor>
#include <QToolButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->createComponents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createComponents(){

    QColor bgColor= QColor(39,39,39);
    QPalette pallete;
    pallete.setColor(QPalette::Window,bgColor);

    //Usar icones nos botoes
    QToolButton *btnNew = new QToolButton;
    QToolButton *btnSave = new QToolButton;
    QToolButton *btnDrawCurve = new QToolButton;
    QToolButton *btnZoomIn = new QToolButton;
    QToolButton *btnZoomOut = new QToolButton;

    btnNew->setText("Novo");
    btnSave->setText("Salvar");
    btnDrawCurve->setText("Desenhar Curva");

    ui->ToolBarMain->addWidget(btnNew);
    ui->ToolBarMain->addWidget(btnSave);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnDrawCurve);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnZoomIn);
    ui->ToolBarMain->addWidget(btnZoomOut);


    ui->Canvas->setAutoFillBackground(true);
    ui->Canvas->setPalette(pallete);

}
