#include "mainwindow.h"
#include <QApplication>
#include "canvascore.h"

int main(int argc, char *argv[])
{    
    QApplication aplicacao(argc, argv);
    MainWindow janelaPrincipal;
    janelaPrincipal.showMaximized();
    return aplicacao.exec();
}
