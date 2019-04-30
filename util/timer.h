#ifndef BASIC_TIMER
#define BASIC_TIMER

#include "types_and_headers.h"

/*// Timer
  struct timeval _tval;
  double get_clock() {
  struct timeval _tval; int ok;
  ok = gettimeofday(&_tval, 0);
  if (ok<0) { std::printf("gettimeofday error");}
  return (_tval.tv_sec * 1.0 + _tval.tv_usec * 1.0E-6);
  }*/
#pragma once
#include <sys/time.h>
class Timer
{
  public:
    struct timeval start, end;
    struct timezone tz;
    double timeSpent;
    string name;

    Timer(string tempName) : name(tempName)
  {
    timeSpent=0.;

  }


    void Start()
    {
      gettimeofday(&start, &tz);
    }

    void Stop()
    {
      gettimeofday(&end,   &tz);
      timeSpent += (double)(end.tv_sec-start.tv_sec) +
        1.0e-6*(double)(end.tv_usec-start.tv_usec);
    }

    void Clear()
    {
      timeSpent=0.0;
    }

    double Time()
    {
      return timeSpent;

    }

};

#endif
