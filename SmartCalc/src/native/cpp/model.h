#ifndef CPP3_SMART_CALC_V2_0_HEADERS_MODEL_H
#define CPP3_SMART_CALC_V2_0_HEADERS_MODEL_H

#include "../../main/java/school21/smartcalc/application/smartcalc/school21_smartcalc_application_smartcalc_HelloController.h"
#include <jni.h>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>

class ExampleModel {
 public:
  ExampleModel() : data_(0){};
  int Calculate(std::string& func, std::string value_of_x);
  std::string GetNumber(char** ptr_func);
  double GetData();
  void CleanData();

 private:
  double data_;
  double x_;
  std::queue<std::string> polish_notation_;
  int GetRang(std::string sign);
  bool IsThisDigit(char chr);
  std::string GetOperation(char** ptr_func);
  void ToReversePolishNotation(std::string& sign);
  void EvaluateReversePolishNotation(std::queue<std::string> polish_notations);
  double PerformOperationWithTwoOperands(std::string operation, double operand1,
                                         double operand2);
  double PerformOperationWithOneOperands(std::string operation,
                                         double operand1);
  void AddOperation(std::string operation, std::stack<std::string>& signs);
  void AddBracketsInPolishNotation(std::string operation,
                                   std::stack<std::string>& signs);
};

#endif  // CPP3_SMART_CALC_V2_0_HEADERS_MODEL_H
