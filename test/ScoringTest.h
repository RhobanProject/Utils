#ifndef SCORING_TEST_H
#define SCORING_TEST_H

#include "tests/TestCase.h"

class ScoringTest : public TestCase
{
protected:
  virtual void _run();

  void testWeight();
  void testKillValue();
  void testUpdate();
  
};
#endif//SCORING_TEST_H
