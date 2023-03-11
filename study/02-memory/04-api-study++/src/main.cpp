// main.cpp - 04-api-study++
#include "pico/api.h"
#define  pi pico

static PI_txt txt = "study memory usage";

static void heading(int i)
{
  pi.log(0,PI_G "Block %d",i);
}

int main(void)
{
  int i = 0;
  pi_hello(10,"let's go ...");

    // 1st block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

    // 2nd block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

    // 3rd block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

    // 4th block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

    // 5th block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

    // 6th block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

    // 7th block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

    // 8th block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

    // 9th block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

    // 10th block

  heading(++i);
  pi.log(0,txt);  pi.log(1,txt);  pi.log(2,txt);  pi.log(3,txt);  pi.log(4,txt);
  pi.log(5,txt);  pi.log(6,txt);  pi.log(7,txt);  pi.log(8,txt);  pi.log(9,txt);
  pi.sleep(500*1000);

  pi.log(0,PI_G "done!");
  return 0;
}
