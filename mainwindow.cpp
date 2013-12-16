#include <QColor>
#include <QToolButton>
#include <QPainter>
#include <QFileDialog>
#include <QImageWriter>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myfile.h"

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
    btnUnSelectCurve = new QPushButton("Unselect curve");
    ToolBarLabel = new QLabel;
    isSaved = false;
    FileName = "";
    canvas = new MyCanvas(btnDeleteCurve,btnUnSelectCurve,ui->CurveXTextEdit,ui->CurveYTextEdit,ui->CurveXTextEdit_2,ui->CurveYTextEdit_2,ui->CurveXTextEdit_3,ui->CurveYTextEdit_3,
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

    TitleAplication = "Curve Editor";

    connect(btnBezier,SIGNAL(clicked()),this,SLOT(clickBtnBezier()));
    connect(btnHermite,SIGNAL(clicked()),this,SLOT(clickBtnHermite()));
    connect(btnCancelCurve,SIGNAL(clicked()),this,SLOT(clickBtnCancelCurve()));
    connect(btnDeleteCurve,SIGNAL(clicked()),this,SLOT(clickDeleteCurve()));
    connect(btnPenConfig,SIGNAL(clicked()),this,SLOT(clickStyle()));
    connect(ui->ApplyButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(btnUnSelectCurve,SIGNAL(clicked()),this,SLOT(unselectcurve()));

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
    ui->ToolBarMain->addWidget(btnUnSelectCurve);
    ui->ToolBarMain->addSeparator();
    ui->ToolBarMain->addWidget(ToolBarLabel);

    ui->LayoutCanvas->addWidget(canvas);


    btnCancelCurve->setEnabled(false);
    btnDeleteCurve->setEnabled(false);
    btnUnSelectCurve->setEnabled(false);

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

    createAction();
    createMenu();

    this->interfaceUpdate();
}

void MainWindow::interfaceUpdate(void){
    ui->IssueLabel->setText("");
    canvas->interfaceUpdate();
    this->setWindowTitle(TitleAplication+" - "+FileName);

}

void MainWindow::clickBtnBezier(){
    ToolBarLabel->setText("You choise Bezier");
    btnCancelCurve->setEnabled(true);
    canvas->setTypeCurve(BEZIER);    
}

void MainWindow::clickBtnHermite(){
    ToolBarLabel->setText("You choise Hermite");
    btnCancelCurve->setEnabled(true);
    canvas->setTypeCurve(HERMITE);
}

void MainWindow::clickBtnCancelCurve(){
    ToolBarLabel->setText(" ");
    canvas->setTypeCurve(NOCURVE);
    canvas->resetCurve();
    btnCancelCurve->setEnabled(false);
    interfaceUpdate();
}

void MainWindow::clickDeleteCurve(){
    canvas->deleteSelectedCurve();
    btnDeleteCurve->setEnabled(false);
    btnUnSelectCurve->setEnabled(false);
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
        curve->ptControl.append(pointList[0]);
        if(canvas->getTypeCurve() == BEZIER){            
            curve->ptControl.append(pointList[1]);
            curve->ptControl.append(pointList[2]);
        }else if(canvas->getTypeCurve() == HERMITE){
            curve->ptControl.append(pointList[1]);
            curve->ptControl.append(pointList[2]);
        }
        curve->ptControl.append(pointList[3]);
        canvas->addCurve(*curve);
    }else{
        ui->IssueLabel->setText("ERROR: Any operation invalid\nYou choise a type of curve?");
        return;
    }

    canvas->resetCurve();
    canvas->interfaceUpdate();
}

void MainWindow::unselectcurve(){
    canvas->UnSelectCurve();
    canvas->resetCurve();
    canvas->interfaceUpdate();
}

void MainWindow::createAction(){
    openAct = new QAction(this);
    openAct->setText("Open");
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(OpenFileAct()));

    saveAct = new QAction(this);
    saveAct->setText("Save");
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save a file"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(SaveFileAct()));

    exitAct = new QAction(this);
    exitAct->setText("Exit");
    exitAct->setStatusTip(tr("Exit"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(ExitFileAct()));

    exportAct = new QAction(this);
    exportAct->setText("Export");
    exportAct->setStatusTip(tr("Export in .png"));
    connect(exportAct, SIGNAL(triggered()), this, SLOT(exportImageAct()));

    newAct = new QAction(this);
    newAct->setText("New");
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("New file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(NewFileAct()));
}

void MainWindow::createMenu(){
    FileMenu->addAction(newAct);
    FileMenu->addAction(openAct);
    FileMenu->addAction(saveAct);
    FileMenu->addSeparator();
    FileMenu->addAction(exportAct);
    FileMenu->addSeparator();
    FileMenu->addAction(exitAct);
}

void MainWindow::OpenFileAct(){
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Open file..."), "",
             tr("All Files (*)"));

    QList<Curve> curves = openFile(fileName);
    NewFileAct();
    canvas->copyCurve(curves);
    canvas->resetCurve();
    FileName = fileName;
    isSaved = true;
    canvas->interfaceUpdate();    
}

void MainWindow::SaveFileAct(){
    QString fileName;
    if(!isSaved)
        fileName = QFileDialog::getSaveFileName(this,
                 tr("Save file..."), "",
                 tr("All Files (*)"));
    else
        fileName = FileName;

    saveFile(canvas->CurveList,fileName);
    FileName = fileName;
    isSaved = true;
    interfaceUpdate();
}

void MainWindow::ExitFileAct(){
    this->hide();
}

void MainWindow::exportImageAct(){
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Export to png..."), "",
             tr(".png(*.png)"));
    canvas->UnSelectCurve();
    QImageWriter *imageWriter = new QImageWriter;
    imageWriter->setFileName(fileName);
    imageWriter->setFormat("png");
    imageWriter->setQuality(100);
    imageWriter->write(canvas->CanvasBufferImage);
}

void MainWindow::NewFileAct(){
    canvas->clearCurveList();
    canvas->resetCurve();
    FileName = "";
    isSaved = false;
    canvas->interfaceUpdate();
    interfaceUpdate();
}
