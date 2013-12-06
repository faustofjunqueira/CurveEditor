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
    startDrawLine = false;
    BufferPoints = (CanvasPoint*) malloc(sizeof(CanvasPoint)*4);
    CanvasBufferImage = QImage(769,539, QImage::Format_ARGB32);
    QColor bgColor= QColor(39,39,39);
    QPalette pallete;
    pallete.setColor(QPalette::Window,bgColor);
    this->setAutoFillBackground(true);
    this->setPalette(pallete);
    CurveList.clear();
}

//Quando eu arrasto o mouse
void MyCanvas::mouseMoveEvent ( QMouseEvent * event ){    
    return;
}

//Quando eu clico
void MyCanvas::mousePressEvent(QMouseEvent *event){    
    LastClickedPoint = ClickedPoint;
    ClickedPoint.x = event->x(); ClickedPoint.y = event->y();
    renderBezier();
    interfaceUpdate();
    return;
}

//Esta sendo incluido 2 curvas em vez de 1
void MyCanvas::renderBezier(){
    QPainter painter(&CanvasBufferImage); // painter do canvas
    if(CanvasBufferAddPoint(ClickedPoint)){
        //painter.drawLine(QPoint(LastClickedPoint.x,LastClickedPoint.y),QPoint(ClickedPoint.x,ClickedPoint.y));
        CanvasBufferGetPoints(BufferPoints);
        CurveList.last().ptControl.append(QPoint(BufferPoints[0].x,BufferPoints[0].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[1].x,BufferPoints[1].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[2].x,BufferPoints[2].y));
        CurveList.last().ptControl.append(QPoint(BufferPoints[3].x,BufferPoints[3].y));
        startDrawLine = false;
        painter.drawRect(0,0,this->width(),this->height()); // Clear da Tela

        for(int i = 1; i < CurveList.size(); i++)
            CurveList[i].draw(&painter,false);
        return;
    }
    if(startDrawLine){
        QPen p(QColor(52,52,52)); // Cor da linha confiracao
        painter.setPen(p);
        painter.drawLine(QPoint(LastClickedPoint.x,LastClickedPoint.y),QPoint(ClickedPoint.x,ClickedPoint.y));
        //Quando Puder escolher o tipo da curva, isso daki roda;
        QPen pen(QColor(255,255,255));
        pen.setWidth(3);
        prepareCurve(pen,BEZIER);
    }else
        startDrawLine = true;

}

void MyCanvas::cancelCurve(){
    CurveList.removeLast();
    CanvasBufferReset();
}

unsigned int MyCanvas::getNCurves(){
    return CurveList.size();
}

void MyCanvas::prepareCurve(QPen pen, char typeCurve){
    Curve *curve = new Curve(typeCurve,pen);
    CurveList.append(*curve);
}

void MyCanvas::interfaceUpdate(void){

    this->setPixmap(QPixmap::fromImage(CanvasBufferImage));
    update();
}
