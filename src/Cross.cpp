#include "Cross.h"

Cross::Cross(const QString& marker)
    : marker(marker)
{}

Cross::~Cross()
{}

QString Cross::getMarker() const
{
    return marker;
}

void Cross::setMarker(const QString& value)
{
    marker = value;
}
