//copyright 2025 deepfrog@deepfrog.org
//CPPMATCH
//adds a rust style variant matching syntactic construct
//in the form of the `match` keyword.
//AS A RESULT, ANY CODE THAT INCLUDES THIS FILE MUST TREAT `match`, ALL THE VARIANTS OF `on`
//AND `mcase` AS RESERVED WORDS
//
//THIS BREAKS C++ STANDARD, THIS IS BY DESIGN, FUCK THE STANDARD
#pragma once
#include <variant>
#include <iostream>

template<class... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};
template<class... Ts>
overload(Ts...) -> overload<Ts...>;

#define match                                                                  \
  {                                                                            \
    auto visitor = overload
#define eval_on(x)                                                             \
  auto _a = x;                                                                 \
  std::visit(visitor, _a);                                                     \
  }                                                                            \

#define return_on(x)                                                            \
  ;                                                                            \
  auto  _a = x;                                                               \
  return std::visit(visitor, _a);}

#define assign_on(x, y)                                                           \
  ;                                                                            \
  auto _a = x;                                                                 \
  y = std::visit(visitor, _a);}                                                 \

#define mcase(v) [&](v & val)
#define mcase_const(v) [&](const v& val)

//usage example
/*
int main() {
  std::variant<int, float> message;
  message = 2.0f;

  match {
    mcase(float) { std::cout << val << "\n"; },
    mcase(int)   { std::cout << "Integers not supported." << "\n";},
  } eval_on(message);


  >>2.0f

  the `x` in xxx_on(x,[y]) must be a std::variant type

  the value of the match is always stored in the variable `val`
  within mcases
}
*/
