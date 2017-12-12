#include "CrossLabel.h"

CrossLabel::CrossLabel(const QString& marker)
    : Cross(marker),
      markerLabel(marker)
{
    markerLabel.setAlignment(Qt::AlignCenter);
}

QLabel* CrossLabel::getWidget()
{
    return &markerLabel;
}
