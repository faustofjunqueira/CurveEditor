#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "QImage"
#include "QLabel"
#include "QMouseEvent"
#include "QPainter"
#include "canvascore.h"
#include <QList>
#include "curve.h"
#include "QPushButton"

class MyCanvas: public QLabel
{

public:    
    Curve *SelectedCurve;
    MyCanvas(QPushButton *btnDeleteCurve);
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent(QMouseEvent *event);
    unsigned int getNCurves();
    void resetCurve();
    void setTypeCurve(char typeCurve);
    char getTypeCurve();
    void interfaceUpdate(void);
    void deleteSelectedCurve();
    void setPen(QPen p);
private:
    QList<Curve> CurveList;
    CanvasPoint LastClickedPoint;
    CanvasPoint LastMovedPoint;
    CanvasPoint MovingPoint;
    CanvasPoint ClickedPoint;
    bool FirstPointSelected;

    char typeCurve;
    QImage CanvasBufferImage;
    CanvasPoint *BufferPoints; // pontos que estao no buffer
    QColor bgColor;
    QPen PenDrawLine; // Cor da linha confiracao
    QPainter painter;
    QPen PenCurve;
    QPoint *SelectedControlPoint;
    bool lockMoveControlPoint;
    bool lockMoveCurve;
    QPushButton *btnDeleteCurve;

    void UnSelectCurve();
    Curve *SelectCurve(unsigned int i);
    Curve *SelectCurve(Curve *c);
    Curve *SelectCurve(CanvasPoint p);

    void renderAllCurve(bool drawMesh);
    void clearImage();
    void renderBezier();
    void renderHermite();

};

#endif // MYCANVAS_H

