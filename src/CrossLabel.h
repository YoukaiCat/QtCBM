#ifndef CROSSLABEL_H
#define CROSSLABEL_H

#include "Cross.h"

#include <QLabel>

class CrossLabel : public Cross
{
public:
    explicit CrossLabel(const QString& marker);
    QLabel* getWidget();
private:
    QLabel markerLabel;
};

#endif // CROSSLABEL_H
