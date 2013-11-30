#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>

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
    QImage bufferCanvas;

    QToolButton *btnNew,
    *btnOpen,
    *btnSave,
    *btnDrawCurve,
    *btnZoomIn,
    *btnZoomOut;
    void interfaceUpdate(void);
    void SetupComponents();
};

#endif // MAINWINDOW_H
