#include "Score.hpp"

#include <iostream>
#include <typeinfo>

using namespace std;

void Score::addMark(Mark * m){
  double total_score = total_weight * score
    + m->getWeight() * m->getScore();
  total_weight += m->getWeight();
  score = total_score / total_weight;
  if (m->isFailed())
    null_score = true;
  marks.push_back(m);
}

void Score::updateName(string newName){
  name = newName;
  markName = newName;
}

void Score::showScore(std::string name, int detailLevel) const{
  for (unsigned int i = 0; i < marks.size(); i++){
    marks[i]->showScore(markName);
    if (detailLevel > 0 && dynamic_cast<Score *>(marks[i]) != 0) {
      marks[i]->showScore(markName, detailLevel - 1);
    }
  }
}

void Score::showMarks(int detailLevel) const{
  showScore("", detailLevel);
}

double Score::getScore() const{
  if (null_score) return 0.0;
  if (total_weight == 0) return 1.0;
  return score;
};

void Score::mark(string mark_name,
                 string note,
                 double weight,
                 double value,
                 double min_value) {
  Mark * m = new Mark(mark_name, note, weight, value, min_value);
  m->show(name);
  addMark(m);
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
