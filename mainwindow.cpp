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

    canvas = new MyCanvas(btnDeleteCurve,ui->CurveXTextEdit,ui->CurveYTextEdit,ui->CurveXTextEdit_2,ui->CurveYTextEdit_2,ui->CurveXTextEdit_3,ui->CurveYTextEdit_3,
                          ui->CurveXTextEdit_4,ui->CurveYTextEdit_4,ui->ColorField,ui->WidthField,ui->TypeCurveLabel,ui->CapStyleComboBox,ui->PenStyleComboBox,
                          ui->Label3,ui->Label4);
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
    connect(ui->ApplyButton,SIGNAL(clicked()),this,SLOT(accept()));

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

    ui->PenStyleComboBox->addItem("Qt::SolidLine");
    ui->PenStyleComboBox->addItem("Qt::DashLine");
    ui->PenStyleComboBox->addItem("Qt::DotLine");
    ui->PenStyleComboBox->addItem("Qt::DashDotLine");
    ui->PenStyleComboBox->addItem("Qt::DashDotDotLine");
    ui->PenStyleComboBox->addItem("Qt::CustomDashLine");

    ui->CapStyleComboBox->addItem("Qt::SquareCap");
    ui->CapStyleComboBox->addItem("Qt::FlatCap");
    ui->CapStyleComboBox->addItem("Qt::RoundCap");

    ui->WidthField->setText("1");

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

void MainWindow::accept(){
    QPen Pen;
    ui->IssueLabel->setText("");
    if(ui->ColorField->toPlainText().size() == 0){
        Pen.setColor(QColor(255,255,255,255));
    }else if(ui->ColorField->toPlainText().size() == 8){
        bool ok;
        QList<int> rgba;
        QString res("0x");
        QString s = ui->ColorField->toPlainText();
        for(int i = 0; i < 4; i++){
            res.append(s[i*2]);
            res.append(s[i*2 +1]);
            rgba.append(res.toInt(&ok,16));
            res.remove(2,2);
        }
        Pen.setColor(QColor(rgba[0],rgba[1],rgba[2],rgba[3]));
    }else if(ui->ColorField->toPlainText().size() == 6){
        bool ok;
        QList<int> rgba;
        QString res("0x");
        QString s = ui->ColorField->toPlainText();
        for(int i = 0; i < 3; i++){
            res.append(s[i*2]);
            res.append(s[i*2 +1]);
            if(!((('0' <= res[2] && res[2] <= '9') || ('A' <= res[2] && res[2] <= 'F') || ('a' <= res[2] && res[2] <= 'f')) &&
               (('0' <= res[3] && res[3] <= '9') || ('A' <= res[3] && res[3] <= 'F') || ('a' <= res[3] && res[3] <= 'f')))){
                    ui->IssueLabel->setText("ERROR: Color invalid");
                    return;
            }
            rgba.append(res.toInt(&ok,16));
            res.remove(2,2);
        }
        Pen.setColor(QColor(rgba[0],rgba[1],rgba[2],255));
    }else{
        ui->IssueLabel->setText("ERROR: Color invalid");
        return;
    }
    switch (ui->PenStyleComboBox->currentIndex()) {
        case 1:Pen.setStyle(Qt::SolidLine);break;
        case 2:Pen.setStyle(Qt::DashLine);break;
        case 3:Pen.setStyle(Qt::DotLine);break;
        case 4:Pen.setStyle(Qt::DashDotLine);break;
        case 5:Pen.setStyle(Qt::DashDotDotLine);break;
        case 6:Pen.setStyle(Qt::CustomDashLine);break;
    }
    switch(ui->CapStyleComboBox->currentIndex()){
        case 1: Pen.setCapStyle(Qt::SquareCap);break;
        case 2: Pen.setCapStyle(Qt::FlatCap);break;
        case 3: Pen.setCapStyle(Qt::RoundCap);break;
    }
    if(ui->WidthField->toPlainText().size() > 0){
        int w;
        bool ok;
        w = ui->WidthField->toPlainText().toInt(&ok,10);
        if(ok)
            Pen.setWidth(w);
    }else{
        ui->IssueLabel->setText("ERROR: Width invalid");
        return;
    }

    QList<QPoint> pointList;
    bool ok;
    int x,y;
    x = ui->CurveXTextEdit->toPlainText().toInt(&ok,10);
    if(!ok){
        ui->IssueLabel->setText("ERROR: Invalid position x invalid");
        return;
    }
    y = ui->CurveYTextEdit->toPlainText().toInt(&ok,10);
    if(!ok){
        ui->IssueLabel->setText("ERROR: Invalid position y invalid");
        return;
    }
    pointList.append(QPoint(x,y));
    x = ui->CurveXTextEdit_2->toPlainText().toInt(&ok,10);
    if(!ok){
        ui->IssueLabel->setText("ERROR: Invalid position x invalid");
        return;
    }
    y = ui->CurveYTextEdit_2->toPlainText().toInt(&ok,10);
    if(!ok){
        ui->IssueLabel->setText("ERROR: Invalid position y invalid");
        return;
    }
    pointList.append(QPoint(x,y));
    x = ui->CurveXTextEdit_3->toPlainText().toInt(&ok,10);
    if(!ok){
        ui->IssueLabel->setText("ERROR: Invalid position x invalid");
        return;
    }
    y = ui->CurveYTextEdit_3->toPlainText().toInt(&ok,10);
    if(!ok){
        ui->IssueLabel->setText("ERROR: Invalid position y invalid");
        return;
    }
    pointList.append(QPoint(x,y));
    x = ui->CurveXTextEdit_4->toPlainText().toInt(&ok,10);
    if(!ok){
        ui->IssueLabel->setText("ERROR: Invalid position x invalid");
        return;
    }
    y = ui->CurveYTextEdit_4->toPlainText().toInt(&ok,10);
    if(!ok){
        ui->IssueLabel->setText("ERROR: Invalid position y invalid");
        return;
    }
    pointList.append(QPoint(x,y));

    if(canvas->SelectedCurve != NULL){
        canvas->SelectedCurve->setPen(Pen);
        if(canvas->SelectedCurve->getCurveType() == BEZIER){
            canvas->SelectedCurve->setPT0(pointList[0]);
            canvas->SelectedCurve->setPT1(pointList[1]);
            canvas->SelectedCurve->setPT2(pointList[2]);
            canvas->SelectedCurve->setPT3(pointList[3]);
        }else if(canvas->SelectedCurve->getCurveType() == HERMITE){
            canvas->SelectedCurve->setPT0(pointList[0]);
            canvas->SelectedCurve->setPT1(pointList[2]);
            canvas->SelectedCurve->setPT2(pointList[1]);
            canvas->SelectedCurve->setPT3(pointList[3]);
        }
    }
    else if(canvas->getTypeCurve() != NOCURVE){
        Curve *curve = new Curve(canvas->getTypeCurve(),Pen);
        if(canvas->getTypeCurve() == BEZIER){
            curve->setPT0(pointList[0]);
            curve->setPT1(pointList[1]);
            curve->setPT2(pointList[2]);
            curve->setPT3(pointList[3]);
        }else if(canvas->getTypeCurve() == HERMITE){
            curve->setPT0(pointList[0]);
            curve->setPT1(pointList[2]);
            curve->setPT2(pointList[1]);
            curve->setPT3(pointList[3]);
        }
    }else{
        ui->IssueLabel->setText("ERROR: Any operation invalid");
        return;
    }

    canvas->resetCurve();
    canvas->interfaceUpdate();
}

