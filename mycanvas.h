#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "QImage"
#include "QLabel"
#include "QMouseEvent"
#include "canvascore.h"

class MyCanvas: public QLabel
{
public:
    MyCanvas();
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent(QMouseEvent *event);

private:
    CanvasPoint LastClickedPoint;
    CanvasPointBuffer *BufferPoints;
    QImage CanvasBufferImage;
};

#endif // MYCANVAS_H
