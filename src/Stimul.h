#ifndef STIMUL_H
#define STIMUL_H

#include <QObject>
#include <QStackedWidget>

class Stimul : public QObject
{
    Q_OBJECT
public:
    explicit Stimul();
    explicit Stimul(bool neutral);

    bool isNeutral() const;
    void setNeutral(bool value);

    virtual QStackedWidget* getWidget() = 0;

    virtual void replaceWith(QWidget* widget) = 0;
    virtual void hide() = 0;

protected:
    QStackedWidget stack;
    bool neutral = true;
};

#endif // STIMUL_H
