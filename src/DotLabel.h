#ifndef DOTLABEL_H
#define DOTLABEL_H

#include "Dot.h"

#include <QLabel>

class DotLabel : public Dot
{
public:
    explicit DotLabel(const QString& marker);
    QLabel* getWidget();
private:
    QLabel markerLabel;
};

#endif // DOTLABEL_H
