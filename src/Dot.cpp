#include "Dot.h"

Dot::Dot(const QString& marker)
    : marker(marker)
{}

Dot::~Dot()
{}

QString Dot::getMarker() const
{
    return marker;
}

void Dot::setMarker(const QString& value)
{
    marker = value;
}
