#ifndef STYLEDIALOG_H
#define STYLEDIALOG_H

#include <QDialog>
#include <QPen>
#include "mycanvas.h"

namespace Ui {
class StyleDialog;
}

class StyleDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit StyleDialog(QWidget *parent = 0);
    ~StyleDialog();
    void setDefaultPen(QPen *pen);
    void setCanvas(MyCanvas *c);
private slots:
    void accept();

private:
    Ui::StyleDialog *ui;
    void SetupComponent();
    QPen Pen;
    MyCanvas *c;
};

#endif // STYLEDIALOG_H
