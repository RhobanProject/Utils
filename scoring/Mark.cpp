#include <iostream>
#include <sstream>

#include "logging/term_display.h"

//TODO this include is here because logging/term_display.h doesn't include
// stdio.h, this should be fixed
#include <stdio.h>

#include "Mark.hpp"

using namespace std;

Mark::Mark(string name,
           string note,
           double w,
           double value,
           double minValue){
  if (value > 1.0) value = 1.0;
  if (value < 0.0) value = 0.0;
  criticalFail = value <= minValue;
  annotation = note;
  weight = w;
  markName = name;
  score = value;
}

string Mark::formattedScore() const{
  ostringstream oss;
  oss << getScore() * 100;
  string s = oss.str();
  double tmp = score * 100;
  int iteration = 0;
  while (tmp < 100 && iteration < 2){
    tmp *= 10;
    iteration++;
    s = " " + s;
  }
  if (s.find('.') == string::npos){
    s += '.';
  }    
  s.resize(6, '0');
  return s;
}

//It is assumed that weight should be inferior to 10
string Mark::formattedWeight() const{
  ostringstream oss;
  oss << weight;
  string s = oss.str();
  if (s.find('.') == string::npos){
    s += ".";
  }
  s.resize(4, '0');
  return s;
}

string Mark::formattedAnnotation() const{
  string tmp(annotation);
  while (tmp.length() < noteSize){
    tmp = " " + tmp;
  }
  return tmp;
}

void Mark::showScore(string callerName) const{
  string formattedMarkName = markName;
  formattedMarkName.resize(markNameSize, ' ');
  string formattedCallerName = callerName;
  formattedCallerName.resize(nameSize, ' ');
  
  
  if (criticalFail){
    TERM_COLOR(FAILURE_COLOR);
    cout << "[" << formattedMarkName << " makes " << formattedCallerName
         << " null";
  }
  else{
    if (getScore() < WANTED_SCORE){
      TERM_COLOR(MITIGATED_COLOR);
    }
    else{
      TERM_COLOR(SUCCESS_COLOR);
    }

    cout << '[' << formattedCallerName << ": " << formattedMarkName << ": "
         << formattedScore() << "% (weight = " << formattedWeight() << ")";
  }
  if (getAnnotation().length() != 0){
    cout << " '" << formattedAnnotation() << "'";
  }
  cout << ']' << endl;
  TERM_COLOR(TC_DEFAULT);
  
}

void Mark::show(string callerName) const{
  if (score < WANTED_SCORE){
    showScore(callerName);
  }
}
