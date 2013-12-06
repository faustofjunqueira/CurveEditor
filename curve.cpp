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

char *Curve::getCurveType(){
    if(this->curve == HERMITE)
        return "HERMITE";
    else if(curve == BEZIER)
        return "BEZIER";
    else
        return NULL;

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

void Curve::draw(QPainter *painter, bool drawMesh){
    QPen penOrig = painter->pen();
    painter->setPen(pen);
    if(curve == HERMITE)
        AlgorithmHermite(painter,ptControl[0],ptControl[1],ptControl[2],ptControl[3],drawMesh);
    else if(curve == BEZIER)
        AlgorithmBezier(painter,ptControl[0],ptControl[1],ptControl[2],ptControl[3],drawMesh);
   painter->setPen(penOrig);

}
