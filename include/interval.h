#include <stdint.h>

#ifndef INTERVAL_H
#define INTERVAL_H

typedef struct {
    double min;
    double max;
} Interval;

void createInterval(double num, Interval *inter);

Interval intervalSum(Interval a, Interval b);

Interval intervalSub(Interval a, Interval b);

Interval intervalMult(Interval a, Interval b);

Interval intervalDiv(Interval a, Interval b);

Interval intervalPow(Interval a, int b);

double intervalMean(Interval a);

#endif /* INTERVAL_H */
