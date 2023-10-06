#include <stdio.h>

#include "../../include/interval.h"

void printInterval(struct Interval interval) {
  printf("[%1.8e,%1.8e]", interval.first.f, interval.second.f);
}

void printOps(struct Expression expr) {
  for (int i = 0; i < OPS; i++) {
    printInterval(*makeInterval(expr.nums[i].f));
    printf(" %c ", expr.ops[i]);
  }
  printInterval(*makeInterval(expr.nums[4].f));
}

void printAnswer(struct Expression expression, struct Interval **intervalVector,
                 struct Interval **ansIntervalVector) {
  printf("1:\n");
  printInterval(*intervalVector[0]);
  printf(" %c ", expression.ops[0]);
  printInterval(*intervalVector[1]);
  printf(" = ");
  printInterval(*ansIntervalVector[0]);
  printf("\n");
  printf("EA: %1.8e; ", absError(*ansIntervalVector[0]));
  printf("ER: %1.8e; ", relError(*ansIntervalVector[0]));
  printf("ULPs: %d;", calcULPs(*ansIntervalVector[0]));
  printf("\n\n");

  for (int i = 1; i < OPS; i++) {
    printf("%d:\n", i + 1);
    printInterval(*ansIntervalVector[i - 1]);
    printf(" %c ", expression.ops[i]);
    printInterval(*intervalVector[i + 1]);
    printf(" = ");
    printInterval(*ansIntervalVector[i]);
    printf("\n");

    printf("EA: %1.8e; ", absError(*ansIntervalVector[i]));
    printf("ER: %1.8e; ", relError(*ansIntervalVector[i]));
    printf("ULPs: %d;", calcULPs(*ansIntervalVector[i]));
    printf("\n\n");
  }
}
