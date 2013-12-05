#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QSlider>
#include <QLabel>
#include <QTextEdit>
#include "mycanvas.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;    

    QToolButton *btnNew,
    *btnOpen,
    *btnSave,
    *btnDrawCurve,
    *btnPenConfig;
    MyCanvas *canvas;
    QLabel *lbcontrol0,*lbcontrol1,*lbcontrol2,*lbcontrol3;
    QTextEdit *txtcontol0,*txtcontol1,*txtcontol2,*txtcontol3;//91x31
    void interfaceUpdate(void);
    void SetupComponents();
};

#endif // MAINWINDOW_H
