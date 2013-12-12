#include "math.h"
#include "algorithms.h"

QPen penBack(QColor(59,59,59));

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

    if(drawMesh){
        painter->setPen(penBack);
        painter->drawLine(pc0,pc1);
        painter->drawLine(pc2,pc1);
        painter->drawLine(pc2,pc3);
        DrawCircleInCurve(painter,pc0,pc1,pc2,pc3);
        DrawRectMoveOfCurve(painter,pc0,pc1,pc2,pc3);
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
    if(drawMesh){
        painter->setPen(penBack);
        painter->drawRect(pc0.x()-3,pc0.y()-3,6,6);
        painter->drawRect(pc1.x()-3,pc1.y()-3,6,6);
        painter->drawRect(pc2.x()-3,pc2.y()-3,6,6);
        painter->drawRect(pc3.x()-3,pc3.y()-3,6,6);
        painter->setPen(penOrig);
    }
    return;
}

void AlgorithmHermite(QPainter *painter, QPoint pc0, QPoint pc1, QPoint T0, QPoint T1, bool drawMesh, unsigned int nsteps){

    if(drawMesh){
        QPen penOrig(painter->pen());
             painter->setPen(penBack);
             painter->drawLine(pc0,T0);
             painter->drawLine(pc1,T1);
             DrawRectMoveOfCurve(painter,pc0,pc1,T0,T1);
             DrawCircleInCurve(painter,pc0,pc1,T0,T1);
             painter->setPen(penOrig);
    }
    QPoint    opostoPoint = oposto(pc1,T1);
    QVector2D p0(pc0),
              p1(T0),
              p2(opostoPoint),
              p3(pc1);

    QVector2D dd01((p1-p0)/nsteps),
              dd12((p2-p1)/nsteps),
              dd23((p3-p2)/nsteps),
              dd02,dd13,dd03,
              p01,p12,p23,p02,p13,p03,
              previusPoint02(p0),previusPoint13(p1),previusPoint03(p0);
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
    if(drawMesh){
        QPen penOrig(painter->pen());
        painter->setPen(penBack);
        painter->drawRect(p0.x()-3,p0.y()-3,6,6);
        painter->drawRect(p1.x()-3,p1.y()-3,6,6);
        painter->drawEllipse(T0,3,3);
        painter->drawEllipse(T1,3,3);
        painter->setPen(penOrig);
    }
    return;
}

double distance2Points(QPoint a, QPoint b){
    return sqrt(
                (a.x()-b.x())*(a.x()-b.x()) +
                (a.y()-b.y())*(a.y()-b.y())
                );
}

/**
 * @brief drawRectMove
 *      Desenha o quadadinho que pode movimentar a Curva
 * @param painter
 *      Renderizador
 * @param p
 *      ponto do centro do quadrado
 */
void drawRectMove(QPainter *painter, QPoint p){
    painter->drawRect(p.x()-10,p.y()-10,10,10);

    painter->drawLine(p.x()-35,p.y()-5,p.x()+30,p.y()-5);
    painter->drawLine(p.x()-5,p.y()+25,p.x()-5,p.y()-35);

    painter->drawLine(p.x()-35,p.y()-5,p.x()-30,p.y());
    painter->drawLine(p.x()-35,p.y()-5,p.x()-30,p.y()-10);

    painter->drawLine(p.x()+30,p.y()-5,p.x()+25,p.y());
    painter->drawLine(p.x()+30,p.y()-5,p.x()+25,p.y()-10);

    painter->drawLine(p.x()-5,p.y()+25,p.x(),p.y()+20);
    painter->drawLine(p.x()-5,p.y()+25,p.x()-10,p.y()+20);

    painter->drawLine(p.x()-5,p.y()-35,p.x(),p.y()-30);
    painter->drawLine(p.x()-5,p.y()-35,p.x()-10,p.y()-30);
}

int MaxX(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3){
    int aux = pc0.x();
    aux = aux > pc1.x() ? aux : pc1.x();
    aux = aux > pc2.x() ? aux : pc2.x();
    return aux > pc3.x() ? aux : pc3.x();
}

int MinX(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3){
    int aux = pc0.x();
    aux = aux < pc1.x() ? aux : pc1.x();
    aux = aux < pc2.x() ? aux : pc2.x();
    return aux < pc3.x() ? aux : pc3.x();
}

int MaxY(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3){
    int aux = pc0.y();
    aux = aux > pc1.y() ? aux : pc1.y();
    aux = aux > pc2.y() ? aux : pc2.y();
    return aux > pc3.y() ? aux : pc3.y();
}

int MinY(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3){
    int aux = pc0.y();
    aux = aux < pc1.y() ? aux : pc1.y();
    aux = aux < pc2.y() ? aux : pc2.y();
    return aux < pc3.y() ? aux : pc3.y();
}

int MiddleX(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3){
    int minX = MinX(pc0,pc1,pc2,pc3),
        maxX = MaxX(pc0,pc1,pc2,pc3);
    return (int)((maxX-minX)/2) + minX;
}

