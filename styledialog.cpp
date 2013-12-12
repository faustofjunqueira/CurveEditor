#include "styledialog.h"
#include "ui_styledialog.h"

StyleDialog::StyleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StyleDialog)
{
    ui->setupUi(this);
    Pen.setColor(QColor(255,255,255));
    SetupComponent();
}

StyleDialog::~StyleDialog()
{
    delete ui;
}

void StyleDialog::SetupComponent(){
    ui->PenStyleComboBox->addItem("Qt::SolidLine");
    ui->PenStyleComboBox->addItem("Qt::DashLine");
    ui->PenStyleComboBox->addItem("Qt::DotLine");
    ui->PenStyleComboBox->addItem("Qt::DashDotLine");
    ui->PenStyleComboBox->addItem("Qt::DashDotDotLine");
    ui->PenStyleComboBox->addItem("Qt::CustomDashLine");

    ui->CapStyleComboBox->addItem("Qt::SquareCap");
    ui->CapStyleComboBox->addItem("Qt::FlatCap");
    ui->CapStyleComboBox->addItem("Qt::RoundCap");
}

void StyleDialog::accept(){
    ui->IssueLabel->setText("");
    if(ui->ColorField->toPlainText().size() == 8){
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
    }
    c->setPen(Pen);
    this->hide();
}

void StyleDialog::setCanvas(MyCanvas *c){
    this->c = c;
}
