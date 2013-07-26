#ifndef MARK_HPP
#define MARK_HPP

#include <string>

#define WANTED_SCORE 0.7

#define SUCCESS_COLOR TC_YELLOW//TODO yellow looks green, is this normal?
#define MITIGATED_COLOR TC_MAGENTA
#define FAILURE_COLOR TC_RED

class Mark{
protected:
  std::string markName;
  double weight;
  double score;
  bool criticalFail;//Some marks can fail critically
  std::string annotation;//The true value examinated (0.003m, 25.32ms, ...)

  std::string formattedScore() const;
  std::string formattedWeight() const;
  std::string formattedAnnotation() const;

public:

  static const unsigned int nameSize = 8;
  static const unsigned int markNameSize = 30;
  static const unsigned int noteSize = 10;

  Mark() : markName("default"), weight(0.0), score(1.0), criticalFail(false) {};

  Mark(std::string name) : markName(name),
                           weight(0.0),
                           score(1.0),
                           criticalFail(false) {};
  // If minValue is not specified, it isn't used
  Mark(std::string name,
       std::string note,
       double w,
       double value,
       double minValue = -1.0);

  virtual ~Mark() {};

  double getWeight() const{ return weight;};
  virtual double getScore() const{ return score;};
  std::string getName() const{ return markName;};
  std::string getAnnotation() const{ return annotation;};

  double isFailed() const{ return criticalFail;};

  // Show score
  void showScore(std::string callerName,
                 std::string prefix = "") const;

  virtual void showScore(std::string callerName,
                         int detailLevel,
                         std::string prefix = "") const {
    showScore(callerName, prefix);
  };

  // Show val and Score if score is < WANTED_SCORE
  void show(std::string callerName) const;
};
#endif//MARK_HPP
