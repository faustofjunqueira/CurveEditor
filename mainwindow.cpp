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
    FileMenu = new QMenu;
    btnBezier= new QPushButton("Bezier");
    btnHermite = new QPushButton("Hermite");    
    btnPenConfig = new QPushButton("Style");    
    btnCancelCurve = new QPushButton("Cancel");
    btnDeleteCurve = new QPushButton("X");
    canvas = new MyCanvas(btnDeleteCurve);
    StyleWindow.setCanvas(canvas);

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
    connect(btnDeleteCurve,SIGNAL(clicked()),this,SLOT(clickDeleteCurve()));
    connect(btnPenConfig,SIGNAL(clicked()),this,SLOT(clickStyle()));

    btnFile->setMenu(FileMenu);

    //Usar icones nos botoes
    btnFile->setText("File");
    ui->ToolBarMain->addWidget(btnFile);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnPenConfig);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnBezier);
    ui->ToolBarMain->addWidget(btnHermite);
    ui->ToolBarMain->addWidget(btnCancelCurve);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnDeleteCurve);
    ui->LayoutCanvas->addWidget(canvas);

    btnCancelCurve->setEnabled(false);
    btnDeleteCurve->setEnabled(false);



    this->interfaceUpdate();
}

void MainWindow::interfaceUpdate(void){
    canvas->interfaceUpdate();    
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
    btnCancelCurve->setEnabled(false);
    interfaceUpdate();
}

void MainWindow::clickDeleteCurve(){
    canvas->deleteSelectedCurve();
    btnDeleteCurve->setEnabled(false);
    interfaceUpdate();
}

void MainWindow::clickStyle(){
    StyleWindow.show();
    interfaceUpdate();
}
