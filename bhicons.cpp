#include "bhicons.h"

bhIcons::bhIcons()
{
    TableIcons.load("icones.jpg");
}

QImage bhIcons::getIcon(short x, short y){
    return TableIcons;
    //return TableIcons.copy(x,y,200,200);
}
