#include <stdint.h>

#ifndef INTERVAL_H
#define INTERVAL_H

typedef union {
  int32_t i;
  float f;
} FloatT;

struct Interval {
  FloatT first;
  FloatT second;
};

struct Expression {
  FloatT nums[OPS + 1];
  char ops[OPS];
};

struct Expression *readExpression();

struct Interval *makeInterval(float num);

struct Interval **makeIntervalVector(struct Expression *expr);

struct Interval *intervalSum(struct Interval a, struct Interval b);

struct Interval *intervalSub(struct Interval a, struct Interval b);

struct Interval *intervalMult(struct Interval a, struct Interval b);

struct Interval *intervalDiv(struct Interval a, struct Interval b);

struct Interval **calculate(struct Expression expression,
                            struct Interval **intervalVector);

float absError(struct Interval interval);

float relError(struct Interval interval);

int calcULPs(struct Interval interval);

void printAnswer(struct Expression expression, struct Interval **intervalVector,
                 struct Interval **ansIntervalVector);

void freeExpression(struct Expression *expression);

void freeIntervalVector(struct Interval **interval);

void freeAnsIntervalVector(struct Interval **interval);

#endif /* INTERVAL_H */
