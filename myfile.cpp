#include <QFile>
#include <QTextStream>
#include <QList>
#include <QString>
#include <QPoint>

#include "curve.h"

QList<Curve> openFile(QString filename){
    QList<Curve> ListCurve;
    QPen pen;
    QFile file(filename);

    if(!file.open(QFile::ReadOnly)){
         return ListCurve;
    }
    QString line;
    QTextStream in(&file);
    QPen PenDefault(QColor(255,255,255));
    QPoint p0,p1,p2,p3;

    char typeCurve;
    while(!in.atEnd()){
        //tipo da linha
        line = in.readLine();
        if(line.isNull())
            return ListCurve;
        else if(!line.compare(QString("B")))
            typeCurve = BEZIER;
        else if(!line.compare(QString("H")))
            typeCurve = HERMITE;
        else
            return ListCurve;

        //CARREGAR A CANETA
        line = in.readLine();
        if(line[0] == 'P'){
            int cs;
            QList<QString> split = line.split("#");
            pen.setColor(QColor(split[1].toInt(),split[2].toInt(),split[3].toInt(),split[4].toInt()));
            cs = split[5].toInt();
            switch (cs){
                case 1: pen.setStyle(Qt::SolidLine);break;
                case 2: pen.setStyle(Qt::DashLine);break;
                case 3: pen.setStyle(Qt::DotLine);break;
                case 4: pen.setStyle(Qt::DashDotDotLine);break;
                case 5: pen.setStyle(Qt::DashDotLine);break;
                case 6: pen.setStyle(Qt::CustomDashLine);break;

            }
            cs = split[5].toInt();
            switch (cs){
                case 1: pen.setCapStyle(Qt::SquareCap);break;
                case 2: pen.setCapStyle(Qt::FlatCap);break;
                case 3: pen.setCapStyle(Qt::RoundCap);break;
            }
            pen.setWidth(split[7].toInt());
            //le o primeiro ponto
            line = in.readLine();
        }else{
            pen = PenDefault;
        }

        if(line.isNull())
             return ListCurve;
        else{
            bool ok;
            QStringList strPoints = line.split(" ");
            p0.setX(strPoints[0].toInt(&ok));
            if(!ok)
                return ListCurve;
            p0.setY(strPoints[1].toInt(&ok));
        }

        line = in.readLine();
        if(line.isNull())
             return ListCurve;
        else{
            bool ok;
            QStringList strPoints = line.split(" ");
            p1.setX(strPoints[0].toInt(&ok));
            if(!ok)
                return ListCurve;
            p1.setY(strPoints[1].toInt(&ok));
        }

        line = in.readLine();
        if(line.isNull())
             return ListCurve;
        else{
            bool ok;
            QStringList strPoints = line.split(" ");
            p2.setX(strPoints[0].toInt(&ok));
            if(!ok)
                return ListCurve;
            p2.setY(strPoints[1].toInt(&ok));
        }

        line = in.readLine();
        if(line.isNull())
             return ListCurve;
        else{
            bool ok;
            QStringList strPoints = line.split(" ");
            p3.setX(strPoints[0].toInt(&ok));
            if(!ok)
                return ListCurve;
            p3.setY(strPoints[1].toInt(&ok));
        }
        ListCurve.append(Curve(p0,p1,p2,p3,typeCurve,pen));
    }
    return ListCurve;
}

bool saveFile(QList<Curve> ListCurve, QString fileName){
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return false;
    QTextStream out(&file);
    for(int i = 0; i < ListCurve.size(); i++){
        if(ListCurve[i].getCurveType() == BEZIER)
            out << "B\n";
        else if(ListCurve[i].getCurveType() == HERMITE)
            out << "H\n";

        //CANETA
        QString capStyle,Style;
        if(ListCurve[i].getPen().style() == Qt::SolidLine)
            Style = "1";
        else if(ListCurve[i].getPen().style() == Qt::DashLine)
            Style = "2";
        else if(ListCurve[i].getPen().style() == Qt::DotLine)
            Style = "3";
        else if(ListCurve[i].getPen().style() == Qt::DashDotLine)
            Style = "4";
        else if(ListCurve[i].getPen().style() == Qt::DashDotDotLine)
            Style = "5";
        else if(ListCurve[i].getPen().style() == Qt::CustomDashLine)
            Style = "6";

        if(ListCurve[i].getPen().capStyle() == Qt::SquareCap)
            capStyle = "1";
        else if(ListCurve[i].getPen().capStyle() == Qt::FlatCap)
            capStyle = "2";
        else if(ListCurve[i].getPen().capStyle() == Qt::RoundCap)
            capStyle = "3";


        out << "P#"+
               QString::number(ListCurve[i].getPen().color().red())
               +"#"+
               QString::number(ListCurve[i].getPen().color().green())
               +"#"+
               QString::number(ListCurve[i].getPen().color().blue())
               +"#"+
               QString::number(ListCurve[i].getPen().color().alpha())
               +"#"+
               Style
               +"#"+
               capStyle
               +"#"+
               QString::number(ListCurve[i].getPen().width())
               +"\n";
        //Pontos
        out << QString::number(ListCurve[i].getPT0().x())+" "+QString::number(ListCurve[i].getPT0().y())+"\n";
        out << QString::number(ListCurve[i].getPT1().x())+" "+QString::number(ListCurve[i].getPT1().y())+"\n";
        out << QString::number(ListCurve[i].getPT2().x())+" "+QString::number(ListCurve[i].getPT2().y())+"\n";
        out << QString::number(ListCurve[i].getPT3().x())+" "+QString::number(ListCurve[i].getPT3().y())+"\n";

    }
    return true;
}
