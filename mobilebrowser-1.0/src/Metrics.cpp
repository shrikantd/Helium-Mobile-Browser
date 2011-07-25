#include "Metrics.h"

Metrics::Metrics(QObject *parent) :
    QObject(parent)
{
}


int Metrics::topBarHeight() {
    return 100;
}

int Metrics::bottomBarHeight() {
    return 70;
}

int Metrics::tabButtonPixelSize() {
    return 20;
}
