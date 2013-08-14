#include "Score.hpp"

#include <iostream>
#include <typeinfo>

using namespace std;

void Score::addMark(Mark * m){
  marks.push_back(m);
}

void Score::updateName(string newName){
  markName = newName;
}

void Score::showScore(string name,
                      int detailLevel,
                      string prefix) const{
  showScore(name, prefix);
  if (detailLevel == 0){
    return;
  }
  string nextPrefix = prefix + "    ";
  for (unsigned int i = 0; i < marks.size(); i++){
    Score * subScore = dynamic_cast<Score *>(marks[i]);
    if (subScore != 0) {
      subScore->showScore("", detailLevel - 1, nextPrefix);
    }
    else{
      marks[i]->showScore("", nextPrefix);
    }
  }
}

void Score::showMarks(int detailLevel) const{
  showScore("", detailLevel);
}

bool Score::isFailed() const{
  for (unsigned int i = 0; i < marks.size(); i++){
    if (marks[i]->isFailed()){
      return true;
    }
  }
  return false;
}

double Score::getScore() const{
  // Since members might be modified at any time, score must be recomputed
  // when asked
  if (isFailed()) return 0.0;
  double sumScore = 0.0;
  double sumWeight = 0.0;
  for (unsigned int i = 0; i < marks.size(); i++){
    double tmpWeight = marks[i]->getWeight();
    sumScore += marks[i]->getScore() * tmpWeight;
    sumWeight += tmpWeight;
  }
  if (sumWeight == 0.0) return 1;
  return sumScore / sumWeight;
};

void Score::mark(string mark_name,
                 string note,
                 double weight,
                 double value,
                 double min_value) {
  addMark(new Mark(mark_name, note, weight, value, min_value));
}

void Score::mark_from_comparison(string mark_name,
                                 string note,
                                 double weight,
                                 double value,
                                 double tolerance,
                                 double max_value,
                                 double kill_value) {
  Mark m;
  value -= tolerance;
  max_value -= tolerance;
  if (value < 0) value = 0.0;
  if (max_value < 0) max_value = 0.0;
  if (kill_value == -1){
    mark(mark_name,
         note,
         weight,
         (max_value - value) / max_value);
  }
  else{
    kill_value -= tolerance;
    if (kill_value > max_value) kill_value = max_value;
    mark(mark_name,
         note,
         weight,
         (max_value - value) / max_value,
         (max_value - kill_value) / max_value);
  }
}

void Score::pp(FILE * output) {
  if (getScore() >= WANTED_SCORE) { TERM_COLOR(SUCCESS_COLOR); }
  //TODO avoid constant here, use something like WANTED_SCORE
  else if (getScore() >= 0.50) { TERM_COLOR(MITIGATED_COLOR); }
  else { TERM_COLOR(FAILURE_COLOR); }
  fprintf(output, "%0.0f%%", getScore() * 100);
  TERM_COLOR(TC_DEFAULT);
}
