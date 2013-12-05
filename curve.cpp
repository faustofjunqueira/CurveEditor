
#include "curve.h"
#include "algorithms.h"

Curve::Curve(QPoint p0,QPoint p1,QPoint p2,QPoint p3,char curve,QPen pen)
{
    ptcontro0 = p0;
    ptcontro1 = p1;
    ptcontro2 = p2;
    ptcontro3 = p3;
    this->pen = pen;
    this->curve = curve;
}

QPoint Curve::getPT0(){
    return this->ptcontro0;
}

QPoint Curve::getPT1(){
    return this->ptcontro1;
}

QPoint Curve::getPT2(){
    return this->ptcontro2;
}

QPoint Curve::getPT3(){
    return this->ptcontro3;
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
    ptcontro0 = pt;
}

void Curve::setPT1(QPoint pt){
    ptcontro1 = pt;
}

void Curve::setPT2(QPoint pt){
    ptcontro2 = pt;
}

void Curve::setPT3(QPoint pt){
    ptcontro3 = pt;
}

void Curve::draw(QPainter *painter, bool drawMesh){
    QPen penOrig = painter->pen();
    painter->setPen(pen);
    if(curve == HERMITE)
        AlgorithmHermite(painter,ptcontro0,ptcontro1,ptcontro2,ptcontro3,drawMesh);
    else if(curve == BEZIER)
        AlgorithmBezier(painter,ptcontro0,ptcontro1,ptcontro2,ptcontro3,drawMesh);
   painter->setPen(penOrig);

}