int MiddleY(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3){
    int minY = MinY(pc0,pc1,pc2,pc3),
        maxY = MaxY(pc0,pc1,pc2,pc3);
    return (int)((maxY-minY)/2) + minY;
}

void DrawRectMoveOfCurve(QPainter *painter, QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3,int W, int H){
    int maxY = MaxY(pc0,pc1,pc2,pc3),
        minY = MinY(pc0,pc1,pc2,pc3),
        minX = MinX(pc0,pc1,pc2,pc3),
        maxX = MaxX(pc0,pc1,pc2,pc3);
    if(W > minX && 0 < minX){
        if(H > maxY+30)
            drawRectMove(painter,QPoint(minX, maxY+30));
        else if(0 < minY-30)
            drawRectMove(painter,QPoint(minX, minY-30));
        else
            drawRectMove(painter,QPoint(minX, MiddleY(pc0,pc1,pc2,pc3)));
    }else if(0 > minX && W > maxX){
        if(H > maxY+30)
            drawRectMove(painter,QPoint(maxX, maxY+30));
        else if(0 < minY-30)
            drawRectMove(painter,QPoint(maxX, minY-30));
        else
            drawRectMove(painter,QPoint(maxX, MiddleY(pc0,pc1,pc2,pc3)));
    }else{
            int midX = MiddleX(pc0,pc1,pc2,pc3),
                midY = MiddleY(pc0,pc1,pc2,pc3);
            drawRectMove(painter,QPoint(midX, midY));
    }
}

bool InRectMoveOfCurve(QPoint P, QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3,int W, int H){
    int maxY = MaxY(pc0,pc1,pc2,pc3),
        minY = MinY(pc0,pc1,pc2,pc3),
        minX = MinX(pc0,pc1,pc2,pc3),
        maxX = MaxX(pc0,pc1,pc2,pc3);
    if(W > minX && 0 < minX){
        if(H > maxY+30){
            if(minX-10 <= P.x() &&  minX >= P.x() && maxY+20 <= P.y() && maxY+30 >= P.y())
                return true;
        }else if(0 < minY-30){
            if(minX-10 <= P.x() &&  minX >= P.x() && minY-40 <= P.y() && minY-30 >= P.y())
                return true;
        }else{
            int midY = MiddleY(pc0,pc1,pc2,pc3);
            if( minX-10 <= P.x() && minX >= P.x() && midY-10 <= P.y() && midY >= P.y())
                return true;
        }
    }else if(0 > minX && W > maxX){
        if(H > maxY+30){
            if(maxX-10 <= P.x() &&  maxX >= P.x() && maxY+20 <= P.y() && maxY+30 >= P.y())
                return true;
        }else if(0 < minY-30){
            if(maxX-10 <= P.x() &&  maxX >= P.x() && minY-40 <= P.y() && minY-30 >= P.y())
                return true;
        }else{
            int midY = MiddleY(pc0,pc1,pc2,pc3);
            if( maxX-10 <= P.x() && maxX >= P.x() && midY-10 <= P.y() && midY >= P.y())
                return true;
        }
    }else{
            int midX = MiddleX(pc0,pc1,pc2,pc3),
                midY = MiddleY(pc0,pc1,pc2,pc3);
            if(midX-10 <= P.x() &&  midX >= P.x() && midY-10 <= P.y() && minY >= P.y()) // Arrumar Esse CASO
                return true;
    }
    return false;
}

void DrawCircleInCurve(QPainter *painter, QPoint p0, QPoint p1, QPoint p2, QPoint p3){
    int midX = MiddleX(p0,p1,p2,p3),
        midY = MiddleY(p0,p1,p2,p3),
        maxX = MaxX(p0,p1,p2,p3),
        minX = MinX(p0,p1,p2,p3),
        maxY = MaxY(p0,p1,p2,p3),
        minY = MinY(p0,p1,p2,p3),
        deltaX = abs(midX-minX) > abs(midX - maxX) ? abs(midX-minX):abs(midX - maxX),
        deltaY = abs(midY-minY) > abs(midY - maxY) ? abs(midY-minY):abs(midY - maxY),
        maxDelta = (deltaX > deltaY ? deltaX : deltaY)+3;//Pego o delta
    painter->drawEllipse(QPoint(midX,midY),maxDelta ,maxDelta);
    painter->drawRect(midX-maxDelta-3,midY-3,6,6);
    painter->drawRect(midX+maxDelta-3,midY-3,6,6);
    painter->drawRect(midX-3,midY-maxDelta-3,6,6);
    painter->drawRect(midX-3,midY+maxDelta-3,6,6);


}

QPoint oposto(QPoint centro, QPoint ponto){
    int x = centro.x() - ponto.x();
    int y = centro.y() - ponto.y();
    x += centro.x();
    y += centro.y();
    return QPoint(x,y);
}
