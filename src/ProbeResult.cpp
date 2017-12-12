#include "ProbeResult.h"

ProbeResult::ProbeResult()
{}

bool ProbeResult::getNeutral() const
{
    return neutral;
}

void ProbeResult::setNeutral(bool value)
{
    neutral = value;
}

int ProbeResult::getDelay() const
{
    return delay;
}

void ProbeResult::setDelay(int value)
{
    delay = value;
}

QTime ProbeResult::getTimestamp() const
{
    return timestamp;
}

void ProbeResult::setTimestamp(const QTime& value)
{
    timestamp = value;
}
