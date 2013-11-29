#ifndef BHICONS_H
#define BHICONS_H

#include <QImage>

class bhIcons
{
public:
    bhIcons();
    QImage getIcon(short x, short y);
private:
    QImage TableIcons;

};

#endif // BHICONS_H
