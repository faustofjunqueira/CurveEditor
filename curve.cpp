#include "curve.h"
#include "algorithms.h"

Curve::Curve(QPoint p0,QPoint p1,QPoint p2,QPoint p3,char curve,QPen pen)
{
    ptControl.append(p0);
    ptControl.append(p1);
    ptControl.append(p2);
    ptControl.append(p3);
    this->pen = pen;
    this->curve = curve;
}
Curve::Curve(char curve,QPen pen){
    this->pen = pen;
    this->curve = curve;
}

QPoint Curve::getPT0(){
    return ptControl[0];
}

QPoint Curve::getPT1(){
    return ptControl[1];
}

QPoint Curve::getPT2(){
    return ptControl[2];
}

QPoint Curve::getPT3(){
    return ptControl[3];
}

char Curve::getCurveType(){
    return curve;
}

void Curve::setPT0(QPoint pt){
    ptControl[0] = pt;
}

void Curve::setPT1(QPoint pt){
    ptControl[1] = pt;
}

void Curve::setPT2(QPoint pt){
    ptControl[2] = pt;
}

void Curve::setPT3(QPoint pt){
    ptControl[3] = pt;
}

double Curve::distance(QPoint p){
    double minDistance = distance2Points(ptControl[0],p);
    double distance;
    for(int i = 1; i < ptControl.size(); i++){
        distance = distance2Points(ptControl[i],p);
        minDistance = distance < minDistance ? distance : minDistance;
    }
    return minDistance;
}



void Curve::draw(QPainter *painter, bool drawMesh){
    QPen penOrig = painter->pen();
    painter->setPen(pen);
    if(curve == HERMITE)
        AlgorithmHermite(painter,ptControl[0],ptControl[1],ptControl[2],ptControl[3],drawMesh);
    else if(curve == BEZIER)
        AlgorithmBezier(painter,ptControl[0],ptControl[1],ptControl[2],ptControl[3],drawMesh);

    painter->setPen(penOrig);

}

QPoint *Curve::selectControlPoint(QPoint p){
    for(int i = 0; i < ptControl.size(); i++){
        if(p.x() >= ptControl[i].x()-3 && p.x() <= ptControl[i].x()+3 && p.y() >= ptControl[i].y()-3 && p.y() <= ptControl[i].y()+3)
            return &ptControl[i];
    }
    return NULL;
}

bool Curve::InMoveRect(QPoint p){
    return InRectMoveOfCurve(p, ptControl[0],ptControl[1],ptControl[2],ptControl[3]);
}

void Curve::IncrementX(int scalar){
    ptControl[0].setX(ptControl[0].x()+scalar);
    ptControl[1].setX(ptControl[1].x()+scalar);
    ptControl[2].setX(ptControl[2].x()+scalar);
    ptControl[3].setX(ptControl[3].x()+scalar);
}

void Curve::IncrementY(int scalar){
    ptControl[0].setY(ptControl[0].y()+scalar);
    ptControl[1].setY(ptControl[1].y()+scalar);
    ptControl[2].setY(ptControl[2].y()+scalar);
    ptControl[3].setY(ptControl[3].y()+scalar);
}

void Curve::DecrementX(int scalar){
    ptControl[0].setX(ptControl[0].x()-scalar);
    ptControl[1].setX(ptControl[1].x()-scalar);
    ptControl[2].setX(ptControl[2].x()-scalar);
    ptControl[3].setX(ptControl[3].x()-scalar);
}

void Curve::DecrementY(int scalar){
    ptControl[0].setY(ptControl[0].y()-scalar);
    ptControl[1].setY(ptControl[1].y()-scalar);
    ptControl[2].setY(ptControl[2].y()-scalar);
    ptControl[3].setY(ptControl[3].y()-scalar);
}
