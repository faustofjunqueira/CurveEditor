#include <stdlib.h>
#include "QColor"
#include "QPalette"
#include "QMouseEvent"
#include "QPainter"
#include "QPen"

#include "mycanvas.h"
#include "algorithms.h"
#include "canvascore.h"

MyCanvas::MyCanvas(QPushButton *btnDeleteCurve,QTextEdit *p0x_field,QTextEdit *p0y_field,QTextEdit *p1x_field,QTextEdit *p1y_field,
                   QTextEdit *p2x_field,QTextEdit *p2y_field,QTextEdit *p3x_field,QTextEdit *p3y_field,QTextEdit *rgba_field,
                   QTextEdit *width_field, QLabel *TypeCurveField, QComboBox *PenCapField,QComboBox *PenStyleField,QLabel *label3,QLabel *label4)
{
    CanvasCoreInit();
    this->p0x_field = p0x_field;
    this->p0y_field = p0y_field;
    this->p1x_field = p1x_field;
    this->p1y_field = p1y_field;
    this->p2x_field = p2x_field;
    this->p2y_field = p2y_field;
    this->p3x_field = p3x_field;
    this->p3y_field = p3y_field;
    this->rgba_field = rgba_field;
    this->width_field = width_field;
    this->TypeCurveField = TypeCurveField;
    this->PenCapField = PenCapField;
    this->PenStyleField = PenStyleField;
    this->Label3 = label3;
    this->Label4 = label4;

    this->btnDeleteCurve = btnDeleteCurve;
    FirstPointSelected = false;
    lockMoveControlPoint = true;
    lockMoveCurve = true;
    SelectedCurve = NULL;
    SelectedControlPoint = NULL;

    BufferPoints = (CanvasPoint*) malloc(sizeof(CanvasPoint)*4);
    CanvasBufferImage = QImage(1009,579, QImage::Format_ARGB32);

    bgColor= QColor(39,39,39);
    QPalette pallete;
    pallete.setColor(QPalette::Window,bgColor);
    this->setAutoFillBackground(true);
    this->setPalette(pallete);
    CurveList.clear();

    PenDrawLine.setColor(QColor(130,130,130));
    PenCurve.setColor(QColor(255,255,255));
    painter.begin(&CanvasBufferImage);
    painter.setPen(PenDrawLine);

    typeCurve = NOCURVE;

}

//Quando eu arrasto o mouse
void MyCanvas::mouseMoveEvent ( QMouseEvent * event ){
    if(typeCurve != NOCURVE)
        return;
    MovingPoint.x = event->x(); MovingPoint.y = event->y();
    if(!lockMoveControlPoint && SelectedCurve && SelectedControlPoint){
        SelectedControlPoint->setX(MovingPoint.x);
        SelectedControlPoint->setY(MovingPoint.y);
    }if(!lockMoveCurve){
        if(MovingPoint.x > ClickedPoint.x)
            SelectedCurve->IncrementX(MovingPoint.x - ClickedPoint.x);
        else if(MovingPoint.x < ClickedPoint.x)
            SelectedCurve->DecrementX(ClickedPoint.x-MovingPoint.x);
        if(MovingPoint.y > ClickedPoint.y)
            SelectedCurve->IncrementY(MovingPoint.y - ClickedPoint.y);
        else if(MovingPoint.y < ClickedPoint.y)
            SelectedCurve->DecrementY(ClickedPoint.y-MovingPoint.y);
        ClickedPoint = MovingPoint;
    }
    resetCurve();
    interfaceUpdate();
    return;
}

void MyCanvas::mousePressEvent(QMouseEvent *event){    
    LastClickedPoint = ClickedPoint;
    ClickedPoint.x = event->x(); ClickedPoint.y = event->y();
    lockMoveControlPoint = true;
    lockMoveCurve = true;
    SelectedControlPoint = NULL;
    switch(typeCurve){
        case BEZIER: renderBezier();break;
        case HERMITE: renderHermite();break;
    default: {

                if(SelectedCurve){
                    if(SelectedCurve->InMoveRect(QPoint(ClickedPoint.x,ClickedPoint.y))){
                        lockMoveCurve = false;
                        return;
                    }
                    SelectedControlPoint = SelectedCurve->selectControlPoint(QPoint(ClickedPoint.x,ClickedPoint.y));
                    if(SelectedControlPoint){
                        lockMoveControlPoint = false;
                    }
                }
                SelectCurve(ClickedPoint);
                resetCurve();
             }
    }
    interfaceUpdate();
    return;
}

