#ifndef TEXTSTIMUL_H
#define TEXTSTIMUL_H

#include "Stimul.h"

#include <QLabel>

class TextStimul : public Stimul
{
    Q_OBJECT
public:
    explicit TextStimul(QString text);
    explicit TextStimul(QString text, bool neutral);

    QString getText() const;
    void setText(const QString& value);

    virtual QStackedWidget* getWidget();

    virtual void replaceWith(QWidget* widget);
    virtual void hide();

private:
    QLabel text;
};

#endif // TEXTSTIMUL_H
