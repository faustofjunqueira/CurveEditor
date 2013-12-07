#include <stdlib.h>
#include "QColor"
#include "QPalette"
#include "QMouseEvent"
#include "QPainter"
#include "QPen"

#include "mycanvas.h"
#include "algorithms.h"
#include "canvascore.h"

MyCanvas::MyCanvas()
{
    CanvasCoreInit();
    FirstPointSelected = false;
    lockMoveControlPoint = true;
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
    }if(SelectedCurve->InMoveRect(QPoint(MovingPoint.x,MovingPoint.y))){
        if(MovingPoint.x > ClickedPoint.x)
            SelectedCurve->IncrementX(MovingPoint.x - ClickedPoint.x);
        else if(MovingPoint.x < ClickedPoint.x)
            SelectedCurve->DecrementX(ClickedPoint.x-MovingPoint.x);
        if(MovingPoint.y > ClickedPoint.y)
            SelectedCurve->IncrementY(MovingPoint.y - ClickedPoint.y);
        else if(MovingPoint.y < ClickedPoint.y)
            SelectedCurve->DecrementY(ClickedPoint.y-MovingPoint.y);
    }
    resetCurve();
    interfaceUpdate();
    return;
}

//Quando eu clico
void MyCanvas::mousePressEvent(QMouseEvent *event){    
    LastClickedPoint = ClickedPoint;
    ClickedPoint.x = event->x(); ClickedPoint.y = event->y();
    lockMoveControlPoint = true;
    SelectedControlPoint = NULL;
    switch(typeCurve){
        case BEZIER: renderBezier();break;
        case HERMITE: renderHermite();break;
    default: {

                if(SelectedCurve){
                    if(SelectedCurve->InMoveRect(QPoint(ClickedPoint.x,ClickedPoint.y)))
                        return;
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
    SelectedCurve = NULL;
    painter.drawRect(ClickedPoint.x-3,ClickedPoint.y-3,6,6); //Desenha um quadradinho aonde clicou click

    if(CanvasBufferAddPoint(ClickedPoint)){
        CanvasBufferGetPoints(BufferPoints);
        //Quando Puder escolher o tipo da curva, isso daki roda;
        QPen pen(QColor(255,255,255));
        pen.setWidth(3);
        Curve *curve = new Curve(BEZIER,pen);
        CurveList.append(*curve);
        CurveList.last().ptControl.append(QPoint(BufferPoints[0].x,BufferPoints[0].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[1].x,BufferPoints[1].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[2].x,BufferPoints[2].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[3].x,BufferPoints[3].y));        
        resetCurve();
        return;
    }
    if(FirstPointSelected)
        painter.drawLine(QPoint(LastClickedPoint.x,LastClickedPoint.y),QPoint(ClickedPoint.x,ClickedPoint.y));        
    else
        FirstPointSelected = true;
}

void MyCanvas::renderHermite(){
    painter.drawRect(ClickedPoint.x-3,ClickedPoint.y-3,6,6); //Desenha um quadradinho aonde clicou click

    if(CanvasBufferAddPoint(ClickedPoint)){
        CanvasBufferGetPoints(BufferPoints);
        //Quando Puder escolher o tipo da curva, isso daki roda;
        QPen pen(QColor(255,255,255));
        pen.setWidth(3);
        Curve *curve = new Curve(HERMITE,pen);
        CurveList.append(*curve);
        CurveList.last().ptControl.append(QPoint(BufferPoints[0].x,BufferPoints[0].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[1].x,BufferPoints[1].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[2].x,BufferPoints[2].y));
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
        SelectedCurve = &CurveList[i];        

    return SelectedCurve;
}

Curve *MyCanvas::SelectCurve(Curve *c){
    UnSelectCurve();
    SelectedCurve = c;
    return SelectedCurve;
}

void MyCanvas::UnSelectCurve(){    
    SelectedCurve = NULL;
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