void MyCanvas::renderBezier(){
    UnSelectCurve();
    painter.setPen(PenDrawLine);
    painter.drawRect(ClickedPoint.x-3,ClickedPoint.y-3,6,6); //Desenha um quadradinho aonde clicou click

    if(CanvasBufferAddPoint(ClickedPoint)){
        CanvasBufferGetPoints(BufferPoints);
        Curve *curve = new Curve(BEZIER,PenCurve);
        CurveList.append(*curve);
        CurveList.last().ptControl.append(QPoint(BufferPoints[0].x,BufferPoints[0].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[1].x,BufferPoints[1].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[2].x,BufferPoints[2].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[3].x,BufferPoints[3].y));
        SelectCurve(&CurveList.last());
        resetCurve();
        return;
    }
    if(FirstPointSelected)
        painter.drawLine(QPoint(LastClickedPoint.x,LastClickedPoint.y),QPoint(ClickedPoint.x,ClickedPoint.y));        
    else
        FirstPointSelected = true;
}

void MyCanvas::renderHermite(){
    UnSelectCurve();
    painter.setPen(PenDrawLine);
    painter.drawRect(ClickedPoint.x-3,ClickedPoint.y-3,6,6); //Desenha um quadradinho aonde clicou click

    if(CanvasBufferAddPoint(ClickedPoint)){
        CanvasBufferGetPoints(BufferPoints);
        Curve *curve = new Curve(HERMITE,PenCurve);
        CurveList.append(*curve);
        CurveList.last().ptControl.append(QPoint(BufferPoints[0].x,BufferPoints[0].y));        
        CurveList.last().ptControl.append(QPoint(BufferPoints[2].x,BufferPoints[2].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[1].x,BufferPoints[1].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[3].x,BufferPoints[3].y));
        SelectCurve(&CurveList.last());
        resetCurve();
        return;
    }
    if(CanvasBufferNelem() % 2 == 0) // se for par desenha se for impar nao desenha
        painter.drawLine(QPoint(LastClickedPoint.x,LastClickedPoint.y),QPoint(ClickedPoint.x,ClickedPoint.y));

}

void MyCanvas::resetCurve(){
    FirstPointSelected = false;
    clearImage();
    renderAllCurve(false);
    if(SelectedCurve)
        SelectedCurve->draw(&painter,true);
    CanvasBufferReset();
}

unsigned int MyCanvas::getNCurves(){
    return CurveList.size();
}

void MyCanvas::interfaceUpdate(void){
    this->setPixmap(QPixmap::fromImage(CanvasBufferImage));
    SelectCurve(SelectedCurve);
    update();
}

Curve *MyCanvas::SelectCurve(CanvasPoint p){
    if(typeCurve != NOCURVE || CurveList.size() == 0)
        UnSelectCurve();
    else if(CurveList.size() == 1)
        SelectCurve((unsigned int)0);
    else{
        double minDistance = CurveList[0].distance(QPoint(p.x,p.y));
        double distance = -1;
        unsigned int pos = 0;
        for(int i = 1; i < CurveList.size(); i++){
            if(CurveList[i].getCurveType() == BEZIER){
                distance = CurveList[i].distance(QPoint(p.x,p.y));
                if(distance < minDistance && distance != -1){ // menor 1 eh erro
                    minDistance = distance;
                    pos = i;
                }
            }
        }
        if(minDistance != -1)
            SelectCurve(pos);
    }
    return SelectedCurve;
}

void MyCanvas::renderAllCurve(bool drawMesh){
    for(int i = 0; i < CurveList.size(); i++)
        CurveList[i].draw(&painter,drawMesh);
}

void MyCanvas::clearImage(){
    CanvasBufferImage.fill(bgColor);
}

void MyCanvas::setTypeCurve(char typeCurve){
    this->typeCurve = typeCurve;
}

char MyCanvas::getTypeCurve(){
    return typeCurve;
}

Curve *MyCanvas::SelectCurve(unsigned int i){
    UnSelectCurve();
    if((int)i < CurveList.size())
        SelectCurve(&CurveList[i]);

    return SelectedCurve;
}

