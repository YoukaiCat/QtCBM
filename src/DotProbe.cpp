#include "DotProbe.h"

#include <QTimer>
#include <QRandomGenerator>

DotProbe::DotProbe()
    : layout(make_unique<QHBoxLayout>())
{}

Stimul* DotProbe::getNeutral() const
{
    return neutral.get();
}

void DotProbe::setNeutral(unique_ptr<Stimul> && value)
{
    neutral = move(value);
}

Stimul* DotProbe::getSalient() const
{
    return salient.get();
}

void DotProbe::setSalient(unique_ptr<Stimul> && value)
{
    salient = move(value);
}

void DotProbe::replaceNeutralWithDot()
{
    neutral->hide();
    neutral->replaceWith(dot->getWidget());
    time.start();
    phase = DotProbePhase::Dot;
}

void DotProbe::replaceSalientWithDot()
{
    salient->hide();
    salient->replaceWith(dot->getWidget());
    time.start();
    phase = DotProbePhase::Dot;
}

void DotProbe::start()
{
    neutral->getWidget()->hide();
    salient->getWidget()->hide();
    startCross();
}

int DotProbe::stop()
{
    return time.elapsed();
}

QLayout* DotProbe::getLayout() const
{
    QWidget* neutralWidget = neutral->getWidget();
    QWidget* salientWidget = salient->getWidget();
    int randint = QRandomGenerator::global()->bounded(0, 2);
    if (randint == 0) {
        std::swap(neutralWidget, salientWidget);
    }
    layout->addWidget(neutralWidget);
    layout->addWidget(cross->getWidget());
    layout->addWidget(salientWidget);
    return layout.get();
}

Cross* DotProbe::getCross() const
{
    return cross.get();
}

void DotProbe::setCross(unique_ptr<Cross> && value)
{
    cross = move(value);
}

Stimul* DotProbe::getStimulWithDot() const
{
    return stimulWithDot;
}

void DotProbe::startCross()
{
    phase = DotProbePhase::Cross;
    cross->getWidget()->show();
    QTimer::singleShot(1000, this, &DotProbe::startStimuli);
}

void DotProbe::startStimuli()
{
    phase = DotProbePhase::Stimuli;
    cross->getWidget()->hide();
    neutral->getWidget()->show();
    salient->getWidget()->show();
    int randint = QRandomGenerator::global()->bounded(0, 100);
    if (randint < treshold) {
        stimulWithDot = neutral.get();
        QTimer::singleShot(delay, this, &DotProbe::replaceNeutralWithDot);
        QTimer::singleShot(delay, salient.get(), &Stimul::hide);
    } else {
        stimulWithDot = salient.get();
        QTimer::singleShot(delay, this, &DotProbe::replaceSalientWithDot);
        QTimer::singleShot(delay, neutral.get(), &Stimul::hide);
    }
}

DotProbePhase DotProbe::getPhase() const
{
    return phase;
}

LayoutMode DotProbe::getLayoutMode() const
{
    return layoutMode;
}

void DotProbe::setLayoutMode(const LayoutMode& value)
{
    if (value == LayoutMode::Horizontal) {
        layout = make_unique<QHBoxLayout>();
    } else {
        layout = make_unique<QVBoxLayout>();
    }
    layoutMode = value;
}

int DotProbe::getDelay() const
{
    return delay;
}

void DotProbe::setDelay(int value)
{
    delay = value;
}

int DotProbe::getTreshold() const
{
    return treshold;
}

void DotProbe::setTreshold(int value)
{
    treshold = value;
}

Dot* DotProbe::getDot() const
{
    return dot.get();
}

void DotProbe::setDot(unique_ptr<Dot> && value)
{
    dot = move(value);
}
