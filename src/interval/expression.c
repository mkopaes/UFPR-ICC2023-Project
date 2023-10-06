#include <stdio.h>
#include <stdlib.h>

#include "../../include/interval.h"

struct Expression *readExpression() {
  struct Expression *expr = malloc(sizeof(struct Expression));

  float x1, x2, x3, x4, x5;
  char o1, o2, o3, o4;

  scanf("%f %c %f %c %f %c %f %c %f", &x1, &o1, &x2, &o2, &x3, &o3, &x4, &o4,
        &x5);

  expr->nums[0].f = x1;
  expr->nums[1].f = x2;
  expr->nums[2].f = x3;
  expr->nums[3].f = x4;
  expr->nums[4].f = x5;
  expr->ops[0] = o1;
  expr->ops[1] = o2;
  expr->ops[2] = o3;
  expr->ops[3] = o4;

  return expr;
}
