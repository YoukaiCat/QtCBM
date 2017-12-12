#ifndef DOT_H
#define DOT_H

#include <QString>
#include <QWidget>

class Dot
{
public:
    Dot(const QString& marker);
    virtual ~Dot();

    virtual QWidget* getWidget() = 0;

    QString getMarker() const;
    void setMarker(const QString& value);

private:
    QString marker;
};

#endif // DOT_H
