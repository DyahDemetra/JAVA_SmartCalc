#include "model.h"

int ExampleModel::Calculate(std::string& func, std::string value_of_x) {
  char* ptr_x = &value_of_x[0];
  x_ = stod(GetNumber(&ptr_x));
  if (*ptr_x != '\0') {
    throw std::runtime_error("Incorrect X");
  }
  ToReversePolishNotation(func);
  EvaluateReversePolishNotation(polish_notation_);
  while (!polish_notation_.empty()) polish_notation_.pop();
  return 1;
}

void ExampleModel::CleanData() {
  data_ = 0;
  x_ = 0;
  while (!polish_notation_.empty()) polish_notation_.pop();
}

int ExampleModel::GetRang(std::string sign) {
  int flag = 0;
  if (sign == "sin" || sign == "cos" || sign == "tan" || sign == "acos" ||
      sign == "asin" || sign == "atan" || sign == "sqrt" || sign == "log" ||
      sign == "ln" || sign == "mod" || sign == "abs" ) {
    flag = 4;
  } else if (sign == "^") {
    flag = 3;
  } else if (sign == "*" || sign == "/") {
    flag = 2;
  } else if (sign == "+" || sign == "-" || sign == "_") {
    flag = 1;
  } else if (sign == "(" || sign == ")") {
    flag = -1;
  }
  return flag;
}

double ExampleModel::GetData() { return data_; }

std::string ExampleModel::GetNumber(char** ptr_func) {
  std::string num;
  bool dot_found = false;
  bool e_found = false;
  if (**ptr_func == '-') {
    num += '-';
    (*ptr_func)++;
  }
  while (IsThisDigit(**ptr_func) || **ptr_func == '.' || **ptr_func == 'e') {
    if (**ptr_func == '.') {
      if (dot_found) {
        CleanData();
        throw std::runtime_error(
            "Invalid number fccormat: multiple dots found");
      }
      dot_found = true;
    }
    if (**ptr_func == 'e') {
      if (e_found) {
        CleanData();
        throw std::runtime_error(
            "Invalid number fccormat: multiple \"e\" found");
      }
      if ((*(*ptr_func + 1) == '-') || (*(*ptr_func + 1) == '+')) {
        num += 'e';
        (*ptr_func)++;
      }
      if (!IsThisDigit(*(*ptr_func + 1))) {
        CleanData();
        throw std::runtime_error("Incorrect num");
      }
      e_found = true;
    }
    if (**ptr_func == 'x') {
      num += 'x';
      (*ptr_func)++;
      return num;
    }
    num += **ptr_func;
    (*ptr_func)++;
  }
  return num;
}

std::string ExampleModel::GetOperation(char** ptr_func) {
  std::string operation;
  while (!IsThisDigit(**ptr_func) && **ptr_func != '\0') {
    if (**ptr_func != ' ') {
      operation += **ptr_func;
      (*ptr_func)++;
      if (GetRang(operation) != 0) {
        break;
      }
    }
  }
  if (GetRang(operation) == 0 && **ptr_func != '\0') {
    CleanData();
    throw std::runtime_error("Unknown operation");
  }
  return operation;
}

void ExampleModel::ToReversePolishNotation(std::string& func) {
  char* ptr = &func[0];
  std::stack<std::string> signs;
  while (*ptr != '\0') {
    if (IsThisDigit(*ptr) || ((*ptr == '-' && IsThisDigit(*(ptr + 1))) &&
                              (*(ptr - 1) != '(' && *(ptr - 1) != ')'))) {
      polish_notation_.push(GetNumber(&ptr));
    }
    if (!IsThisDigit(*ptr)) {
      std::string operation = GetOperation(&ptr);
      if (operation == "-" && !IsThisDigit(*ptr)) operation = "_";
      if (operation == "(" && *(ptr) == ')') {
        CleanData();
        throw std::runtime_error("Meaningless brackets");
      }
      AddOperation(operation, signs);
    }
  }
  while (!signs.empty()) {
    polish_notation_.push(signs.top());
    signs.pop();
  }
  if (!IsThisDigit(*(ptr - 1)) && *(ptr - 1) != ')') {
    CleanData();
    throw std::runtime_error("Function can't ending by operation");
  }
}

