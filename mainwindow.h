#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QSlider>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QMenu>
#include "mycanvas.h"
#include "styledialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void clickBtnBezier();
    void clickBtnHermite();
    void clickBtnCancelCurve();
    void clickDeleteCurve();
    void clickStyle();

//    void OpenFileAct();
//    void SaveFileAct();
//    void ExitFileAct();

private:
    Ui::MainWindow *ui;    

    QToolButton
        *btnFile;
    QPushButton
        *btnPenConfig,
        *btnBezier,
        *btnHermite,
        *btnCancelCurve,
        *btnDeleteCurve;
    QMenu *FileMenu;
    //QAction *openAct, *saveAct, *exitAct, *exportAct;
    MyCanvas *canvas;
    QPen Pen;
    QLabel *lbcontrol0,*lbcontrol1,*lbcontrol2,*lbcontrol3;
    QTextEdit *txtcontol0,*txtcontol1,*txtcontol2,*txtcontol3;//91x31
    StyleDialog StyleWindow;
    void interfaceUpdate(void);
    void SetupComponents();

};

#endif // MAINWINDOW_H
