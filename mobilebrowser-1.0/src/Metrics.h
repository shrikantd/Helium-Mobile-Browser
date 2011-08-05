#ifndef METRICS_H
#define METRICS_H

#include <QObject>

class Metrics : public QObject
{
    Q_OBJECT
public:
    Metrics(QObject *parent = 0);

    Q_PROPERTY( int topBarHeight READ topBarHeight );
    Q_PROPERTY( int bottomBarHeight READ bottomBarHeight);

    Q_PROPERTY( int tabButtonPixelSize READ tabButtonPixelSize );

    int topBarHeight();
    int bottomBarHeight();

    int tabButtonPixelSize();
};

#endif // METRICS_H
