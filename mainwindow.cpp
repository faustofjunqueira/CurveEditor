#include <QColor>
#include <QToolButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    btnNew = new QToolButton;
    btnOpen = new QToolButton;
    btnSave = new QToolButton;
    btnDrawCurve = new QToolButton;
    btnZoomIn = new QToolButton;
    btnZoomOut = new QToolButton;
    this->SetupComponents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupComponents(){

    QColor bgColor= QColor(39,39,39);
    QPalette pallete;
    pallete.setColor(QPalette::Window,bgColor);

    //Usar icones nos botoes

    btnNew->setText("Novo");
    btnOpen->setText("Abrir");
    btnSave->setText("Salvar");
    btnDrawCurve->setText("Desenhar Curva");
    btnZoomIn->setText("+");
    btnZoomOut->setText("-");

    ui->ToolBarMain->addWidget(btnNew);
    ui->ToolBarMain->addWidget(btnOpen);
    ui->ToolBarMain->addWidget(btnSave);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnDrawCurve);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(btnZoomIn);
    ui->ToolBarMain->addWidget(btnZoomOut);

    ui->Canvas->setAutoFillBackground(true);
    ui->Canvas->setPalette(pallete);

}
