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
    QImage CanvasBufferImage;
    CanvasPoint *BufferPoints; // pontos que estao no buffer

    void interfaceUpdate(void);
};

#endif // MYCANVAS_H
