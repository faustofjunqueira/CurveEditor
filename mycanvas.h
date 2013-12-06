#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "QImage"
#include "QLabel"
#include "QMouseEvent"
#include "QPainter"
#include "canvascore.h"
#include <QList>
#include "curve.h"

class MyCanvas: public QLabel
{

public:    
    MyCanvas();
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent(QMouseEvent *event);
    unsigned int getNCurves();
    void cancelCurve();
    void prepareCurve(QPen pen, char typeCurve);
private:
    QList<Curve> CurveList;
    CanvasPoint LastClickedPoint;
    CanvasPoint ClickedPoint;
    bool startDrawLine;
    QImage CanvasBufferImage;
    CanvasPoint *BufferPoints; // pontos que estao no buffer

    void renderBezier();
    void interfaceUpdate(void);
};

#endif // MYCANVAS_H

