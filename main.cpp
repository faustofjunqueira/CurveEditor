#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication aplicacao(argc, argv);
    MainWindow janelaPrincipal;
    janelaPrincipal.show();
    
    return aplicacao.exec();
}
