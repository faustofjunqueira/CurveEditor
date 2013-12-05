#include <QColor>
#include <QToolButton>
#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "curve.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btnNew = new QToolButton;
    btnOpen = new QToolButton;
    btnSave = new QToolButton;
    btnPenConfig = new QToolButton;
    btnBezier = new QToolButton;
    btnHermite = new QToolButton;
    canvas = new MyCanvas;

    this->SetupComponents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupComponents(){

    //Usar icones nos botoes

    btnNew->setText("Novo");
    btnOpen->setText("Abrir");
    btnSave->setText("Salvar");
    btnPenConfig->setText("Configurar Caneta");
    btnBezier->setText("Bezier");
    btnHermite->setText("Hermite");


    ui->ToolBarMain->addWidget(btnNew);
    ui->ToolBarMain->addWidget(btnOpen);
    ui->ToolBarMain->addWidget(btnSave);
    ui->ToolBarMain->addSeparator();    
    ui->ToolBarMain->addWidget(btnPenConfig);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnBezier);
    ui->ToolBarMain->addWidget(btnHermite);
    ui->LayoutCanvas->addWidget(canvas);

    this->interfaceUpdate();
}

void MainWindow::interfaceUpdate(void){
    update();
}
