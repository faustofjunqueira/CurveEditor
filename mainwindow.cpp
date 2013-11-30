#include <QColor>
#include <QToolButton>
#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "algorithms.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bufferCanvas = QImage(769,539, QImage::Format_ARGB32);
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

    QPen pen = QPen(QColor(255,255,255));
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(5);
    QPainter painter(&bufferCanvas);
    painter.setPen(pen);
    QPoint p0 = QPoint(100,300),
            p1 = QPoint(150,150),
            p2 = QPoint(200,300),
            p3 = QPoint(300,150);
    AlgorithmHermite(&painter,p0,p1,p2,p3);

    this->interfaceUpdate();
}

void MainWindow::interfaceUpdate(void)
{
    ui->Canvas->setPixmap(QPixmap::fromImage(bufferCanvas));
    update();
}
