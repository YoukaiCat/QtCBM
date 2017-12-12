#include "Stimul.h"

Stimul::Stimul()
{}

Stimul::Stimul(bool neutral)
    : neutral(neutral)
{}

bool Stimul::isNeutral() const
{
    return neutral;
}

void Stimul::setNeutral(bool value)
{
    neutral = value;
}
