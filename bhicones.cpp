#include <QImage>
#include "bhicones.h"

bhIcones::bhIcones()
{
    this->tabelaIcones.load("icones.jpg");
}

QImage bhIcones::get
