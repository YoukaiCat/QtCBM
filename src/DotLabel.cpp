#include "DotLabel.h"

DotLabel::DotLabel(const QString& marker)
    : Dot(marker),
      markerLabel(marker)
{
    markerLabel.setAlignment(Qt::AlignCenter);
}

QLabel* DotLabel::getWidget()
{
    return &markerLabel;
}