void ExampleModel::EvaluateReversePolishNotation(
    std::queue<std::string> polish_notations) {
  std::stack<double> stk;
  while (polish_notations.front() != "\0" && !polish_notations.empty()) {
    std::string element = polish_notations.front();
    polish_notations.pop();
    if (IsThisDigit(element[0]) ||
        (element[0] == '-' && IsThisDigit(element[1]))) {
      if (element == "x")
        stk.push(x_);
      else if (element == "-x")
        stk.push(-x_);
      else
        stk.push(stod(element));
    } else if (stk.empty()) {
      CleanData();
      throw std::runtime_error("Functions cannot contain only operations.");
    } else {
      double operand2 = stk.top();
      stk.pop();
      double result;
      if ((GetRang(element) == 4 && element != "mod") || element == "_") {
        result = PerformOperationWithOneOperands(element, operand2);
      } else {
        if (stk.empty()) {
          CleanData();
          throw std::runtime_error("More operations than operands");
        }
        double operand1 = stk.top();
        stk.pop();
        result = PerformOperationWithTwoOperands(element, operand1, operand2);
      }
      stk.push(result);
    }
  }
  data_ = stk.top();
  if (stk.size() != 1) {
    CleanData();
    throw std::runtime_error("Error!");
  }
}

double ExampleModel::PerformOperationWithTwoOperands(std::string operation,
                                                     double operand1,
                                                     double operand2) {
  if (operation == "+")
    return operand1 + operand2;
  else if (operation == "-")
    return operand1 - operand2;
  else if (operation == "*")
    return operand1 * operand2;
  else if (operation == "/")
    return operand1 / operand2;
  else if (operation == "mod")
    return fmod(operand1, operand2);
  else if (operation == "^")
    return pow(operand1, operand2);
  else {
    CleanData();
    throw std::runtime_error("Unknown operation in function!");
  }
}

double ExampleModel::PerformOperationWithOneOperands(std::string operation,
                                                     double operand1) {
  if (operation == "sin")
    return sin(operand1);
  else if (operation == "cos")
    return cos(operand1);
  else if (operation == "tan")
    return tan(operand1);
  else if (operation == "log")
    return log10(operand1);
  else if (operation == "abs")
    return abs(operand1);
  else if (operation == "ln")
    return log(operand1);
  else if (operation == "acos")
    return acos(operand1);
  else if (operation == "asin")
    return asin(operand1);
  else if (operation == "atan")
    return atan(operand1);
  else if (operation == "sqrt")
    return sqrt(operand1);
  else if (operation == "_")
    return -operand1;
  else {
    CleanData();
    throw std::runtime_error("Unknown operation in function.");
  };
}

void ExampleModel::AddOperation(std::string operation,
                                std::stack<std::string>& signs) {
  if (!signs.empty()) {
    if (operation == "(" || operation == ")") {
      AddBracketsInPolishNotation(operation, signs);
    } else if (GetRang(operation) > GetRang(signs.top())) {
      signs.push(operation);
    } else {
      while (!signs.empty() && GetRang(signs.top()) >= GetRang(operation)) {
        polish_notation_.push(signs.top());
        signs.pop();
      }
      signs.push(operation);
    }
  } else {
    signs.push(operation);
  }
}

void ExampleModel::AddBracketsInPolishNotation(std::string operation,
                                               std::stack<std::string>& signs) {
  if (operation == ")") {
    while (!signs.empty() && signs.top() != "(") {
      polish_notation_.push(signs.top());
      signs.pop();
    }
    if (!signs.empty()) signs.pop();
  } else if (operation == "(") {
    signs.push(operation);
  }
}

bool ExampleModel::IsThisDigit(char chr) {
  if ((chr >= '0' && chr <= '9') || (chr == 'x'))
    return true;
  else
    return false;
}

extern "C" {
    // JNI функция для вызова метода Calculate из Java
    JNIEXPORT jdouble JNICALL Java_school21_smartcalc_application_smartcalc_HelloController_Calculate(JNIEnv *env, jobject obj,  jstring func, jstring x) {
        try {
            const char* funcC = env->GetStringUTFChars(func, nullptr);
            const char* xC = env->GetStringUTFChars(x, nullptr);

            std::string cppFunc(funcC);
            std::string cppX(xC);

            ExampleModel model;
            model.Calculate(cppFunc, cppX);
            jdouble result = model.GetData();

            env->ReleaseStringUTFChars(func, funcC);
            env->ReleaseStringUTFChars(x, xC);

            return result;
        } catch (const std::runtime_error& e) {
            env->ThrowNew(env->FindClass("java/lang/RuntimeException"), e.what());
            return 0;  // Возвращаем значение по умолчанию
        }
    }
}