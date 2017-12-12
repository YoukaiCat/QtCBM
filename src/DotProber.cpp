#include "DotProber.h"
#include "TextStimul.h"
#include "DotLabel.h"
#include "CrossLabel.h"

#include <QRandomGenerator>
#include <QDirIterator>
#include <QTextStream>
#include <QLayout>
#include <QSet>
#include <QtDebug>

DotProber::DotProber()
{}

QList<QString> DotProber::loadStimuliFromDirectory(const QString& value)
{
    QSet<QString> words;
    QDirIterator dirIt(value, QDirIterator::Subdirectories |
                       QDirIterator::FollowSymlinks);
    while (dirIt.hasNext()) {
        QString path = dirIt.next();
        QFile f(path);
        QFileInfo fi(path);
        if (fi.completeSuffix() == "txt") {
            f.open(QIODevice::ReadOnly);
            QTextStream in(&f);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (!line.isEmpty()) {
                    words << line;
                }
            }
        }
    }
    return words.toList();
}

QString DotProber::getRandomStimuli(const QList<QString>& stimuli)
{
    if (stimuli.size() > 0) {
        int randIndex = QRandomGenerator::global()->bounded(0, stimuli.size());
        return stimuli.at(randIndex);
    } else {
        return QString("");
    }
}

bool DotProber::getIsRunning() const
{
    return isRunning;
}

void DotProber::setIsRunning(bool value)
{
    isRunning = value;
}

void DotProber::start()
{
    if (!isRunning) {
        isRunning = true;

        probe = make_unique<DotProbe>();

        neutralStimuli = loadStimuliFromDirectory(dirWithNeutralStimuli);
        salientStimuli = loadStimuliFromDirectory(dirWithSalientStimuli);

        auto neutral = make_unique<TextStimul>(getRandomStimuli(neutralStimuli), true);
        auto salient = make_unique<TextStimul>(getRandomStimuli(salientStimuli), false);

        unique_ptr<Dot> dot;
        int randint = QRandomGenerator::global()->bounded(0, 2);
        if (randint == 0) {
            dot = make_unique<DotLabel>("<");
        } else {
            dot = make_unique<DotLabel>(">");
        }
        auto cross = make_unique<CrossLabel>("+");

        probe->setNeutral(std::move(neutral));
        probe->setSalient(std::move(salient));
        probe->setDot(std::move(dot));
        probe->setCross(std::move(cross));
        probe->setDelay(delay);
        probe->setLayoutMode(layoutMode);

        if (training) {
            probe->setTreshold(90);
        } else {
            probe->setTreshold(50);
        }

        widget->setLayout(probe->getLayout());

        probe->start();
    }
}

void DotProber::stop(const QString& marker)
{
    if (isRunning) {
        if (probe->getPhase() == DotProbePhase::Dot) {
            if (probe->getDot()->getMarker() == marker) {
                ProbeResult result;
                result.setNeutral(probe->getStimulWithDot()->isNeutral());
                result.setDelay(probe->stop());
                result.setTimestamp(QTime::currentTime());
                emit resultReady(result);
                qDebug() << "Stop: Ok";
            } else {
                qDebug() << "Stop: Marker check failed";
            }
        } else {
            qDebug() << "Stop: Double stop";
        }
        isRunning = false;
    }
}

QWidget* DotProber::getWidget() const
{
    return widget;
}

void DotProber::setWidget(QWidget* value)
{
    widget = value;
}

bool DotProber::getTraining() const
{
    return training;
}

void DotProber::setTraining(bool value)
{
    training = value;
}

LayoutMode DotProber::getLayoutMode() const
{
    return layoutMode;
}

void DotProber::setLayoutMode(const LayoutMode& value)
{
    layoutMode = value;
}

int DotProber::getDelay() const
{
    return delay;
}

void DotProber::setDelay(int value)
{
    delay = value;
}

QString DotProber::getDirectoryWithNeutralStimuli() const
{
    return dirWithNeutralStimuli;
}

void DotProber::setDirectoryWithNeutralStimuli(const QString& value)
{
    dirWithNeutralStimuli = value;
}

QString DotProber::getDirectoryWithSalientStimuli() const
{
    return dirWithSalientStimuli;
}

void DotProber::setDirectoryWithSalientStimuli(const QString& value)
{
    dirWithSalientStimuli = value;
}
