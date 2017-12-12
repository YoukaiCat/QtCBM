#ifndef CROSS_H
#define CROSS_H

#include <QString>
#include <QWidget>

class Cross
{
public:
    Cross(const QString& marker);
    virtual ~Cross();

    virtual QWidget* getWidget() = 0;

    QString getMarker() const;
    void setMarker(const QString& value);

private:
    QString marker;
};

#endif // CROSS_H
