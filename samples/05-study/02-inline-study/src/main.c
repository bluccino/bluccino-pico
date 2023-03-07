// main.c - 02-inline-study
#include "pico/log.h"

static PI_txt txt = "study memory usage";

static void heading(int i)
{
  pi_log(0,PI_G "Block %d",i);
}

int main(void)
{
  int i = 0;
  pi_hello(10,"let's go ...");

    // 1st block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

    // 2nd block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

    // 3rd block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

    // 4th block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

    // 5th block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

    // 6th block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

    // 7th block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

    // 8th block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

    // 9th block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

    // 10th block

  heading(++i);
  pi_log(0,txt);  pi_log(1,txt);  pi_log(2,txt);  pi_log(3,txt);  pi_log(4,txt);
  pi_log(5,txt);  pi_log(6,txt);  pi_log(7,txt);  pi_log(8,txt);  pi_log(9,txt);
  pi_sleep(500*1000);

  pi_log(0,PI_G "done!");
  return 0;
}
