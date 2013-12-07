#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <QImage>
#include <QPainter>
#include <QList>
#include <QPoint>
#include <QColor>
#include <QVector2D>

#define resolutionW 1009
#define resolutionH 579

/**
    Algoritmo de desenho de linha de Bresenham

    Parametro:
        QPainter *painter : Deve vir previamente configurado com Pen que deseja e um QImage
        QPoint pc0 : primeiro ponto de controle
        QPoint pc1 : segundo ponto de controle
        QPoint T0 : vetor tangente de pc0
        QPoint T1 : vetor tangente de pc1

     Exemplo:
        QPen pen = QPen(QColor(255,255,255));
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidth(5);
        QPainter painter(&bufferCanvas);
        painter.setPen(pen);
        QPoint p0 = QPoint(100,300),
                p1 = QPoint(300,150);
        AlgorithmBresenham(&painter,p0,p1);
*/
void AlgorithmBresenham(QPainter *painter, QPoint p1, QPoint p2);

/**
  Algoritmo de Castejeu para criar curvas de Bezier

  Parametros:
    QPainter *painter : Deve vir previamente configurado com Pen que deseja e um QImage
    QPoint pc0 : primeiro ponto de controle
    QPoint pc1 : segundo ponto de controle
    QPoint pc2 : terceiro ponto de controle
    QPoint pc3 : quarto ponto de controle
    bool drawMesh : Se estiver setado para true ira tambem renderizar a malha (traços) que foi usado para criar a curva. Default false
    unsigned int nsteps : numero de passos para o algoritmo, quanto maior mais perfeita a curva. Default 50

  Exemplo de Codigo:
    // bufferCanvas eh uma QImage
    //    TESTE BEZIER
    QPen pen = QPen(QColor(255,255,255));
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(5);
    QPainter painter(&bufferCanvas);
    painter.setPen(pen);
    QPoint p0 = QPoint(100,300),
            p1 = QPoint(150,150),
            p2 = QPoint(200,300),
            p3 = QPoint(300,150);
    AlgorithmBezier(&painter, p1, p0,p3,p2,true);
    painter.end();
*/
void AlgorithmBezier(QPainter *painter, QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3, bool drawMesh = false, unsigned int nsteps = 50);

/**
    Referencia:
        http://www-usr.inf.ufsm.br/~pozzer/disciplinas/cg_7_2d_curvas.pdf
    Formula:
        Seja
            TTT = t*t*t
            TT = t*t
         logo
            P(t) = P1(2*TTT -3*TT + 1) + P2(-2*TTT + 3*TT) + V1(TTT -2*TT + t) + V2(TTT - TT)

    Algortimo que descreve Curvas de Hermite.

    Parametro:
        QPainter *painter : Deve vir previamente configurado com Pen que deseja e um QImage
        QPoint pc0 : primeiro ponto de controle
        QPoint pc1 : segundo ponto de controle
        QPoint T0 : vetor tangente de pc0
        QPoint T1 : vetor tangente de pc1

    Exemplo:
        QPen pen = QPen(QColor(255,255,255));
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidth(5);
        QPainter painter(&bufferCanvas);
        painter.setPen(pen);
        QPoint p0 = QPoint(100,300),
                p1 = QPoint(150,150),
                p2 = QPoint(200,300),
                p3 = QPoint(300,150);
        AlgorithmHermite(&painter,p0,p1,p2,p3);

*/
void AlgorithmHermite(QPainter *painter, QPoint pc0, QPoint pc1, QPoint T0, QPoint T1, bool drawMesh=false, double steps = 0.05);

double distance2Points(QPoint a, QPoint b);

/**
 * @brief drawRectMove
 *      Desenha o quadadinho que pode movimentar a Curva
 * @param painter
 *      Renderizador
 * @param p
 *      ponto do centro do quadrado
 */
void drawRectMove(QPainter *painter, QPoint p);

int MiddleX(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3);
int MiddleY(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3);
int MinY(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3);
int MaxY(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3);
int MinX(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3);
int MaxX(QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3);

/**
 * @brief DrawRectMoveOfCurve
 *          desenha o quadradrinho que move a curva
 * @param pc0
 * @param pc1
 * @param pc2
 * @param pc3
 * @param W
 *       resolucao da tela W
 * @param H
 *       resolucao da tela H
 */
void DrawRectMoveOfCurve(QPainter *painter, QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3,int W = resolutionW, int H = resolutionH);

bool InRectMoveOfCurve(QPoint P, QPoint pc0, QPoint pc1, QPoint pc2, QPoint pc3,int W=resolutionW, int H=resolutionH);

#endif // ALGORITHMS_H
