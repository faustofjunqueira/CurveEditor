#include <stdlib.h>
#include "QColor"
#include "QPalette"
#include "QMouseEvent"
#include "QPainter"

#include "mycanvas.h"
#include "algorithms.h"
#include "canvascore.h"

#define DRAWBEZIER(painter,drawMesh) AlgorithmBezier(painter,QPoint(BufferPoints[0].x,BufferPoints[0].y),QPoint(BufferPoints[1].x,BufferPoints[1].y),QPoint(BufferPoints[2].x,BufferPoints[2].y),QPoint(BufferPoints[3].x,BufferPoints[3].y),drawMesh);

MyCanvas::MyCanvas()
{
    CanvasCoreInit();
    BufferPoints = (CanvasPoint*) malloc(sizeof(CanvasPoint)*4);
    CanvasBufferImage = QImage(769,539, QImage::Format_ARGB32);
    QColor bgColor= QColor(39,39,39);
    QPalette pallete;
    pallete.setColor(QPalette::Window,bgColor);
    this->setAutoFillBackground(true);
    this->setPalette(pallete);
}

//Quando eu arrasto o mouse
void MyCanvas::mouseMoveEvent ( QMouseEvent * event ){    

    return;
}

//Quando eu clico
void MyCanvas::mousePressEvent(QMouseEvent *event){    
    LastClickedPoint.x = event->x(); LastClickedPoint.y = event->y();

    if(CanvasBufferAddPoint(LastClickedPoint)){
        CanvasBufferGetPoints(BufferPoints);
        QPainter painter(&CanvasBufferImage);
        DRAWBEZIER(&painter,false);
        painter.end();
    }
    interfaceUpdate();
    return;
}

void MyCanvas::interfaceUpdate(void){
    this->setPixmap(QPixmap::fromImage(CanvasBufferImage));
    update();
}
