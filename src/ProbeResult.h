#ifndef PROBERESULT_H
#define PROBERESULT_H

#include <QTime>

class ProbeResult
{
public:
    explicit ProbeResult();

    bool getNeutral() const;
    void setNeutral(bool value);

    int getDelay() const;
    void setDelay(int value);

    QTime getTimestamp() const;
    void setTimestamp(const QTime& value);

private:
    bool neutral;
    int delay;
    QTime timestamp;
};

#endif // PROBERESULT_H
