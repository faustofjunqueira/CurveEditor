#include "algorithms.h"
#include "var.h"
/** ----------PROBLEMA----------- **/
void AlgorithmBresenham(QPainter *painter, QPoint p1, QPoint p2){
    int slope;
    int dx, dy, incE, incNE, d, x, y;
    // Onde inverte a linha x1 > x2
    if (p1.x() > p2.x()){
        AlgorithmBresenham(painter, p2, p1);
         return;
    }
    dx = p2.x() - p1.x();
    dy = p2.y() - p1.y();

    if (dy < 0){
        slope = -1;
        dy = -dy;
    }
    else{
       slope = 1;
    }
    // Constante de Bresenham
    incE = 2 * dy;
    incNE = 2 * dy - 2 * dx;
    d = 2 * dy - dx;
    y = p1.y();
    for (x = p1.x(); x <= p2.x(); x++){
        painter->drawPoint(x, y); // Uso o drawPoint para utilizar a Pen
        if (d <= 0){
          d += incE;
        }
        else{
          d += incNE;
          y += slope;
        }
    }
    return;
}

void AlgorithmBezier(QPainter *painter, QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3, bool drawMesh, unsigned int nsteps){
    QPen penOrig(painter->pen());
    QPen penBack(QColor(59,59,59));

    if(drawMesh){
        painter->setPen(penBack);
        painter->drawLine(pc0,pc1);
        painter->drawLine(pc2,pc1);
        painter->drawLine(pc2,pc3);
    }

    QVector2D p0(pc0), p1(pc1), p2(pc2), p3(pc3);

    QVector2D dd01((p1-p0)/nsteps),
           dd12((p2-p1)/nsteps),
           dd23((p3-p2)/nsteps),
           dd02,dd13,dd03,
           p01,p12,p23,p02,p13,p03,
            previusPoint02(p0),previusPoint13(p1),previusPoint03(p0);

    if(drawMesh){
        painter->setPen(penBack);
        for(int i = 0; i <= (int)nsteps; i++){
            p01 = p0+dd01*i;
            p12 = p1+dd12*i;
            p23 = p2+dd23*i;

            dd02 = (p12-p01)/nsteps;
            p02 = p01 + dd02*i;
            dd13 = (p23-p12)/nsteps;
            p13 = p12 + dd13*i;
            dd03 = (p13 - p02)/nsteps;
            p03 = p02 + dd03*i;


            painter->drawLine(QPoint(p01.x(),p01.y()),QPoint(p02.x(),p02.y()));
            painter->drawLine(QPoint(p12.x(),p12.y()),QPoint(p23.x(),p23.y()));
            painter->drawLine(QPoint(previusPoint02.x(),previusPoint02.y()),QPoint(p02.x(),p02.y()));
            painter->drawLine(QPoint(previusPoint13.x(),previusPoint13.y()),QPoint(p13.x(),p13.y()));

            previusPoint02 = p02;
            previusPoint13 = p13;
            previusPoint03 = p03;

        }
        painter->setPen(penOrig);
    }

    previusPoint02 = previusPoint03 = p0;
    previusPoint13 = p1;

    for(int i = 0; i <= (int)nsteps; i++){
        p01 = p0+dd01*i;
        p12 = p1+dd12*i;
        p23 = p2+dd23*i;

        dd02 = (p12-p01)/nsteps;
        p02 = p01 + dd02*i;
        dd13 = (p23-p12)/nsteps;
        p13 = p12 + dd13*i;
        dd03 = (p13 - p02)/nsteps;
        p03 = p02 + dd03*i;

        painter->drawLine(QPoint(previusPoint03.x(),previusPoint03.y()),QPoint(p03.x(),p03.y()));

        previusPoint02 = p02;
        previusPoint13 = p13;
        previusPoint03 = p03;

    }
    return;
}

void AlgorithmHermite(QPainter *painter, QPoint pc0, QPoint pc1, QPoint T0, QPoint T1, bool drawMesh, double steps){
    QVector2D p0(pc0), p1(pc1), tan0(T0), tan1(T1), previusPoint(p0), pt;
    if(drawMesh){
        QPen penOrig(painter->pen());
        QPen penBack(QColor(59,59,59));
        painter->setPen(penBack);
        painter->drawLine(pc0,T0);
        painter->drawLine(pc1,T1);
        painter->setPen(penOrig);
    }
    float TTT,TT;
    for(float t = 0; t <= 1.0; t+=steps){
        TTT = t*t*t;
        TT = t*t;
        //Para suavizer a curva, multiplica-se algum lugar aqui por WG = 0.5, suponho que multiplique por tan0 e tan1
        pt = p0*(2*TTT -3*TT + 1) + p1*(-2*TTT + 3*TT) + tan0*(TTT -2*TT + t) + tan1*(TTT - TT);
        painter->drawLine(QPoint(previusPoint.x(),previusPoint.y()),QPoint(pt.x(),pt.y()));
        previusPoint = pt;
    }
    return;
}
