#ifndef DOTPROBE_H
#define DOTPROBE_H

#include "Stimul.h"
#include "Dot.h"
#include "Cross.h"
#include "LayoutMode.h"
#include "DotProbePhase.h"

#include <QObject>
#include <QLayout>
#include <QTime>

#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::move;

class DotProbe : public QObject
{
    Q_OBJECT
public:
    explicit DotProbe();

    Stimul* getNeutral() const;
    void setNeutral(unique_ptr<Stimul> && value);

    Stimul* getSalient() const;
    void setSalient(unique_ptr<Stimul> && value);

    Dot* getDot() const;
    void setDot(unique_ptr<Dot> && value);

    Cross* getCross() const;
    void setCross(unique_ptr<Cross> && value);

    Stimul* getStimulWithDot() const;

    int getTreshold() const;
    void setTreshold(int value);

    int getDelay() const;
    void setDelay(int value);

    LayoutMode getLayoutMode() const;
    void setLayoutMode(const LayoutMode& value);

    QLayout* getLayout() const;

    DotProbePhase getPhase() const;

    void replaceNeutralWithDot();
    void replaceSalientWithDot();

    void start();
    int stop();

private:
    void startCross();
    void startStimuli();

    QTime time;
    int treshold = 50;
    int delay = 1000;
    DotProbePhase phase = DotProbePhase::Cross;
    LayoutMode layoutMode = LayoutMode::Horizontal;
    Stimul* stimulWithDot;
    unique_ptr<Stimul> neutral;
    unique_ptr<Stimul> salient;
    unique_ptr<QLayout> layout;
    unique_ptr<Dot> dot;
    unique_ptr<Cross> cross;
};

#endif // DOTPROBE_H
