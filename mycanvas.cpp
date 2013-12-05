#include "mycanvas.h"
#include "QColor"
#include "QPalette"
#include "QMouseEvent"
#include "QPainter"

#include "algorithms.h"
#include "canvascore.h"



#define DRAWBEZIER(painter,drawMesh) AlgorithmBezier(painter,QPoint(BufferPoints->buffer[0].x,BufferPoints->buffer[0].y),QPoint(BufferPoints->buffer[1].x,BufferPoints->buffer[1].y),QPoint(BufferPoints->buffer[2].x,BufferPoints->buffer[2].y),QPoint(BufferPoints->buffer[3].x,BufferPoints->buffer[3].y),drawMesh);

MyCanvas::MyCanvas()
{
    CanvasCoreInit();
    CanvasBufferImage = QImage(769,539, QImage::Format_ARGB32);
//    QColor bgColor= QColor(39,39,39);
//    QPalette pallete;
//    pallete.setColor(QPalette::Window,bgColor);
//    this->setAutoFillBackground(true);
//    this->setPalette(pallete);
    BufferPoints = getCanvasBuffer();
}

//Quando eu arrasto o mouse
void MyCanvas::mouseMoveEvent ( QMouseEvent * event ){    
    return;
}

//Quando eu clico
void MyCanvas::mousePressEvent(QMouseEvent *event){    
    LastClickedPoint.x = event->x(); LastClickedPoint.y = event->y();

    this->setText("x:"+QString::number(LastClickedPoint.x)+" y:"+QString::number(LastClickedPoint.y)+"\nbuffer x:"+QString::number(BufferPoints->buffer[BufferPoints->nelem].x)+" y:"+QString::number(BufferPoints->buffer[BufferPoints->nelem].y)+"\nNelem"+QString::number(BufferPoints->nelem));
    if(CanvasBufferAddPoint(LastClickedPoint)){
        QPainter painter(&CanvasBufferImage);
        DRAWBEZIER(&painter,false);
    }

    return;
}
