#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  double current_balance = initial;
  int current_age = startAge;
  while (working.months > 0) {
    printf("Age %3d month %2d you have $%.2lf\n",
           (current_age / 12),
           (current_age % 12),
           current_balance);
    current_balance =
        current_balance + current_balance * working.rate_of_return + working.contribution;
    working.months--;
    current_age++;
  }

  while (retired.months > 0) {
    printf("Age %3d month %2d you have $%.2lf\n",
           (current_age / 12),
           (current_age % 12),
           current_balance);
    current_balance =
        current_balance + current_balance * retired.rate_of_return + retired.contribution;
    retired.months--;
    current_age++;
  }
}

int main(void) {
  int startAge = 327;
  double saving = 21345.00;
  retire_info_t working, retiring;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = (0.045 / 12);
  retiring.months = 384;
  retiring.contribution = -4000;
  retiring.rate_of_return = (0.01 / 12);
  retirement(startAge, saving, working, retiring);
  return 0;
}
