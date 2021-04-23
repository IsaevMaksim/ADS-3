// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int pri(char c) {
  if (c == '*' || c == '/')
    return 3;
  else if (c == '+' || c == '-')
    return 2;
  else if (c == ')')
    return 1;
  else
    return 0;
}

std::string infx2pstfx(std::string inf) {
  TStack<char> stack;
  std::string str;
  for (int i = 0; i < inf.length(); i++) {
    if (inf[i] >= '1' && inf[i] <= '9') {
      str += inf[i];
      str += ' ';
    }
    else if (inf[i] == '(' || pri(inf[i]) > pri(stack.get()) || stack.isEmpty())
      stack.push(inf[i]);
    else if (inf[i] == ')') {
      char ch;
      do {
        ch = stack.get();
        stack.pop();
        str += ch;
        str += ' ';
      } while (ch != '(');
    }
    else {
      while (pri(stack.get()) >= pri(inf[i]) && !stack.isEmpty()) {
        str += stack.get();
        str += ' ';
        stack.pop();
      }
      stack.push(inf[i]);
    }
  }
  while (!stack.isEmpty()) {
    str += stack.get();
    str += ' ';
    stack.pop();
  }
  str.pop_back();
  return str;
}

int eval(std::string pst) {
  TStack<char> stack;
  for (int i=0; i<pst.length(); i++){
    if (pst[i] >= '1' && pst[i] <= '9')
      stack.push(pst[i] - '0');
    else if (pst[i] != ' ') {
      int n2 = stack.get();
      stack.pop();
      int n1 = stack.get();
      stack.pop();
      if (pst[i] == '*')
        stack.push(n1 * n2);
      else if (pst[i] == '+')
        stack.push(n1 + n2);
      else if (pst[i] == '/')
        stack.push(n1 / n2);
      else
        stack.push(n1 - n2);
    }
  }
  return stack.get();
}
