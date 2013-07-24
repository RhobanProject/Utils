#ifndef SCORE_HPP
#define SCORE_HPP

#include <vector>
#include <stdio.h>

#include "logging/term_display.h"

#include "Mark.hpp"

/* multi criterion score computation */
// Using heritage of mark since a score can be used as a Mark of a score
class Score : public Mark {//TODO pass Mark to private and handle conflicts
private:
  std::vector<Mark *> marks;
  double total_weight;

  using Mark::showScore;
  void showScore(std::string name,
                 int detailLevel,
                 std::string prefix = "") const;

public:
  std::string name;

  Score(std::string name,
        double weight = 1.0,
        double value = 0.0) : Mark(name, "", weight, value),
                              total_weight(0.0),
                              name(name) {};

  virtual ~Score(){
    for (unsigned int i = 0; i < marks.size(); i++){
      delete marks[i];
    }
  };

  void updateName(std::string newName);

  double getScore() const;

  // Score shouldn't be touched once this method has been called
  void addMark(Mark * m);

  void showMarks(int detailLevel = 0) const;
  
  /* weights are relative,
   * if value is less than min_value, then score will be 0 (note eliminatoire)
   * value is in [0,1] */
  void mark(std::string mark_name,
            std::string note,
            double weight,
            double value,
            double min_value = -1.0);

  /* the more the value is small the more the mark is high,
   * value and max_value must be positive 
   * if value is less than min_value, then the score will be 0 */
  void mark_from_comparison(std::string mark_name,
                            std::string note,
                            double weight,
                            double value,
                            double tolerance,
                            double max_value,
                            double kill_value = -1.0);

  void pp(FILE * output = stdout);
};

#endif//SCORE_HPP
