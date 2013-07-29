#include "ScoringTest.h"

#include <ostream>

#include "tests/runTests.h"
#include "scoring/Score.hpp"

int main(){
  runTests<ScoringTest>("Testing Scores");
}

double deltaDouble = 0.000001;

void ScoringTest::testWeight(){
  Score s("Testing Score");
  Mark * m = new Mark("Test Mark 1", "", 2.0, 0.5);
  Mark * m2 = new Mark("Test Mark 2", "", 1.0, 0.2);
  s.addMark(m);
  s.addMark(m2);
  // (0.5 * 2 + 0.2) / 3 = 0.4
  assertEqualsDelta(s.getScore(), 0.4, deltaDouble);
}

/* If a mark is under kill value, then score should be failed and getScore
 * should return 0
 */
void ScoringTest::testKillValue(){
  Score s("TestingScore");
  Mark * m = new Mark("Test Mark 1", "", 2.0, 0.5);
  Mark * m2 = new Mark("Test Mark 2", "", 1.0, 0.2, 0.3);
  s.addMark(m);
  s.addMark(m2);
  // (0.5 * 2 + 0.2) / 3 = 0.4
  assertEqualsDelta(s.getScore(), 0.0, deltaDouble);
  assertTrue(s.isFailed());
}
void ScoringTest::testUpdate(){
  Score s("TestingScore");
  Mark * m = new Mark("Test Mark 1", "", 2.0, 0.5);
  Mark * m2 = new Mark("Test Mark 2", "", 1.0, 0.2, 0.3);
  s.addMark(m);
  s.addMark(m2);
  // (0.5 * 2 + 0.8) / 3 = 0.6
  m2->updateScore(0.8);
  assertEqualsDelta(s.getScore(), 0.6, deltaDouble);
  assertFalse(s.isFailed());
}

void 
ScoringTest::_run(){
  testWeight();
  testKillValue();
  testUpdate();
}
