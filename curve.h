#ifndef CURVE_H
#define CURVE_H

#define NOCURVE 0
#define HERMITE 1
#define BEZIER 2

#include <QPoint>
#include <QPainter>
#include <QPen>
#include <QColor>

class Curve
{
public:
    Curve(QPoint p0,QPoint p1,QPoint p2,QPoint p3,char curve,QPen pen = QPen(QColor(255,255,255)));
    Curve(char curve,QPen pen);
    QPoint getPT0();
    QPoint getPT1();
    QPoint getPT2();
    QPoint getPT3();
    QPen getPen();
    char getCurveType();
    void setPT0(QPoint pt);
    void setPT1(QPoint pt);
    void setPT2(QPoint pt);
    void setPT3(QPoint pt);
    void draw(QPainter *painter, bool drawMesh=false);
    double distance(QPoint p);
    QPoint *selectControlPoint(QPoint p);
    bool InMoveRect(QPoint p);
    QList<QPoint> ptControl;
    void IncrementX(int scalar);
    void IncrementY(int scalar);
    void DecrementX(int scalar);
    void DecrementY(int scalar);
    void setPen(QPen pen);
private:

    char curve;
    QPen pen;
};

#endif // CURVE_H
