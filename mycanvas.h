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
#include "QTextEdit"
#include "QComboBox"

class MyCanvas: public QLabel
{

public:    
    Curve *SelectedCurve;
    MyCanvas(QPushButton *btnDeleteCurve,QPushButton *btnUnselectCurve,QTextEdit *p0x_field,QTextEdit *p0y_field,QTextEdit *p1x_field,QTextEdit *p1y_field,
             QTextEdit *p2x_field,QTextEdit *p2y_field,QTextEdit *p3x_field,QTextEdit *p3y_field,QTextEdit *rgba_field,
             QTextEdit *width_field, QLabel *TypeCurveField, QComboBox *PenCapField,QComboBox *PenStyleField,QLabel *label3,QLabel *label4);

    unsigned int getNCurves();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resetCurve();
    void setTypeCurve(char typeCurve);
    char getTypeCurve();
    void interfaceUpdate(void);
    void deleteSelectedCurve();
    void setPen(QPen p);
    void addCurve(Curve c);
    void renderAllCurve(bool drawMesh);
    void UnSelectCurve();

private:
    QTextEdit *p0x_field,
              *p0y_field,
              *p1x_field,
              *p1y_field,
              *p2x_field,
              *p2y_field,
              *p3x_field,
              *p3y_field,
              *rgba_field,
              *width_field;
    QLabel *TypeCurveField, *Label3, *Label4;
    QComboBox *PenCapField, *PenStyleField;

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
    QPushButton *btnDeleteCurve, *btnUnselectCurve;

    Curve *SelectCurve(unsigned int i);
    Curve *SelectCurve(Curve *c);
    Curve *SelectCurve(CanvasPoint p);

    void clearImage();
    void renderBezier();
    void renderHermite();

};

#endif // MYCANVAS_H