Curve *MyCanvas::SelectCurve(Curve *c){
    if(c == NULL)
        return NULL;
    else{
        UnSelectCurve();
        SelectedCurve = c;
        btnDeleteCurve->setEnabled(true);
        if(c->getCurveType() == BEZIER){
            TypeCurveField->setText("Bezier");
            Label3->setText("P3");
            Label4->setText("P4");
            p0x_field->setText(QString::number(SelectedCurve->getPT0().x()));
            p0y_field->setText(QString::number(SelectedCurve->getPT0().y()));
            p1x_field->setText(QString::number(SelectedCurve->getPT1().x()));
            p1y_field->setText(QString::number(SelectedCurve->getPT1().y()));
            p2x_field->setText(QString::number(SelectedCurve->getPT2().x()));
            p2y_field->setText(QString::number(SelectedCurve->getPT2().y()));
            p3x_field->setText(QString::number(SelectedCurve->getPT3().x()));
            p3y_field->setText(QString::number(SelectedCurve->getPT3().y()));
        }else if(c->getCurveType() == HERMITE){
            TypeCurveField->setText("Hermit");
            Label3->setText("T0");
            Label4->setText("T1");
            p0x_field->setText(QString::number(SelectedCurve->getPT0().x()));
            p0y_field->setText(QString::number(SelectedCurve->getPT0().y()));
            p1x_field->setText(QString::number(SelectedCurve->getPT1().x()));
            p1y_field->setText(QString::number(SelectedCurve->getPT1().y()));
            p2x_field->setText(QString::number(SelectedCurve->getPT2().x()));
            p2y_field->setText(QString::number(SelectedCurve->getPT2().y()));
            p3x_field->setText(QString::number(SelectedCurve->getPT3().x()));
            p3y_field->setText(QString::number(SelectedCurve->getPT3().y()));
        }
        switch (SelectedCurve->getPen().style()){
            case Qt::SolidLine: PenStyleField->setCurrentIndex(1);break;
            case Qt::DashLine: PenStyleField->setCurrentIndex(2);break;
            case Qt::DotLine: PenStyleField->setCurrentIndex(3);break;
            case Qt::DashDotLine: PenStyleField->setCurrentIndex(4);break;
            case Qt::DashDotDotLine: PenStyleField->setCurrentIndex(5);break;
            case Qt::CustomDashLine: PenStyleField->setCurrentIndex(6);break;
        }
        switch(SelectedCurve->getPen().capStyle()){
            case Qt::SquareCap: PenCapField->setCurrentIndex(1);break;
            case Qt::FlatCap: PenCapField->setCurrentIndex(2);break;
            case Qt::RoundCap: PenCapField->setCurrentIndex(3);break;
        }

        width_field->setText(QString::number(SelectedCurve->getPen().width()));
        rgba_field->setText((QString::number(SelectedCurve->getPen().color().red(),16)+QString::number(SelectedCurve->getPen().color().blue(),16)+
                            QString::number(SelectedCurve->getPen().color().green(),16)+QString::number(SelectedCurve->getPen().color().alpha(),16)).toUpper());

        return SelectedCurve;
    }
}

void MyCanvas::UnSelectCurve(){
    TypeCurveField->setText("");
    Label3->setText("P3");
    Label4->setText("P4");
    p0x_field->setText("");
    p0y_field->setText("");
    p1x_field->setText("");
    p1y_field->setText("");
    p2x_field->setText("");
    p2y_field->setText("");
    p3x_field->setText("");
    p3y_field->setText("");
    rgba_field->setText("");
    width_field->setText("");
    PenCapField->setCurrentIndex(0);
    PenStyleField->setCurrentIndex(0);
    SelectedCurve = NULL;
    btnDeleteCurve->setEnabled(false);    
}

void MyCanvas::deleteSelectedCurve(){
    if(SelectedCurve)
        for(int i = 0; i < CurveList.size(); i++)
            if(SelectedCurve == &CurveList[i]){
                SelectedCurve = NULL;
                CurveList.removeAt(i);
            }
    resetCurve();
}

void MyCanvas::setPen(QPen p){
    PenCurve = p;
    painter.setPen(p);
}

void MyCanvas::addCurve(Curve c){
    CurveList.append(c);
    SelectCurve(&CurveList.last());
}
