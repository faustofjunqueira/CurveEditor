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
    btnFile = new QToolButton;

    btnBezier= new QPushButton("Bezier");
    btnHermite = new QPushButton("Hermite");    
    btnPenConfig = new QPushButton("Style");    
    btnCancelCurve = new QPushButton("Cancel");
    canvas = new MyCanvas();

    this->SetupComponents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupComponents(){

    connect(btnBezier,SIGNAL(clicked()),this,SLOT(clickBtnBezier()));
    connect(btnHermite,SIGNAL(clicked()),this,SLOT(clickBtnHermite()));
    connect(btnCancelCurve,SIGNAL(clicked()),this,SLOT(clickBtnCancelCurve()));

    //Usar icones nos botoes
    btnFile->setText("File");
    ui->ToolBarMain->addWidget(btnFile);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnPenConfig);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnBezier);
    ui->ToolBarMain->addWidget(btnHermite);
    ui->ToolBarMain->addWidget(btnCancelCurve);
    ui->LayoutCanvas->addWidget(canvas);

    btnCancelCurve->setEnabled(false);

    this->interfaceUpdate();
}

void MainWindow::interfaceUpdate(void){
    canvas->interfaceUpdate();
    btnCancelCurve->setEnabled(false);
}

void MainWindow::clickBtnBezier(){
    btnCancelCurve->setEnabled(true);
    canvas->setTypeCurve(BEZIER);    
}

void MainWindow::clickBtnHermite(){
    btnCancelCurve->setEnabled(true);
    canvas->setTypeCurve(HERMITE);
}

void MainWindow::clickBtnCancelCurve(){
    canvas->setTypeCurve(NOCURVE);
    canvas->resetCurve();
    interfaceUpdate();
}

