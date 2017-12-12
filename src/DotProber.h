#ifndef DOTPROBER_H
#define DOTPROBER_H

#include "DotProbe.h"
#include "ProbeResult.h"

#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::move;

class DotProber : public QObject
{
    Q_OBJECT
public:
    DotProber();

    void start();
    void stop(const QString& marker);

    QWidget* getWidget() const;
    void setWidget(QWidget* value);

    bool getTraining() const;
    void setTraining(bool value);

    LayoutMode getLayoutMode() const;
    void setLayoutMode(const LayoutMode& value);

    int getDelay() const;
    void setDelay(int value);

    QString getDirectoryWithNeutralStimuli() const;
    void setDirectoryWithNeutralStimuli(const QString& value);

    QString getDirectoryWithSalientStimuli() const;
    void setDirectoryWithSalientStimuli(const QString& value);

    bool getIsRunning() const;
    void setIsRunning(bool value);

signals:
    void stopped();
    void resultReady(const ProbeResult& result);

private:
    QList<QString> loadStimuliFromDirectory(const QString& value);
    QString getRandomStimuli(const QList<QString>& stimuli);

    bool isRunning = false;
    bool training = false;
    LayoutMode layoutMode = LayoutMode::Horizontal;
    int delay = 1000;
    QString dirWithNeutralStimuli;
    QString dirWithSalientStimuli;
    QList<QString> neutralStimuli;
    QList<QString> salientStimuli;
    unique_ptr<DotProbe> probe;
    QWidget* widget;
};

#endif // DOTPROBER_H
