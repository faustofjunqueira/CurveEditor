#ifndef MYFILE_H
#define MYFILE_H

QList<Curve> openFile(QString filename);
bool saveFile(QList<Curve> ListCurve, QString fileName);

#endif // MYFILE_H
